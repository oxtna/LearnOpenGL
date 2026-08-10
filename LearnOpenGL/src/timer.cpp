#include "timer.h"
#include <GLFW/glfw3.h>

float Timer::time() const
{
    return static_cast<float>(_lastUpdateTime);
}

float Timer::deltaTime() const
{
    return static_cast<float>(_deltaTime);
}

void Timer::update()
{
    double currentUpdateTime = glfwGetTime();
    _deltaTime = currentUpdateTime - _lastUpdateTime;
    _lastUpdateTime = currentUpdateTime;
}
