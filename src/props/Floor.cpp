#pragma once

#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/graphics/Frame.h>
#include <latebit/core/objects/Object.h>

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