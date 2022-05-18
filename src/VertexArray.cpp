#include "VertexArray.h"

#include <stdio.h>

namespace GLhf
{

    void VertexArray::Create(int location, int count)
    {
        glGenVertexArrays(1, &this->ID);
        glBindVertexArray(ID);

        glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, count * sizeof(float), (void *)0);
        glEnableVertexAttribArray(location);
    }

    void VertexArray::Create(int location, int count, int location2, int count2)
    {
        glGenVertexArrays(1, &this->ID);
        glBindVertexArray(ID);

        glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, (count + count2) * sizeof(float), (void *)0);
        glEnableVertexAttribArray(location);

        glVertexAttribPointer(location2, count2, GL_FLOAT, GL_FALSE, (count + count2) * sizeof(float), (void *)(count * sizeof(float)));
        glEnableVertexAttribArray(location2);
    }

    void VertexArray::Create(const VertexBuffer& coords_buffer, const VertexBuffer& texcoords_buffer)
    {
        // Create
        glGenVertexArrays(1, &this->ID);
        glBindVertexArray(this->ID);

        /* Enable 2 shader array attrib location */
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        /* Connect the 2 buffers to independant binding index slots */
        glVertexArrayVertexBuffer(ID, /*slot index*/0, coords_buffer.ID   , /*offset*/ 0, /*stride*/3*sizeof(GLfloat));
        glVertexArrayVertexBuffer(ID, /*slot index*/1, texcoords_buffer.ID, /*offset*/ 0, /*stride*/2*sizeof(GLfloat));

        /* Connect those slots to shader attribute locations */
        glVertexArrayAttribBinding(ID, /*location*/0, /*slot index*/ 0);
        glVertexArrayAttribBinding(ID, /*location*/1, /*slot index*/ 1);
                                
        /* Set the format of the attributes */
        glVertexArrayAttribFormat(ID, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribFormat(ID, 1, 2, GL_FLOAT, GL_FALSE, 0);
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