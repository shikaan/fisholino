#pragma once

#include "./Enemy.cpp"
#include <latebit/core/events/EventStep.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/ObjectList.h>
#include <latebit/core/objects/ObjectListIterator.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/core/utils/utils.h>

using namespace lb;

class EnemyFactory : public Object {
private:
  const int INTERVAL = 60;
  const int COUNT = 5;

  ObjectList enemies = ObjectList();
  int allowedCount = COUNT;
  int interval = INTERVAL;

  void placeEnemy(Object *enemy) {
    auto position = enemy->getPosition();
    auto enemyBox = enemy->getWorldBox();

    // check overlap with other enemies
    ObjectListIterator oli(&enemies);
    for (oli.first(); !oli.isDone(); oli.next()) {
      auto other = oli.currentObject();
      if (other == enemy)
        continue;
      auto otherBox = other->getWorldBox();

      if (intersects(enemyBox, otherBox)) {
        position = other->getPosition() + Vector(otherBox.getWidth() + 20, 0);
        enemy->setPosition(position);
        enemyBox = enemy->getWorldBox();
      }
    }
  }

public:
  EnemyFactory() {
    setType("EnemyFactory");

    for (int i = 0; i < allowedCount; i++)
      createEnemy(enemies);
  };

  ~EnemyFactory() {
    ObjectListIterator oli(&enemies);

    for (oli.first(); !oli.isDone(); oli.next()) {
      WM.markForDelete(oli.currentObject());
    }
  };

  int eventHandler(const Event *p_e) {
    if (p_e->getType() == STEP_EVENT) {
      if (interval > 0) {
        interval--;
        return 1;
      }
    }

    if (interval == 0) {
      ObjectList newEnemies = WM.objectsOfType("Enemy");

      if (newEnemies.getCount() < allowedCount) {
        createEnemy(newEnemies);
      }

      enemies = newEnemies;
      interval = INTERVAL;
      return 1;
    }

    return 0;
  }

  void createEnemy(lb::ObjectList &enemies) {
    auto newEnemy = new Enemy();
    placeEnemy(newEnemy);
    enemies.insert(newEnemy);
  }
};