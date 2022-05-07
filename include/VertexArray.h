/* Vertex Array Abstraction */

#pragma once

#include <glad/glad.h>

namespace GLhf
{

    class VertexArray
    {
    private:
        GLuint ID;

    public:
        VertexArray() {}
        ~VertexArray() {}
        void Create(int location, int count);
        void Create(int location, int count, int location2, int count2);

        void Bind();
        void Unbind();

        void Destroy();
    };

}
