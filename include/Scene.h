#pragma once

#include "Cube.h"
#include "Camera.h"

#include <vector>

namespace GLhf
{

    class Scene
    {
    public:
        Camera Camera_;
        std::vector<Cube> Cubes_;
    }


}