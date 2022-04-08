#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(const GLuint *data, GLuint count)
    : count(count)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

void ElementBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ElementBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::destroy()
{
    glDeleteBuffers(1, &ID);
}