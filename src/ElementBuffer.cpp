#include "ElementBuffer.h"

namespace GLhf
{

    void ElementBuffer::Create(const GLuint *data, GLuint size)
    {
        glGenBuffers(1, &id_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        size_ = size;
    }

    void ElementBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    }

    void ElementBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void ElementBuffer::Destroy()
    {
        glDeleteBuffers(1, &id_);
    }

}