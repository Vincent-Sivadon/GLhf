/* Element Buffer Abstraction */

#pragma once

#include <glad/glad.h>

namespace GLhf
{

    class ElementBuffer
    {
    private:
        // Every OpenGL object will have an ID (name)
        GLuint ID;
        GLuint count;

    public:
        ElementBuffer() {}
        ~ElementBuffer() {}
        void Create(const GLuint *data, GLuint count);

        void Bind() const;
        void Unbind() const;

        void Destroy();

        // Getter
        inline GLuint GetCount() const { return count; };
    };

}