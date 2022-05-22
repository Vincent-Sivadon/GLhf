#pragma once

#include "Cube.h"
#include "Camera.h"

#include <vector>

namespace GLhf
{

    class Scene
    {
    public:
        std::vector<Cube> cubes_;

        void AddCube(const Cube& cube)
        {
            cubes_.push_back(cube);
        }

    };


}