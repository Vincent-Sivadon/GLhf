#pragma once

#include <glad/glad.h>

class IndexBuffer
{
private:
    // Every OpenGL object will have an ID (name)
    GLuint ID;
    GLuint count;

public:
    IndexBuffer(const GLuint *data, GLuint count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    // Getter
    inline GLuint GetCount() const { return count; };
};