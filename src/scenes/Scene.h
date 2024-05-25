#pragma once

#include <latebit/core/objects/Object.h>

class Scene : public lb::Object {
  public:
    Scene() = default;
    virtual void play() = 0;
    virtual void cleanup() = 0;
};