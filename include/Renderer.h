#pragma once

#include "Cube.h"
#include "Scene.h"

namespace GLhf
{

    class Renderer
    {
    private:

    public:
        Renderer() {}
        
        void Init(const Scene& scene)
        {
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1800.0f / 950.0f, 0.1f, 400.0f);
            for(auto& cube : scene.Cubes_)
                cube.SetProjection(projection);
        }

        void Draw(const Cube& cube)
        {
            cube.Bind();
            // glDrawElements(GL_TRIANGLES, ElementsSize / sizeof(GLuint), GL_UNSIGNED_INT, 0);
            // glDrawElements(GL_TRIANGLES, cube.ElementsBuffer_.Size(), GL_UNSIGNED_INT, 0);
        }
    }


}