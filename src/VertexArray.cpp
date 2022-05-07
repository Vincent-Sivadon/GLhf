#include "VertexArray.h"

#include <stdio.h>

namespace GLhf
{

    VertexArray::VertexArray(int location, int count)
    {
        glGenVertexArrays(1, &this->ID);
        glBindVertexArray(ID);

        glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, count * sizeof(float), (void *)0);
        glEnableVertexAttribArray(location);
    }

    VertexArray::VertexArray(int location, int count, int location2, int count2)
    {
        glGenVertexArrays(1, &this->ID);
        glBindVertexArray(ID);

        glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, (count + count2) * sizeof(float), (void *)0);
        glEnableVertexAttribArray(location);

        glVertexAttribPointer(location2, count2, GL_FLOAT, GL_FALSE, (count + count2) * sizeof(float), (void *)(count * sizeof(float)));
        glEnableVertexAttribArray(location2);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(ID);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArray::Destroy()
    {
        glDeleteVertexArrays(1, &ID);
    }

}