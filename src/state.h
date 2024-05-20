#pragma once

class State {
private:
  static int score;

public:
  static void setScore(int s);
  static void addScore(int s);
  static int getScore();
};