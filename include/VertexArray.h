/* Vertex Array Abstraction */

#pragma once

#include <GL/glew.h>

#include "VertexBuffer.h"

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
        void Create(const VertexBuffer& coords_buffer, const VertexBuffer& tex_buffer);

        void Bind();
        void Unbind();

        void Destroy();
    };

}
