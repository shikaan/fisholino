#pragma once

#include <cmath>

#include "./Floor.cpp"
#include "./HUD.cpp"
#include "./ScoreEvent.cpp"
#include "./helpers.h"
#include <latebit/DisplayManager.h>
#include <latebit/EventOut.h>
#include <latebit/Object.h>
#include <latebit/WorldManager.h>

using namespace lb;
using namespace std;

class Enemy : public Object {
private:
  void initialize() {
    static int h = DM.getHorizontalCells();
    static int v = DM.getVerticalCells();
    static int spriteHeight = getAnimation().getSprite()->getHeight();
    static int boxHeight = getBox().getHeight();
    static int lanes =
        floor((v - Floor::HEIGHT - HUD::HEIGHT) / (float)spriteHeight);

    int lane = randomRange(0, lanes);
    setVelocity(Vector(-1, 0));
    Vector pos(randomRange(h, 2 * h), HUD::HEIGHT + lane * spriteHeight);
    setPosition(pos);
  }

public:
  Enemy() {
    setType("Enemy");
    setSprite("enemy");
    setBox(Box(Vector(2, 7), 20, 6));
    setSolidness(SOFT);
    initialize();
    subscribe(OUT_EVENT);
  }

  int eventHandler(const Event *p_e) {
    if (p_e->getType() == OUT_EVENT) {
      WM.onEvent(new ScoreEvent(1));
      initialize();
      return 1;
    }

    return 0;
  }
};