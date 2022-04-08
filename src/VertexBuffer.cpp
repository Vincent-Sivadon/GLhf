#include "VertexBuffer.h"

#include <stdio.h>

VertexBuffer::VertexBuffer(const void *data, GLuint size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const
{
    printf("vao id : %u\n", ID);

    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::destroy()
{
    glDeleteBuffers(1, &ID);
}