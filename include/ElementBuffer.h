#pragma once

#include <glad/glad.h>

class ElementBuffer
{
private:
    // Every OpenGL object will have an ID (name)
    GLuint ID;
    GLuint count;

public:
    ElementBuffer() {}
    ElementBuffer(const GLuint *data, GLuint count);
    ~ElementBuffer() {}

    void bind() const;
    void unbind() const;

    void destroy();

    // Getter
    inline GLuint getCount() const { return count; };
};