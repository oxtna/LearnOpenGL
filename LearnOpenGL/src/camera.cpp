#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>

Camera::Camera()
    : _position(DefaultPosition),
      _front(),
      _up(),
      _right(),
      _worldUp(DefaultWorldUp),
      _yaw(DefaultYaw),
      _pitch(DefaultPitch),
      _fieldOfView(DefaultFieldOfView)
{
    updateDirections();
}

Camera::Camera(
    const glm::vec3& position, const glm::vec3& worldUp, float yaw, float pitch, float fieldOfView
)
    : _position(position),
      _front(),
      _up(),
      _right(),
      _worldUp(worldUp),
      _yaw(yaw),
      _pitch(pitch),
      _fieldOfView(fieldOfView)
{
    updateDirections();
}

Camera::~Camera()
{}

glm::vec3 Camera::position() const
{
    return _position;
}

glm::vec3 Camera::front() const
{
    return _front;
}

glm::vec3 Camera::up() const
{
    return _up;
}

glm::vec3 Camera::right() const
{
    return _right;
}

glm::vec3 Camera::worldUp() const
{
    return _worldUp;
}

float Camera::fieldOfView() const
{
    return _fieldOfView;
}

constexpr float Camera::speed() const
{
    return Speed;
}

constexpr float Camera::sensitivity() const
{
    return Sensitivity;
}

void Camera::fieldOfView(float fieldOfView)
{
    _fieldOfView = fieldOfView;
    if (_fieldOfView < 10.0f)
    {
        _fieldOfView = 10.0f;
    }
    else if (_fieldOfView > 45.0f)
    {
        _fieldOfView = 45.0f;
    }
#ifdef _DEBUG
    std::cerr << "Camera field of view: " << _fieldOfView << '\n';
#endif
}

void Camera::translate(const glm::vec3& translation)
{
    _position += translation;
#ifdef _DEBUG
    std::cerr << "Camera position: (" << _position.x << ", " << _position.y << ", " << _position.z
              << ")\n";
#endif
}

void Camera::rotate(float yaw, float pitch)
{
    _yaw += yaw;
    _pitch += pitch;
    if (_pitch > 89.0f)
    {
        _pitch = 89.0f;
    }
    else if (_pitch < -89.0f)
    {
        _pitch = -89.0f;
    }
    updateDirections();
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(_position, _position + _front, _up);
}

void Camera::updateDirections()
{
    _front = glm::vec3(
        std::cosf(glm::radians(_yaw)) * std::cosf(glm::radians(_pitch)),
        std::sinf(glm::radians(_pitch)),
        std::sinf(glm::radians(_yaw)) * std::cosf(glm::radians(_pitch))
    );
    _front = glm::normalize(_front);
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
#ifdef _DEBUG
    std::cerr << "Camera front: (" << _front.x << ", " << _front.y << ", " << _front.z << ")\n";
#endif
}
