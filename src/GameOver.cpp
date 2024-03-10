#include "./GameOverEvent.cpp"
#include "./GameStartEvent.cpp"
#include "./ScoreEvent.cpp"
#include <latebit/DisplayManager.h>
#include <latebit/EventKeyboard.h>
#include <latebit/GameManager.h>
#include <latebit/Music.h>
#include <latebit/Object.h>
#include <latebit/ObjectListIterator.h>
#include <latebit/ResourceManager.h>
#include <latebit/WorldManager.h>

using namespace lb;

class GameOver : public lb::Object {
private:
  bool shouldDraw = false;
  int score = 0;
  Frame frame;
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
    this->frame =
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
    int result = this->frame.draw(Vector());

    result += DM.drawString(
        lb::Vector(DM.getHorizontalCells() / 2.0,
                   DM.getVerticalCells() / 2.0 - FONT_SIZE_DEFAULT),
        "GAME OVER", ALIGN_CENTER, WHITE);

    char s[16];
    sprintf(s, "Score: %d", score);
    result += DM.drawString(
        lb::Vector(DM.getHorizontalCells() / 2.0, DM.getVerticalCells() / 2.0),
        s, ALIGN_CENTER, WHITE);

    result += DM.drawString(
        lb::Vector(DM.getHorizontalCells() / 2.0,
                   DM.getVerticalCells() / 2.0 + FONT_SIZE_DEFAULT),
        "Press [Esc] to close", ALIGN_CENTER, WHITE);

    result += DM.drawString(
        lb::Vector(DM.getHorizontalCells() / 2.0,
                   DM.getVerticalCells() / 2.0 + FONT_SIZE_DEFAULT * 2),
        "Press [Return] to restart", ALIGN_CENTER, WHITE);

    return result;
  };
};