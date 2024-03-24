#include "./GameOverEvent.cpp"
#include "./GameStartEvent.cpp"
#include "./ScoreEvent.cpp"
#include <latebit/Colors.h>
#include <latebit/DisplayManager.h>
#include <latebit/EventKeyboard.h>
#include <latebit/GameManager.h>
#include <latebit/Music.h>
#include <latebit/Object.h>
#include <latebit/ObjectListIterator.h>
#include <latebit/ResourceManager.h>
#include <latebit/WorldManager.h>

using namespace lb;

const Vector CENTER =
    Vector(DM.getHorizontalCells() / 2, DM.getVerticalCells() / 2);

class GameOver : public lb::Object {
private:
  bool shouldDraw = false;
  int score = 0;
  Frame background;
  Music *music;

public:
  GameOver() {
    setType("GameOver");
    setSolidness(lb::SPECTRAL);
    setAltitude(4);
    subscribe(SCORE_EVENT);
    subscribe(KEYBOARD_EVENT);
    subscribe(GAME_OVER);
    vector<Color> content;
    this->music = RM.getMusic("music");
    for (int i = 0; i < DM.getHorizontalCells() * DM.getVerticalCells(); i++) {
      content.push_back(BLACK);
    }
    this->background =
        Frame(DM.getHorizontalCells(), DM.getVerticalCells(), content);
  };

  int eventHandler(const Event *p_e) {
    if (p_e->getType() == GAME_OVER) {
      shouldDraw = true;

      auto all = WM.getAllObjects();
      ObjectListIterator oli(&all);

      for (oli.first(); !oli.isDone(); oli.next()) {
        auto object = oli.currentObject();
        if (object != this && object->getType() != "GameStart")
          WM.markForDelete(object);
      }

      return 1;
    }

    if (p_e->getType() == SCORE_EVENT) {
      auto event = static_cast<const ScoreEvent *>(p_e);
      score += event->getPoints();
      return 1;
    }

    if (p_e->getType() == KEYBOARD_EVENT) {
      auto event = static_cast<const EventKeyboard *>(p_e);
      if (shouldDraw && event->getKey() == Keyboard::ESCAPE) {
        GM.setGameOver();
        return 1;
      }

      if (shouldDraw && event->getKey() == Keyboard::RETURN &&
          event->getKeyboardAction() == KEY_PRESSED) {
        WM.onEvent(new GameStartEvent());
        WM.markForDelete(this);
        return 1;
      }
    }

    return 0;
  };

  int draw() {
    if (!shouldDraw)
      return 0;

    this->music->stop();
    int result = this->background.draw(Vector());

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