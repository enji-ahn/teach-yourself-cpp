#include <iostream>
#include <cassert>

class Display
{
public:
    virtual void showLine(std::string line) = 0;
};

class ArtR56Display : public Display
{
public:
    virtual void showLine(std::string line)
    {
        std::cout << "R56LCD : " << line << std::endl;
    }
};

class FakeDisplay : public Display
{
public:
    virtual void showLine(std::string line)
    {
        lastLine = line;
    }
    std::string getLastLine()
    {
        return lastLine;
    }

private:
    std::string lastLine;
};

class Sale
{
public:
    Sale(Display &display) : display(display)
    {
    }
    void scan(std::string barcode)
    {
        if (barcode == "1")
        {
            std::string itemLine = "Milk $3.99";
            display.showLine(itemLine);
        }
    }

private:
    Display &display;
};

int main()
{
    // Product Code
    {
        ArtR56Display display;
        Sale sale(display);
        sale.scan("1");
    }

    // 테스트를 위한 Fake Display 객체로 교체하여 출력값이 정상적으로 나오는지 테스트
    {
        Display *display = new FakeDisplay();
        Sale sale(*display);

        sale.scan("1");
        std::string result = static_cast<FakeDisplay *>(display)->getLastLine();
        assert(result == "Milk $3.99");
        std::cout << "result : " << result;
    }

    return 0;
}
