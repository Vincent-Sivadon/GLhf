#include "VertexBuffer.h"

#include <stdio.h>

namespace GLhf
{

    void VertexBuffer::Create(const void *data, GLuint size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void VertexBuffer::UpdateData(const void *data, GLuint size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }


    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Destroy()
    {
        glDeleteBuffers(1, &ID);
    }

}