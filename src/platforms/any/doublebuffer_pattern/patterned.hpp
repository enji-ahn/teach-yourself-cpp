#ifndef __PATTERNED__HPP__
#define __PATTERNED__HPP__

#include <cassert>
#include <iostream>
#include <list>
#include <memory>

class FrameBuffer {
  public:
    FrameBuffer() { clear();  }
    void clear() {
      for (auto i = 0; i < WIDTH * HEIGHT; ++i) {
        pixels_[i] = 0xFF; // WHITE
      }
    }
    void draw(int x, int y) {
      pixels_[WIDTH * y + x] = 0x00; // BLACK
    }

    const unsigned char *getPixels() { return pixels_; }

    static const int WIDTH = 16;
    static const int HEIGHT = 12;

  private:

    unsigned char pixels_[WIDTH * HEIGHT];
};

class Scene {
  public:
  Scene(): current_(&buffers_[0]), next_(&buffers_[1]) {}
  void draw() {
    static unsigned char map[][6] = {
      { 0, 0, 0, 0, 0, 0 },
      { 0, 1, 0, 0, 1, 0 },
      { 0, 0, 0, 0, 0, 0 },
      { 0, 1, 0, 0, 1, 0 },
      { 0, 0, 1, 1, 0, 0 },
      { 0, 0, 0, 0, 0, 0 }
    };
    unsigned char *linear_map = (unsigned char *)map;

    for (int i = 0; i < sizeof(map); ++i) {
      linear_map[i] = (linear_map[i] == 0) ? 1 : 0;
    }

    next_->clear();
    int MAX_Y = static_cast<int>(sizeof(map) / sizeof(map[0]));
    int MAX_X = static_cast<int>(sizeof(map[0]));
    for (auto y = 0; y < MAX_Y; ++y) {
      for (auto x = 0; x < MAX_X; ++x) {
        if (map[y][x] == 0) { continue; }
        next_->draw(x, y);
      }
    }
    swap();
  }

  FrameBuffer &getBuffer() { return *current_; }

private:
void swap() {
  auto tmp = current_;
  current_ = next_;
  next_ = tmp;
}
  FrameBuffer buffers_[2];
  FrameBuffer *current_;
  FrameBuffer *next_;
};
#endif