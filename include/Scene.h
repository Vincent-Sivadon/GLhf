#pragma once

#include "Cube.h"
#include "InstanceCube.h"
#include "Camera.h"

#include <vector>

namespace GLhf
{

    class Scene
    {
    public:
        std::vector<Cube> cubes_;
        std::vector<InstanceCube> instance_cubes_;

        void Add(const Cube& cube)
        {
            cubes_.push_back(cube);
        }

        void Add(const InstanceCube& instance_cube)
        {
            instance_cubes_.push_back(instance_cube);
        }

    };


}