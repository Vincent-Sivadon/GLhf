#pragma once

#include <Cube.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

namespace GLhf
{

    struct Object {
        // Physics
        glm::vec3 position_;
        glm::vec3 velocity_;
        glm::vec3 force_;
        float mass_;

        Cube *cube;
    };

}