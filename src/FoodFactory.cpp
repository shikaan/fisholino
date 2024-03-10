#pragma once

#include "./Food.cpp"
#include <latebit/EventStep.h>
#include <latebit/Object.h>
#include <latebit/ObjectList.h>
#include <latebit/ObjectListIterator.h>
#include <latebit/WorldManager.h>

using namespace lb;

class FoodFactory : public Object {
private:
  ObjectList food;
  int allowedCount;
  int interval;

public:
  FoodFactory() {
    setType("FoodFactory");
    food = ObjectList();
    interval = 60;
    allowedCount = 2;
    subscribe(STEP_EVENT);
  };

  ~FoodFactory() {
    ObjectListIterator oli(&food);

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
      ObjectListIterator oli(&food);
      ObjectList newFood = WM.objectsOfType("Food");

      if (newFood.getCount() < allowedCount) {
        newFood.insert(new Food());
      }

      food = newFood;
      interval = 60;
      return 1;
    }

    return 0;
  }
};