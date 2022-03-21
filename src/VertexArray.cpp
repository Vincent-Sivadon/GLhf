#include "VertexArray.h"

VertexArray::VertexArray(GLuint buffer, int count)
{
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);

    glVertexAttribPointer(ID, count, GL_FLOAT, GL_FALSE, count * sizeof(float), (void *)0);
    glEnableVertexAttribArray(ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::bind()
{
    glBindVertexArray(ID);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}
