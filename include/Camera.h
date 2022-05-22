/* 3D Camera Abstraction */

#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

namespace GLhf
{

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
        Camera() {}

        // Properties
        float yaw_ = -90.0f;
        float pitch_ = 0.0f;
        float speed_ = 5.0f;
        float sensitivity_ = 0.1f;
        float zoom_ = 45.0f;

        // Directions
        glm::vec3 position_;
        glm::vec3 front_;
        glm::vec3 up_;
        glm::vec3 right_;
        glm::vec3 world_up_;

        // Constructors
        void Create(glm::vec3 position = glm::vec3(0.0f, 0.0f, 4.0f),
                    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
        void Create(float posX, float posY, float posZ,
                    float upX, float upY, float upZ);
        void Create(float posX, float posY, float posZ);

        glm::mat4 GetViewMatrix();

        void Set(glm::vec3 pos, glm::vec3 up);
        void Set(glm::vec3 pos);
        void Set(float posX, float posY, float posZ,
                float upX, float upY, float upZ);
        void Set(float posX, float posY, float posZ);
        void SetSpeed(float s) { speed_ = s;}

        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void ProcessKeyboard(CameraDirection direction, float deltaTime);

    private:
        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors();
    };

}