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
        VertexArray(int location, int count);
        VertexArray(int location, int count, int location2, int count2);
        ~VertexArray() {}

        void Bind();
        void Unbind();

        void Destroy();
    };

}
