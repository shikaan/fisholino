#include "CameraShake.cpp"
#include "Scene.h"
#include "characters/characters.h"
#include "helpers.h"
#include <latebit/core/events/EventStep.h>
#include <latebit/core/geometry/Box.h>
#include <latebit/core/objects/WorldManager.h>

class Death : public Scene {
  const int DURATION = 50;
  unique_ptr<CameraShake> camerShake = make_unique<CameraShake>(2, DURATION);
  unique_ptr<Sound> death = unique_ptr<Sound>(RM.getSound("death"));
  int initial = 0;

public:
  Death() {
    setType("Death");
    setSolidness(SPECTRAL);
    subscribe(STEP_EVENT);
  }

  int eventHandler(const Event *e) {
    if (e->getType() == STEP_EVENT) {
      initial++;
      if (initial >= DURATION) {
        WM.onEvent(new GameOverEvent());
        return 1;
      }

      if (initial % 3 == 0) {
        DM.setBackground(initial % 2 == 0 ? Color::RED : Color::INDIGO);
      }
    }
    return 0;
  }

  void play() {
    DM.setBackground(Color::RED);
    initial = 0;
    camerShake->start();
    death->play();
  }

  void cleanup() {
    camerShake->stop();
    death->stop();
  }

  int draw() {
    return DM.drawString(CENTER - Vector(0, 16), "DEATH", TEXT_ALIGN_CENTER,
                         WHITE, TEXT_SIZE_XXLARGE);
  };
};