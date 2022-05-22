/* */

#include "Camera.h"

#include <iostream>

namespace GLhf
{

    // constructor with vectors
    void Camera::Create(glm::vec3 position, glm::vec3 up)
    {
        front_ = glm::vec3(0.0f, 0.0f, -1.0f);
        position_ = position;
        world_up_ = up;
        updateCameraVectors();
    }

    // constructor with scalars
    void Camera::Create(float posX, float posY, float posZ,
        float upX, float upY, float upZ)
    {
        front_ = glm::vec3(0.0f, 0.0f, -1.0f);
        position_ = glm::vec3(posX, posY, posZ);
        world_up_ = glm::vec3(upX, upY, upZ);
        updateCameraVectors();
    }
    // constructor with scalars
    void Camera::Create(float posX, float posY, float posZ)
    {
        front_ = glm::vec3(0.0f, 0.0f, -1.0f);
        position_ = glm::vec3(posX, posY, posZ);
        world_up_ = glm::vec3(0.0f, 1.0f, 0.0f);
        updateCameraVectors();
    }
    
    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(position_, position_ + front_, up_);
    }

    void Camera::Set(glm::vec3 pos, glm::vec3 up)
    {
        front_ = glm::vec3(0.0f, 0.0f, -1.0f);
        position_ = pos;
        world_up_ = up;

        // Calculate right_ and up_ vectors
        right_ = glm::normalize(glm::cross(front_, world_up_)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up_ = glm::normalize(glm::cross(right_, front_));
    }
    void Camera::Set(glm::vec3 pos)
    {
        front_ = glm::vec3(0.0f, 0.0f, -1.0f);
        position_ = pos;

        // Calculate right_ and up_ vectors
        right_ = glm::normalize(glm::cross(front_, world_up_)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up_ = glm::normalize(glm::cross(right_, front_));
    }
    void Camera::Set(float posX, float posY, float posZ,
                    float upX, float upY, float upZ)
    {
        front_ = glm::vec3(0.0f, 0.0f, -1.0f);
        position_ = glm::vec3(posX, posY, posZ);
        world_up_ = glm::vec3(upX, upY, upZ);

        // Calculate right_ and up_ vectors
        right_ = glm::normalize(glm::cross(front_, world_up_)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up_ = glm::normalize(glm::cross(right_, front_));
    }
    void Camera::Set(float posX, float posY, float posZ)
    {
        front_ = glm::vec3(0.0f, 0.0f, -1.0f);
        position_ = glm::vec3(posX, posY, posZ);

        // Calculate right_ and up_ vectors
        right_ = glm::normalize(glm::cross(front_, world_up_)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up_ = glm::normalize(glm::cross(right_, front_));
    }

    // calculates the front vector from the Camera's (updated) Euler Angles
    void Camera::updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        front.y = sin(glm::radians(pitch_));
        front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        front_ = glm::normalize(front);

        // also re-calculate the right_ and up_ vector
        right_ = glm::normalize(glm::cross(front_, world_up_)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up_ = glm::normalize(glm::cross(right_, front_));
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
    {
        xoffset *= sensitivity_;
        yoffset *= sensitivity_;

        yaw_ += xoffset;
        pitch_ += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (pitch_ > 89.0f)
                pitch_ = 89.0f;
            if (pitch_ < -89.0f)
                pitch_ = -89.0f;
        }

        // update Front, right_ and up_ Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void Camera::ProcessKeyboard(CameraDirection direction, float deltaTime)
    {
        float velocity = speed_ * deltaTime;

        if (direction == FORWARD)
            position_ += front_ * velocity;
        if (direction == BACKWARD)
            position_ -= front_ * velocity;
        if (direction == LEFT)
            position_ -= right_ * velocity;
        if (direction == RIGHT)
            position_ += right_ * velocity;
        if (direction == UP)
            position_ += up_ * velocity;
        if (direction == DOWN)
            position_ -= up_ * velocity;
    }
    
}