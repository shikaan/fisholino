#include "events/events.h"
#include <cstdio>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/SceneGraph.h>
#include <vector>

using namespace lb;
using namespace std;

class HUD : public Object {
private:
  int score = 0;
  const int WIDTH = DM.getHorizontalCells();
  Frame cell;

public:
  static const int HEIGHT = 14;

  HUD() {
    setType("HUD");
    setSolidness(SPECTRAL);
    setAltitude(lb::MAX_ALTITUDE);
    vector<Color> content;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
      content.push_back(BLACK);
    this->cell = Frame(WIDTH, HEIGHT, content);
    // The position represents the bottom left corner.
    // This is used to allow the slide-in effect for the score bar
    this->setPosition(Vector(0, 0));

    subscribe(SCORE_UPDATED_EVENT);
    subscribe(STEP_EVENT);
  }

  int draw() {
    char score[17];
    snprintf(score, 17, "SCORE: %d", this->score);

    auto position = this->getPosition();
    auto topLeftCorner = position - Vector(0, HEIGHT);
    int result = this->cell.draw(topLeftCorner);
    result += DM.drawString(
        Vector(DM.getHorizontalCells() / 2, 4 + topLeftCorner.getY()), score,
        TEXT_ALIGN_CENTER, WHITE);

    return result;
  }

  int eventHandler(const Event *e) {
    if (e->getType() == SCORE_UPDATED_EVENT) {
      auto event = static_cast<const ScoreUpdated *>(e);
      score = event->points;
      return 1;
    }

    if (e->getType() == STEP_EVENT) {
      auto event = static_cast<const EventStep *>(e);
      auto steps = event->getStepCount();

      if (this->getPosition().getY() >= HEIGHT) {
        unsubscribe(STEP_EVENT);
        return 1;
      }

      this->setPosition(this->getPosition() + Vector(0, 1));
    }

    return 0;
  }
};