#pragma once

#include "./Enemy.cpp"
#include <latebit/EventStep.h>
#include <latebit/Object.h>
#include <latebit/ObjectList.h>
#include <latebit/ObjectListIterator.h>
#include <latebit/WorldManager.h>
#include <latebit/utils.h>

using namespace lb;

class EnemyFactory : public Object {
private:
  const int INTERVAL = 60;
  const int COUNT = 5;

  ObjectList m_enemies = ObjectList();
  int m_allowedCount = COUNT;
  int m_interval = INTERVAL;

  void placeEnemy(Object *enemy) {
    auto position = enemy->getPosition();
    auto enemyBox = enemy->getWorldBox();

    // check overlap with other enemies
    ObjectListIterator oli(&m_enemies);
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

    for (int i = 0; i < m_allowedCount; i++)
      createEnemy(m_enemies);
  };

  ~EnemyFactory() {
    ObjectListIterator oli(&m_enemies);

    for (oli.first(); !oli.isDone(); oli.next()) {
      WM.markForDelete(oli.currentObject());
    }
  };

  int eventHandler(const Event *p_e) {
    if (p_e->getType() == STEP_EVENT) {
      if (m_interval > 0) {
        m_interval--;
        return 1;
      }
    }

    if (m_interval == 0) {
      ObjectListIterator oli(&m_enemies);
      ObjectList newEnemies = WM.objectsOfType("Enemy");

      if (newEnemies.getCount() < m_allowedCount) {
        createEnemy(newEnemies);
      }

      m_enemies = newEnemies;
      m_interval = INTERVAL;
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