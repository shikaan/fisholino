#include <stdlib.h>

#include "helpers.h"
#include <latebit/core/events/EventCollision.h>
#include <latebit/core/objects/Object.h>

using namespace lb;
using namespace std;

int randomRange(int min, int max) { return min + rand() % (max - min); }
int randomRange(int max) { return randomRange(0, max); }

bool isCollisionWith(const Event *e, std::string type) {
  if (e->getType() == COLLISION_EVENT) {
    auto event = static_cast<const EventCollision *>(e);
    auto obj1 = event->getFirstObject();
    auto obj2 = event->getSecondObject();

    return obj1->getType() == type || obj2->getType() == type;
  }

  return false;
}
