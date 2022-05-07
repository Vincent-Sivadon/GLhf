#include "ElementBuffer.h"

namespace GLhf
{

    ElementBuffer::ElementBuffer(const GLuint *data, GLuint count)
        : count(count)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
    }

    void ElementBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    void ElementBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void ElementBuffer::Destroy()
    {
        glDeleteBuffers(1, &ID);
    }
    
}