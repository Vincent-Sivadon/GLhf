#include "VertexBuffer.h"

#include <stdio.h>

VertexBuffer::VertexBuffer(const void *data, GLuint size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
    printf("vao id : %u\n", ID);

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