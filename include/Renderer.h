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
        
        void Init(Scene& scene)
        {
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1800.0f / 950.0f, 0.1f, 400.0f);
            for(Cube& cube : scene.cubes_)
                cube.SetProjection(projection);
        }

        void Draw(Cube& cube, const glm::mat4& view_matrix)
        {
            cube.SetView(view_matrix);
            cube.Bind();
            glDrawElements(GL_TRIANGLES, cube.ElementsBufferSize(), GL_UNSIGNED_INT, 0);
        }

        void Clear()
        {
            glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    };


}