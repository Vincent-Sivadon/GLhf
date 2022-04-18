/* */

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

enum CameraDirection
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    // Properties
    float Yaw = -90.0f;
    float Pitch = 0.0f;
    float Speed = 2.5f;
    float Sensitivity = 0.1f;
    float Zoom = 45.0f;

    // Directions
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    void PrintViewMatrix()
    {
        glm::mat4 view = GetViewMatrix();
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                std::cout << view[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 4.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Position(position), WorldUp(up)
    {
        updateCameraVectors();
    }
    // constructor with scalars
    Camera(float posX, float posY, float posZ,
           float upX, float upY, float upZ)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
          Position(glm::vec3(posX, posY, posZ)),
          WorldUp(glm::vec3(upX, upY, upZ))
    {
        updateCameraVectors();
    }
    // constructor with scalars
    Camera(float posX, float posY, float posZ)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
          Position(glm::vec3(posX, posY, posZ)),
          WorldUp(glm::vec3(0.0f, 1.0f, 0.0f))
    {
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix();

    void Set(glm::vec3 pos, glm::vec3 up);
    void Set(glm::vec3 pos);
    void Set(float posX, float posY, float posZ,
             float upX, float upY, float upZ);
    void Set(float posX, float posY, float posZ);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(CameraDirection direction, float deltaTime);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};