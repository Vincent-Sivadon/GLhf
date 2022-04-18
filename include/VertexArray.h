/* Vertex Array Abstraction */

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

    void Bind();
    void Unbind();

    void Destroy();
};
