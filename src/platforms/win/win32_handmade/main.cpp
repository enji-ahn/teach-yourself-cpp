#include "pch.h"
#include <windows.h>
#include <tchar.h>
#include <cassert>
#include <stdint.h>
#include <xinput.h>
#include <dsound.h>
#include <math.h>
#include <stdio.h>

#define PI32 3.14159265f

static BOOL Running;

struct win32_offscreen_buffer
{
    BITMAPINFO Info;
    void *Memory;
    int Width;
    int Height;
    int Pitch;
};

win32_offscreen_buffer GlobalBackBuffer;
LPDIRECTSOUNDBUFFER GlobalSecondaryBuffer;

struct win32_window_dimension
{
    int width;
    int height;
};

#if 0
LARGE_INTEGER
QueryPerformanceCount
#endif

#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(x_input_get_state);
X_INPUT_GET_STATE(XInputGetStateStub)
{
    return ERROR_DEVICE_NOT_CONNECTED;
}
static x_input_get_state *XInputGetState_ = XInputGetStateStub;

#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
typedef X_INPUT_SET_STATE(x_input_set_state);
X_INPUT_SET_STATE(XInputSetStateStub)
{
    return ERROR_DEVICE_NOT_CONNECTED;
}
static x_input_set_state *XInputSetState_ = XInputSetStateStub;

#define XInputGetState XInputGetState_
#define XInputSetState XInputSetState_

static void
Win32LoadXInput()
{
    auto XInputLibrary = LoadLibrary(_T("xinput1_4.dll"));
    if (!XInputLibrary)
    {
        XInputLibrary = LoadLibrary(_T("xinput1_3.dll"));
    }

    if (XInputLibrary)
    {
        XInputGetState = (x_input_get_state *)GetProcAddress(XInputLibrary, "XInputGetState");
        XInputSetState = (x_input_set_state *)GetProcAddress(XInputLibrary, "XInputSetState");
    }
}

#define DIRECT_SOUND_CREATE(name) DWORD WINAPI name(LPGUID lpGuid,       \
                                                    LPDIRECTSOUND *ppDS, \
                                                    LPUNKNOWN pUnkOuter)
typedef DIRECT_SOUND_CREATE(direct_sound_create);

static void
Win32InitDSound(HWND hwnd,
                int32_t SamplesPerSecond,
                int32_t BufferSize)
{
    // load the library
    auto DSoundLibrary = LoadLibrary(_T("dsound.dll"));

    if (DSoundLibrary)
    {
        // get a DirectSound object
        auto DirectSoundCreate = (direct_sound_create *)GetProcAddress(DSoundLibrary,
                                                                       "DirectSoundCreate");

        LPDIRECTSOUND DirectSound;

        if (DirectSoundCreate && SUCCEEDED(DirectSoundCreate(NULL,
                                                             &DirectSound,
                                                             NULL)))
        {
            WAVEFORMATEX WaveFormat = {};
            WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
            WaveFormat.nChannels = 2;
            WaveFormat.nSamplesPerSec = SamplesPerSecond;
            WaveFormat.wBitsPerSample = 16;
            WaveFormat.nBlockAlign = (WaveFormat.nChannels * WaveFormat.wBitsPerSample) / 8;
            WaveFormat.nAvgBytesPerSec = WaveFormat.nSamplesPerSec * WaveFormat.nBlockAlign;
            WaveFormat.cbSize = 0;

            if (SUCCEEDED(DirectSound->SetCooperativeLevel(hwnd,
                                                           DSSCL_PRIORITY)))
            {
                DSBUFFERDESC BufferDescription = {};
                BufferDescription.dwSize = sizeof(BufferDescription);
                BufferDescription.dwFlags = DSBCAPS_PRIMARYBUFFER;

                // create a primary buffer
                LPDIRECTSOUNDBUFFER PrimaryBuffer;
                if (SUCCEEDED(DirectSound->CreateSoundBuffer(&BufferDescription,
                                                             &PrimaryBuffer,
                                                             0)))
                {
                    auto error = PrimaryBuffer->SetFormat(&WaveFormat);
                    if (SUCCEEDED(error))
                    {
                        OutputDebugString(
                            _T("Primary buffer format was set\n"));
                    }
                    else
                    {
                    }
                }
            }
            else
            {
            }

            DSBUFFERDESC BufferDescription = {};
            BufferDescription.dwSize = sizeof(BufferDescription);
            BufferDescription.dwFlags = 0;
            BufferDescription.dwBufferBytes = BufferSize;
            BufferDescription.lpwfxFormat = &WaveFormat;

            // create a secondary buffer

            if (SUCCEEDED(DirectSound->CreateSoundBuffer(&BufferDescription,
                                                         &GlobalSecondaryBuffer,
                                                         0)))
            {
                OutputDebugString(
                    _T("Secondary buffer format was set\n"));
            }
            else
            {
            }
        }

        // start it playing
    }
}

static win32_window_dimension
Win32GetWindowDimension(HWND hwnd)
{
    win32_window_dimension result;

    RECT ClientRect;
    GetClientRect(hwnd, &ClientRect);
    result.width = ClientRect.right - ClientRect.left;
    result.height = ClientRect.bottom - ClientRect.top;

    return result;
}

static void RenderWiredGradient(win32_offscreen_buffer Buffer,
                                int const &BlueOffset,
                                int const &GreenOffset)
{
    auto row = (uint8_t *)Buffer.Memory;
    for (int y = 0; y < Buffer.Height; ++y)
    {
        auto pixel = (uint32_t *)row;
        for (int x = 0; x < Buffer.Width; ++x)
        {
            // memory   : BB GG RR xx
            // register : xx RR GG BB
            uint8_t green = y + GreenOffset;
            uint8_t blue = x + BlueOffset;
            *pixel = ((green << 8) | blue);
            ++pixel;
        }

        row += Buffer.Pitch;
    }
}

static void Win32ResizeDIBSection(win32_offscreen_buffer *Buffer,
                                  long const &width,
                                  long const &height)
{
    if (Buffer->Memory)
    {
        VirtualFree(Buffer->Memory, 0, MEM_RELEASE);
    }

    Buffer->Width = width;
    Buffer->Height = height;

    auto const BytesPerPixel = 4;

    Buffer->Info.bmiHeader.biSize = sizeof(Buffer->Info.bmiHeader);
    Buffer->Info.bmiHeader.biWidth = Buffer->Width;
    Buffer->Info.bmiHeader.biHeight = -1 * Buffer->Height;
    Buffer->Info.bmiHeader.biPlanes = 1;
    Buffer->Info.bmiHeader.biBitCount = 32;
    Buffer->Info.bmiHeader.biCompression = BI_RGB;

    auto const BitmapMemorySize = Buffer->Width * Buffer->Height * BytesPerPixel;
    Buffer->Memory = VirtualAlloc(
        NULL,
        BitmapMemorySize,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE);
    assert(Buffer->Memory);

    Buffer->Pitch = width * BytesPerPixel;
}

static void Win32DisplayBufferInWindow(
    win32_offscreen_buffer const &Buffer,
    HDC hdc,
    long WindowWidth,
    long WindowHeight)
{
    StretchDIBits(
        hdc,
        0,
        0,
        WindowWidth,
        WindowHeight,
        0,
        0,
        Buffer.Width,
        Buffer.Height,
        Buffer.Memory,
        &Buffer.Info,
        DIB_RGB_COLORS,
        SRCCOPY);
}

LRESULT CALLBACK Win32MainWindowCallback(_In_ HWND hwnd,
                                         _In_ UINT uMsg,
                                         _In_ WPARAM wParam,
                                         _In_ LPARAM lParam)
{
    LRESULT result = 0;

    switch (uMsg)
    {
    case WM_SIZE:
    {
        // OutputDebugStringA("WM_SIZE\n");
    }
    break;
    case WM_DESTROY:
        Running = FALSE;
        // OutputDebugStringA("WM_DESTROY\n");
        break;
    case WM_CLOSE:
        Running = FALSE;
        // OutputDebugStringA("WM_CLOSE\n");
        break;
    case WM_ACTIVATEAPP:
        OutputDebugStringA("WM_ACTIVATEAPP\n");
        break;
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        auto WasDown = (lParam & (1 << 30)) != 0; // 30bit of lParam has previous key state
        auto IsDown = (lParam & ((unsigned long)1 << 31)) == 0;  // 31bit of lParam has current key state (1 mean key up)
        auto VKCode = (uint32_t)wParam;

        if (WasDown != IsDown)
        {
            if (VKCode == 'W')
            {
                OutputDebugString(_T("W"));
            }
            else if (VKCode == 'S')
            {
            }
            else if (VKCode == 'A')
            {
            }
            else if (VKCode == 'D')
            {
            }
            else if (VKCode == 'Q')
            {
            }
            else if (VKCode == 'E')
            {
            }
            else if (VKCode == VK_UP)
            {
            }
            else if (VKCode == VK_LEFT)
            {
            }
            else if (VKCode == VK_DOWN)
            {
            }
            else if (VKCode == VK_RIGHT)
            {
            }
            else if (VKCode == VK_ESCAPE)
            {
                OutputDebugString(_T("escape: "));
                if (IsDown)
                {
                    OutputDebugString(_T("IsDown "));
                }

                if (WasDown)
                {
                    OutputDebugString(_T("WasDown "));
                }

                OutputDebugString(_T("\n"));
            }
            else if (VKCode == VK_SPACE)
            {
            }
        }

        auto AltKeyWasDown = (lParam & (1 << 29)) != 0;
        if (VKCode == VK_F4 && AltKeyWasDown)
        {
            Running = false;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT Paint;
        auto context = BeginPaint(hwnd, &Paint);

        auto dimension = Win32GetWindowDimension(hwnd);
        Win32DisplayBufferInWindow(
            GlobalBackBuffer,
            context,
            dimension.width,
            dimension.height);

        EndPaint(hwnd, &Paint);
    }
    break;
    default:
        result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;
    }

    return result;
}

struct win32_sound_output
{
    int SamplesPerSecond;
    int ToneHz;
    int32_t RunningSampleIndex;
    int WavePeriod;
    int BytesPerSample;
    int SecondaryBufferSize;
    int16_t ToneVolume;
};

static void
Win32FillSoundBuffer(win32_sound_output *SoundOutput,
                     DWORD ByteToLock,
                     DWORD BytesToWrite)
{
    void *Region1;
    DWORD Region1Size;
    void *Region2;
    DWORD Region2Size;

    if (SUCCEEDED(GlobalSecondaryBuffer->Lock(ByteToLock,
                                              BytesToWrite,
                                              &Region1,
                                              &Region1Size,
                                              &Region2,
                                              &Region2Size,
                                              0)))
    {
        auto SampleOut = (int16_t *)Region1;
        auto Region1SampleCount = Region1Size / SoundOutput->BytesPerSample;
        for (auto SampleIndex = 0; SampleIndex < Region1SampleCount; ++SampleIndex)
        {
            auto t = (2.f * PI32 * (float)SoundOutput->RunningSampleIndex) / (float)SoundOutput->WavePeriod;
            auto SineValue = sinf(t);
            auto SampleValue = (int16_t)(SineValue * SoundOutput->ToneVolume);

            *SampleOut++ = SampleValue;
            *SampleOut++ = SampleValue;
            ++(SoundOutput->RunningSampleIndex);
        }

        SampleOut = (int16_t *)Region2;
        auto Region2SampleCount = Region2Size / SoundOutput->BytesPerSample;
        for (auto SampleIndex = 0; SampleIndex < Region2SampleCount; ++SampleIndex)
        {
            auto t = (2.f * PI32 * (float)SoundOutput->RunningSampleIndex) / (float)SoundOutput->WavePeriod;
            auto SineValue = sinf(t);
            auto SampleValue = (int16_t)(SineValue * SoundOutput->ToneVolume);

            *SampleOut++ = SampleValue;
            *SampleOut++ = SampleValue;
            ++(SoundOutput->RunningSampleIndex);
        }

        GlobalSecondaryBuffer->Unlock(Region1,
                                      Region1Size,
                                      Region2,
                                      Region2Size);
    }
}

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    Win32LoadXInput();
    Win32ResizeDIBSection(&GlobalBackBuffer,
                          1024,
                          768);

    LARGE_INTEGER PerformanceFrequency;
    QueryPerformanceFrequency(&PerformanceFrequency);
    auto PerfCountFrequency = PerformanceFrequency.QuadPart;

    WNDCLASS WindowClass = {};
    WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = Win32MainWindowCallback;
    WindowClass.hInstance = hInstance;
    WindowClass.hIcon = NULL;
    WindowClass.lpszClassName = _T("Handmade Hero Window Class");

    auto registered = RegisterClass(&WindowClass);
    assert(registered);

    auto WindowHandle = CreateWindowEx(
        0,
        WindowClass.lpszClassName,
        _T("Handmade Hero"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        hInstance,
        0);
    assert(WindowHandle != 0);

    // NOTE: since we specified CW_OWNDC, we can just get one device context
    // and use it forever because we are not sharing it with anyone
    auto DeviceContext = GetDC(WindowHandle);

    Running = TRUE;

    auto XOffset = 0;
    auto YOffset = 0;

    win32_sound_output SoundOutput = {};
    SoundOutput.SamplesPerSecond = 48000;
    SoundOutput.ToneHz = 256;
    SoundOutput.RunningSampleIndex = 0;
    SoundOutput.WavePeriod = SoundOutput.SamplesPerSecond / SoundOutput.ToneHz;
    SoundOutput.BytesPerSample = sizeof(int16_t) * 2;
    SoundOutput.SecondaryBufferSize = SoundOutput.SamplesPerSecond * SoundOutput.BytesPerSample;
    SoundOutput.ToneVolume = 3800;

    Win32InitDSound(WindowHandle,
                    SoundOutput.SamplesPerSecond,
                    SoundOutput.SecondaryBufferSize);
    Win32FillSoundBuffer(&SoundOutput, 0, SoundOutput.SecondaryBufferSize);
    GlobalSecondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);

    LARGE_INTEGER LastCounter;
    ;
    QueryPerformanceCounter(&LastCounter);

    while (Running)
    {

        MSG Message;
        while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
        {
            if (Message.message == WM_QUIT)
            {
                Running = false;
            }

            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

        for (auto ControllerIndex = 0; ControllerIndex < XUSER_MAX_COUNT; ++ControllerIndex)
        {
            XINPUT_STATE ControllerState;
            auto e = XInputGetState(ControllerIndex, &ControllerState);
            if (e == ERROR_SUCCESS)
            {
                // NOTE: this controller is plugged in
                auto *Pad = &(ControllerState.Gamepad);

                auto Up = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
                auto Down = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
                auto Left = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
                auto Right = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
                auto Start = (Pad->wButtons & XINPUT_GAMEPAD_START);
                auto Back = (Pad->wButtons & XINPUT_GAMEPAD_BACK);
                auto LeftShoulder = (Pad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
                auto RightShoulder = (Pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
                auto AButton = (Pad->wButtons & XINPUT_GAMEPAD_A);
                auto BButton = (Pad->wButtons & XINPUT_GAMEPAD_B);
                auto XButton = (Pad->wButtons & XINPUT_GAMEPAD_X);
                auto YButton = (Pad->wButtons & XINPUT_GAMEPAD_Y);

                auto StickX = Pad->sThumbLX;
                auto StickY = Pad->sThumbLY;

                XOffset += StickX >> 12;
                YOffset += StickY >> 12;
            }
            else
            {
                // NOTE: the controller is not available
            }
        }

#if 0 //Vibrate Controller
		XINPUT_VIBRATION Vibration;
		Vibration.wLeftMotorSpeed = 60000;
		Vibration.wRightMotorSpeed = 60000;
		XInputSetState(0, &Vibration);
#endif

        RenderWiredGradient(GlobalBackBuffer, XOffset, YOffset);

        // NOTE: DirectSound output test
        DWORD PlayCursor;
        DWORD WriteCursor;

        if (SUCCEEDED(GlobalSecondaryBuffer->GetCurrentPosition(&PlayCursor,
                                                                &WriteCursor)))
        {
            auto ByteToLock = (SoundOutput.RunningSampleIndex * SoundOutput.BytesPerSample) % SoundOutput.SecondaryBufferSize;
            DWORD BytesToWrite;
            if (ByteToLock == PlayCursor)
            {
                BytesToWrite = 0;
            }
            else if (ByteToLock > PlayCursor)
            {
                BytesToWrite = (SoundOutput.SecondaryBufferSize - ByteToLock);
                BytesToWrite += PlayCursor;
            }
            else
            {
                BytesToWrite = PlayCursor - ByteToLock;
            }

            Win32FillSoundBuffer(&SoundOutput, ByteToLock, BytesToWrite);
        }

        auto dimension = Win32GetWindowDimension(WindowHandle);

        Win32DisplayBufferInWindow(
            GlobalBackBuffer,
            DeviceContext,
            dimension.width,
            dimension.height);

        LARGE_INTEGER EndCounter;
        QueryPerformanceCounter(&EndCounter);

        auto CounterElapsed = EndCounter.QuadPart - LastCounter.QuadPart;
        auto MSPerFrame = (1000 * CounterElapsed) / PerfCountFrequency;
        auto FPS = PerfCountFrequency / CounterElapsed;

        TCHAR buffer[1024];
        _stprintf_s(buffer, 1024, _T("Milliseconds/frame : %lldns / %lldFPS\n"), MSPerFrame, FPS);
        OutputDebugString(_T(""));

        LastCounter = EndCounter;
    }

    return 0;
}
