#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Define possible camera movements
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
    // Camera properties
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler angles
    GLfloat Yaw;
    GLfloat Pitch;

    // Camera options
    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;

    // Constructors
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        GLfloat yaw = YAW,
        GLfloat pitch = PITCH);

    Camera(
        GLfloat posX, GLfloat posY, GLfloat posZ,
        GLfloat upX, GLfloat upY, GLfloat upZ,
        GLfloat yaw, GLfloat pitch)
        : Camera(
            glm::vec3(posX, posY, posZ),
            glm::vec3(upX, upY, upZ),
            yaw,
            pitch) { }

    // Gets the view matrix
    glm::mat4 GetViewMatrix();

    // Processes a keyboard-like input to perform movement
    void ProcessMovement(CameraMovement direction, GLfloat deltaTime);

    // Processes a mouse-like input to perform eye movement
    void ProcessEyeMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

    // Processes a mouse-wheel-like input to perform zoom
    void ProcessZoom(GLfloat yoffset);

private:
    // Update the camera vectors based on the current pitch and Yaw
    void updateCameraVectors();
};