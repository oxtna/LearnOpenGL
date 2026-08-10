#pragma once
#include <GLFW/glfw3.h>

class Timer
{
  public:
    Timer() : _deltaTime{glfwGetTime()}, _lastUpdateTime{} {}
    explicit Timer(float start) : _deltaTime{start}, _lastUpdateTime{} {}
    // Get the time after last update in seconds.
    float time() const;
    // Time elapsed between the last two updates in seconds.
    float deltaTime() const;
    // Update the timer.
    void update();

  private:
    double _deltaTime;
    double _lastUpdateTime;
};
