#include <stdlib.h>

#include <latebit/EventCollision.h>
#include <latebit/Object.h>

using namespace lb;
using namespace std;

int randomRange(int min, int max) { return min + rand() % (max - min); }
int randomRange(int max) { return randomRange(0, max); }

bool isCollisionWith(const Event *p_e, std::string type) {
  if (p_e->getType() == COLLISION_EVENT) {
    auto event = static_cast<const EventCollision *>(p_e);
    auto obj1 = event->getFirstObject();
    auto obj2 = event->getSecondObject();

    return obj1->getType() == type || obj2->getType() == type;
  }

  return false;
}
