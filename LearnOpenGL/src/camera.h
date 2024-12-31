#pragma once
#include <glm/glm.hpp>

// An abstract camera representation, encapsulating functionality
// related to view matrices and field of view.
class Camera
{
  public:
    static constexpr float Sensitivity = 0.08f;
    static constexpr float Speed = 2.0f;
    static constexpr glm::vec3 DefaultPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    static constexpr glm::vec3 DefaultWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    static constexpr float DefaultYaw = -90.0f;
    static constexpr float DefaultPitch = 0.0f;
    static constexpr float DefaultFieldOfView = 45.0f;

    Camera();
    Camera(
        const glm::vec3& position, const glm::vec3& worldUp, float yaw, float pitch,
        float fieldOfView
    );
    ~Camera();

    glm::vec3 position() const;
    glm::vec3 front() const;
    glm::vec3 up() const;
    glm::vec3 right() const;
    glm::vec3 worldUp() const;
    float fieldOfView() const;
    constexpr float speed() const;
    constexpr float sensitivity() const;

    void translate(const glm::vec3& translation);
    void rotate(float yaw, float pitch);
    void fieldOfView(float fieldOfView);

    // Calculate the view matrix based on the camera's position and directions.
    glm::mat4 getViewMatrix() const;

  private:
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _worldUp;
    float _yaw;
    float _pitch;
    float _fieldOfView;

    // Update camera's front, up and right vectors after changing yaw and/or pitch.
    void updateDirections();
};
