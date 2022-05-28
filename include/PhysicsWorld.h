#pragma once

#include <Object.h>

#include <vector>

static const float G = 9.81;

namespace GLhf
{

    class PhysicsWorld
    {
    public:
        PhysicsWorld() {}
        void Create(std::vector<Object>& objects) {
            objects_ = &objects;
        }
        
        void Update(float dt)
        {
            for (Object object : *objects_)
            {
                // Compute Dynamics
                object.force_    += object.mass_ * G;
                object.velocity_ += dt * object.force_ / object.mass_;
                object.position_ += dt * object.velocity_;

                // Reset force
                object.force_.x = 0.0f;
                object.force_.y = 0.0f;
                object.force_.z = 0.0f;
            }
        }

    private:
        std::vector<Object>* objects_;
    };

}