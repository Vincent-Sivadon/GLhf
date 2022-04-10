#include "VertexArray.h"

#include <stdio.h>

VertexArray::VertexArray(int location, int count)
{
    glGenVertexArrays(1, &this->ID);
    glBindVertexArray(ID);

    glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, count * sizeof(float), (void *)0);
    glEnableVertexAttribArray(location);
}

void VertexArray::Bind()
{
    glBindVertexArray(ID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::Destroy()
{
    glDeleteVertexArrays(1, &ID);
}