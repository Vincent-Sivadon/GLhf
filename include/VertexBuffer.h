/* Vertex Buffer Abstraction */

#pragma once

#include <GL/glew.h>

namespace GLhf
{

    class VertexBuffer
    {
    public:
        // Every OpenGL object will have an ID (name)
        GLuint id_;
        GLuint size_;

        VertexBuffer() {}
        ~VertexBuffer() {}
        void Create(const void *data, GLuint size);

        void UpdateData(const void *data, GLuint size);

        void Bind() const;
        void Unbind() const;

        inline GLuint Size() const { return size_; }

        void Destroy();
    };

}