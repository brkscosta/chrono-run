#pragma once

namespace core::logic {
class TimeController {
public:
  TimeController();
  ~TimeController();
  void update();
  void setSpeed(float speed);
  float getSpeed();
  void pause();
  void resume();
  void reset();

private:
  float speed;
  bool paused;
};

} // namespace core::logic