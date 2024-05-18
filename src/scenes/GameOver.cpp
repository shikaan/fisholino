#include "Scene.h"
#include "events/events.h"
#include "helpers.h"
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
private:
  bool visible = false;
  int score = 0;

public:
  GameOver() {
    setType("GameOver");
    setSolidness(lb::SPECTRAL);
    setAltitude(4);
    subscribe(SCORE_EVENT);
    subscribe(KEYBOARD_EVENT);
  };

  void play() {
    DM.setBackground(Color::BLACK);
    visible = true;
  }

  void cleanup() {
    visible = false;
    score = 0;
  }

  int eventHandler(const Event *p_e) {
    // TODO: this should be stored in a game state, not duplicated
    if (p_e->getType() == SCORE_EVENT) {
      auto event = static_cast<const ScoreEvent *>(p_e);
      score += event->getPoints();
      return 1;
    }

    if (p_e->getType() == KEYBOARD_EVENT) {
      auto event = static_cast<const EventKeyboard *>(p_e);
      if (visible && event->getKey() == Keyboard::ESCAPE) {
        GM.setGameOver();
        return 1;
      }

      if (visible && event->getKey() == Keyboard::RETURN &&
          event->getKeyboardAction() == KEY_PRESSED) {
        WM.onEvent(new GameStartEvent());

        return 1;
      }
    }

    return 0;
  };

  int draw() {
    if (!visible)
      return 0;

    int result = 0;

    result += DM.drawString(CENTER - Vector(0, 32), "GAME OVER",
                            TEXT_ALIGN_CENTER, RED, TEXT_SIZE_XLARGE);
    result += DM.drawString(CENTER - Vector(1, 33), "GAME OVER",
                            TEXT_ALIGN_CENTER, WHITE, TEXT_SIZE_XLARGE);

    char s[16];
    snprintf(s, 16, "SCORE: %d", score);
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