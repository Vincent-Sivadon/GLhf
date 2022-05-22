/* Vertex Array Abstraction */

#pragma once

#include <GL/glew.h>

#include "VertexBuffer.h"

namespace GLhf
{

    class VertexArray
    {
    private:
        GLuint id_;

    public:
        VertexArray() {}
        ~VertexArray() {}
        void Create(int location, int count);
        void Create(int location, int count, int location2, int count2);
        void Create(const VertexBuffer& coords_buffer);
        void Create(const VertexBuffer& coords_buffer, const VertexBuffer& tex_buffer);
        void Create(const VertexBuffer& coords_buffer,
                    const VertexBuffer& texcoords_buffer,
                    const VertexBuffer& normals_buffer);

        void Bind() const;
        void Unbind() const;

        void Destroy();
    };

}
