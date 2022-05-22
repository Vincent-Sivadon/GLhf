/* Element Buffer Abstraction */

#pragma once

#include <GL/glew.h>

namespace GLhf
{

    class ElementBuffer
    {
    private:
        // Every OpenGL object will have an ID (name)
        GLuint id_;
        GLuint size_;

    public:
        ElementBuffer() {}
        ~ElementBuffer() {}
        void Create(const GLuint *data, GLuint count);

        void Bind() const;
        void Unbind() const;

        void Destroy();

        // Getter
        inline GLuint Size() const { return size_; }
    };

}