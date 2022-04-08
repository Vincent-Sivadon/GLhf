#pragma once

#include <glad/glad.h>

class VertexArray
{
private:
    GLuint ID;

public:
    VertexArray() {}
    VertexArray(int location, int count);
    ~VertexArray() {}

    void bind();
    void unbind();

    void destroy();
};
