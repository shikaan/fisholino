#pragma once
#include <stdlib.h>

#include <latebit/core/events/Event.h>
#include <latebit/core/objects/Object.h>

using namespace lb;
using namespace std;

int randomRange(int max);
int randomRange(int min, int max);
bool isCollisionWith(const Event *p_e, string type);