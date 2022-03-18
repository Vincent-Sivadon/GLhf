#pragma once

#include <glad/glad.h>

class VertexBuffer
{
private:
    // Every OpenGL object will have an ID (name)
    GLuint ID;

public:
    VertexBuffer(const void *data, GLuint size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};