#include <latebit/core/events/Event.h>

using namespace lb;

const std::string SCORE_UPDATED_EVENT = "score";

class ScoreUpdated : public Event {
public:
  int points = 0;

  ScoreUpdated(int points) {
    setType(SCORE_UPDATED_EVENT);
    this->points = points;
  }
};