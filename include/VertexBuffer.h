/* Vertex Buffer Abstraction */

#pragma once

#include <glad/glad.h>

namespace GLhf
{

    class VertexBuffer
    {
    public:
        // Every OpenGL object will have an ID (name)
        GLuint ID;

        VertexBuffer() {}
        ~VertexBuffer() {}
        void Create(const void *data, GLuint size);

        void UpdateData(const void *data, GLuint size);

        void Bind() const;
        void Unbind() const;

        void Destroy();
    };

}