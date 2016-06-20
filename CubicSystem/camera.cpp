#include "camera.h"

#include <math.h>

Camera::Camera(
    glm::vec3 position,
    glm::vec3 up,
    GLfloat yaw,
    GLfloat pitch) :

    Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;

    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessMovement(CameraMovement direction, GLfloat deltaTime)
{
    GLfloat velocity = MovementSpeed * deltaTime;
    switch (direction)
    {
    case FORWARD: Position += Front * velocity; break;
    case BACKWARD: Position -= Front * velocity; break;

    case LEFT: Position -= Right * velocity; break;
    case RIGHT: Position += Right * velocity; break;
    }
}

#include <iostream>
void Camera::ProcessEyeMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    if (xoffset == 0 && yoffset == 0)
        return;

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    // If we don't constrain the yaw to only use values between 0-360
    // we would lose floating precission with very high values, hence
    // the movement would look like big "steps" instead a smooth one!
    Yaw = std::fmod((Yaw + xoffset), (GLfloat)360.0f);
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 80.0f)
            Pitch = 80.0f;
        else if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessZoom(GLfloat yoffset)
{
    Zoom -= yoffset / 50.0f; // avoid going too fast

    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 80.0f)
        Zoom = 80.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front(
        cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
        sin(glm::radians(Pitch)),
        sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))
    );
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
