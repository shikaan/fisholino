#pragma once

#include <latebit/Colors.h>
#include <latebit/DisplayManager.h>
#include <latebit/Frame.h>
#include <latebit/Object.h>

using namespace lb;

class Floor : public Object {
private:
  const int WIDTH = DM.getHorizontalCells();
  Frame frame;

public:
  static const int HEIGHT = 8;
  Floor() {
    setType("Floor");
    setSolidness(HARD);
    setPosition(Vector(0, DM.getVerticalCells() - HEIGHT));
    this->frame = Frame(WIDTH, HEIGHT, makeFrame());
  }

  vector<Color> makeFrame() {
    vector<Color> colors = {};
    for (int j = 0; j < HEIGHT; j++) {
      for (int i = 0; i < WIDTH; i++) {
        colors.push_back(Color::RED);
      }
    }

    return colors;
  }

  int draw() { return this->frame.draw(getPosition()); }
};