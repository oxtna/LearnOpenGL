#include "time.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float Time::_deltaTime = 0.0f;
float Time::_lastFrameTime = 0.0f;

float Time::time()
{
    return _lastFrameTime;
}

float Time::deltaTime()
{
    return _deltaTime;
}

void Time::update()
{
    float currentFrameTime = static_cast<float>(glfwGetTime());
    _deltaTime = currentFrameTime - _lastFrameTime;
    _lastFrameTime = currentFrameTime;
}
