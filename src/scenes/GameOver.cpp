#include "Scene.h"
#include "events/events.h"
#include "helpers.h"
#include "state.h"
#include <latebit/core/GameManager.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/audio/Music.h>
#include <latebit/core/events/EventKeyboard.h>
#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/ObjectListIterator.h>
#include <latebit/core/objects/WorldManager.h>

using namespace lb;

class GameOver : public Scene {
public:
  GameOver() {
    setType("GameOver");
    setSolidness(lb::SPECTRAL);
    setAltitude(4);
    subscribe(SCORE_UPDATED_EVENT);
    subscribe(KEYBOARD_EVENT);
  };

  void play() {
    DM.setBackground(Color::BLACK);
    setVisible(true);
  }

  void cleanup() {}

  int eventHandler(const Event *e) {
    if (e->getType() == KEYBOARD_EVENT) {
      auto event = static_cast<const EventKeyboard *>(e);
      if (event->getKey() == Keyboard::ESCAPE) {
        GM.setGameOver();
        return 1;
      }

      if (event->getKey() == Keyboard::RETURN &&
          event->getKeyboardAction() == KEY_PRESSED) {
        WM.onEvent(new GameStartEvent());

        return 1;
      }
    }

    return 0;
  };

  int draw() {
    int result = 0;

    result += DM.drawString(CENTER - Vector(0, 32), "GAME OVER",
                            TEXT_ALIGN_CENTER, RED, TEXT_SIZE_XLARGE);
    result += DM.drawString(CENTER - Vector(1, 33), "GAME OVER",
                            TEXT_ALIGN_CENTER, WHITE, TEXT_SIZE_XLARGE);

    char s[16];
    snprintf(s, 16, "SCORE: %d", State::getScore());
    result +=
        DM.drawString(CENTER, s, TEXT_ALIGN_CENTER, WHITE, TEXT_SIZE_LARGE);

#ifndef __EMSCRIPTEN__
    result += DM.drawString(CENTER + Vector(0, 24), "Press [Esc] to close",
                            TEXT_ALIGN_CENTER, WHITE);
#endif

    result += DM.drawString(CENTER + Vector(0, 40), "Press [Return] to restart",
                            TEXT_ALIGN_CENTER, WHITE);

    return result;
  };
};