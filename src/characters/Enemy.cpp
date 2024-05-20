#pragma once

#include <cmath>

#include "events/events.h"
#include "helpers.h"
#include "props/props.h"
#include "state.h"
#include "ui/ui.h"
#include <latebit/core/events/EventOut.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/WorldManager.h>

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
    setVelocity(Vector(-1 - State::getScore() / 100.0, 0));
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

  int eventHandler(const Event *e) {
    if (e->getType() == OUT_EVENT) {
      State::addScore(1);
      initialize();
      return 1;
    }

    return 0;
  }
};