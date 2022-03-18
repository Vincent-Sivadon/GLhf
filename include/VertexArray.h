#pragma once

#include <glad/glad.h>

class VertexArray
{
private:
    GLuint ID;
    GLuint buffer;

public:
    VertexArray(GLuint buffer, int count);
    ~VertexArray();

    void bind();
    void unbind();
};
