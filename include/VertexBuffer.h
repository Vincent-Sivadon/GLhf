#pragma once

#include <glad/glad.h>

class VertexBuffer
{
public:
    // Every OpenGL object will have an ID (name)
    GLuint ID;

    VertexBuffer() {}
    VertexBuffer(const void *data, GLuint size);
    ~VertexBuffer() {}

    void Bind() const;
    void Unbind() const;

    void Destroy();
};