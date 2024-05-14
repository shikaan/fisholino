#pragma once

#include "ScoreEvent.cpp"
#include <cstdio>
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
    subscribe(SCORE_EVENT);
    vector<Color> content;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
      content.push_back(BLACK);
    this->cell = Frame(WIDTH, HEIGHT, content);
  }

  int draw() {
    char score[17];
    snprintf(score, 17, "SCORE: %d", this->score);

    int result = this->cell.draw(Vector());
    result += DM.drawString(Vector(DM.getHorizontalCells() / 2, 4), score,
                            TEXT_ALIGN_CENTER, WHITE);

    return result;
  }

  int eventHandler(const Event *p_e) {
    if (p_e->getType() == SCORE_EVENT) {
      auto event = static_cast<const ScoreEvent *>(p_e);
      score += event->getPoints();
      return 1;
    }
    return 0;
  }
};