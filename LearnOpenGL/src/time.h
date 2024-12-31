#pragma once

class Time
{
  public:
    // Time at the beginning of the current frame.
    static float time();
    // Time elapsed since last frame in seconds.
    static float deltaTime();
    // Update internal variables storing time and delta time.
    static void update();

  private:
    static float _deltaTime;
    static float _lastFrameTime;
};
