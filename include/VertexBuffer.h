#pragma once

#include <glad/glad.h>

class VertexBuffer
{
private:
    // Every OpenGL object will have an ID (name)
    GLuint ID;

public:
    VertexBuffer() {}
    VertexBuffer(const void *data, GLuint size);
    ~VertexBuffer() {}

    void bind() const;
    void unbind() const;

    void destroy();
};