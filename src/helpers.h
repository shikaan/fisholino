#pragma once
#include <stdlib.h>

#include <latebit/core/events/Event.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>

using namespace lb;
using namespace std;

int randomRange(int max);
int randomRange(int min, int max);
bool isCollisionWith(const Event *p_e, string type);
void cameraShake(int intensity, int durationInFrames);

const Vector CENTER =
    Vector(DM.getHorizontalCells() / 2, DM.getVerticalCells() / 2);