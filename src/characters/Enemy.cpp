#pragma once

#include <cmath>

#include "events/events.h"
#include "helpers.h"
#include "props/props.h"
#include "state.h"
#include "ui/ui.h"
#include <latebit/core/events/EventCollision.h>
#include <latebit/core/events/EventOut.h>
#include <latebit/core/geometry/Box.h>
#include <latebit/core/geometry/Vector.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/ObjectList.h>
#include <latebit/core/objects/ObjectListIterator.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/core/utils/utils.h>

using namespace lb;
using namespace std;

int lanes = 1;

class Enemy : public Object {
private:
  int getLanes() {
    const int v = DM.getVerticalCells();
    const int spriteHeight = getAnimation().getSprite()->getHeight();
    return floor((v - Floor::HEIGHT - HUD::HEIGHT - 2) / (float)spriteHeight);
  }

  float getSpeed() { return (1 + State::getScore() / 100.0); }

  // Returns a random vertical position in a lane
  int getVerticalPosition() {
    const int lane = randomRange(0, lanes);
    const int spriteHeight = getAnimation().getSprite()->getHeight();
    return HUD::HEIGHT + 1 + lane * spriteHeight;
  }

  // Returns a random horizontal position that doesn't align verticslly with any
  // other enemy
  int getHorizontalPosition(int offset = 0) {
    const Box box = getSpriteBox(this);
    const int cells = DM.getHorizontalCells();
    const int x = offset + randomRange(cells, 2 * cells);

    ObjectList objects = WM.objectsOfType("Enemy");
    ObjectListIterator it(&objects);
    for (it.first(); !it.isDone(); it.next()) {
      Object *enemy = it.currentObject();
      const Box enemyBox = getSpriteBox(enemy);

      bool intersects =
          (x > enemyBox.getCorner().getX() &&
           x < enemyBox.getCorner().getX() + enemyBox.getWidth()) || // Left
          (x + box.getWidth() > enemyBox.getCorner().getX() &&
           x + box.getWidth() <
               enemyBox.getCorner().getX() + enemyBox.getWidth()); // Right

      if (intersects) {
        // When we push the enemy to the right, we need to ensure the enemy
        // on the left is faster, else it will overtake and they would overlap
        auto enemyVelocity = enemy->getVelocity();
        auto thisVelocity = getVelocity();
        if (enemyVelocity.getX() < thisVelocity.getX()) {
          enemy->setVelocity(thisVelocity);
          setVelocity(enemyVelocity);
        }

        return getHorizontalPosition(enemyBox.getCorner().getX() +
                                     enemyBox.getWidth());
      }
    }

    return x;
  }

  void initialize() {
    setPosition(Vector(getHorizontalPosition(), getVerticalPosition()));
    setVelocity(Vector(-getSpeed(), 0));
  }

  Box getSpriteBox(const Object *enemy) {
    const Vector position = enemy->getPosition();
    const Sprite *sprite = enemy->getAnimation().getSprite();
    const int spriteX = sprite->getWidth();
    const int spriteY = sprite->getHeight();
    return Box(position, spriteX, spriteY);
  }

public:
  Enemy() {
    setType("Enemy");
    setSprite("enemy");
    setBox(Box(Vector(3, 5), 18, 8));
    setSolidness(SOFT);
    initialize();
    subscribe(OUT_EVENT);
    lanes = getLanes();
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