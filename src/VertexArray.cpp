#include "VertexArray.h"

#include <stdio.h>
#include <glm/glm.hpp>

namespace GLhf
{

    void VertexArray::Create(int location, int count)
    {
        glGenVertexArrays(1, &this->id_);
        glBindVertexArray(id_);

        glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, count * sizeof(float), (void *)0);
        glEnableVertexAttribArray(location);
    }

    void VertexArray::Create(int location, int count, int location2, int count2)
    {
        glGenVertexArrays(1, &this->id_);
        glBindVertexArray(id_);

        glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, (count + count2) * sizeof(float), (void *)0);
        glEnableVertexAttribArray(location);

        glVertexAttribPointer(location2, count2, GL_FLOAT, GL_FALSE, (count + count2) * sizeof(float), (void *)(count * sizeof(float)));
        glEnableVertexAttribArray(location2);
    }

    void VertexArray::Create(const VertexBuffer& coord_buffer)
    {
        // Create
        glGenVertexArrays(1, &this->id_);
        glBindVertexArray(this->id_);

        /* Enable shader array attrib location */
        glEnableVertexAttribArray(0);

        /* Connect the buffer to independant binding index slots */
        glVertexArrayVertexBuffer(id_, /*slot index*/0, coord_buffer.id_   , /*offset*/ 0, /*stride*/3*sizeof(GLfloat));

        /* Connect the slot to shader attribute locations */
        glVertexArrayAttribBinding(id_, /*location*/0, /*slot index*/ 0);
                                
        /* Set the format of the attributes */
        glVertexArrayAttribFormat(id_, 0, 3, GL_FLOAT, GL_FALSE, 0);
    }

    void VertexArray::Create(const VertexBuffer& coord_buffer, const VertexBuffer& tex_coord_buffer)
    {
        // Create
        glGenVertexArrays(1, &this->id_);
        glBindVertexArray(this->id_);

        /* Enable 2 shader array attrib location */
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        /* Connect the 2 buffers to independant binding index slots */
        glVertexArrayVertexBuffer(id_, /*slot index*/0, coord_buffer.id_   , /*offset*/ 0, /*stride*/3*sizeof(GLfloat));
        glVertexArrayVertexBuffer(id_, /*slot index*/1, tex_coord_buffer.id_, /*offset*/ 0, /*stride*/2*sizeof(GLfloat));

        /* Connect those slots to shader attribute locations */
        glVertexArrayAttribBinding(id_, /*location*/0, /*slot index*/ 0);
        glVertexArrayAttribBinding(id_, /*location*/1, /*slot index*/ 1);
                                
        /* Set the format of the attributes */
        glVertexArrayAttribFormat(id_, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribFormat(id_, 1, 2, GL_FLOAT, GL_FALSE, 0);
    }

    void VertexArray::Create(const VertexBuffer& coord_buffer,
                             const VertexBuffer& tex_coord_buffer,
                             const VertexBuffer& normal_buffer)
    {
        Create(coord_buffer, tex_coord_buffer);

        glEnableVertexAttribArray(2);

        /* Connect the 3 buffers to independant binding index slots */
        glVertexArrayVertexBuffer(id_, /*slot index*/2, normal_buffer.id_  , /*offset*/ 0, /*stride*/3*sizeof(GLfloat));

        /* Connect those slots to shader attribute locations */
        glVertexArrayAttribBinding(id_, /*location*/2, /*slot index*/ 2);
                                
        /* Set the format of the attributes */
        glVertexArrayAttribFormat(id_, 2, 3, GL_FLOAT, GL_FALSE, 0);
    }
    
    void VertexArray::Create(const VertexBuffer& coord_buffer,
                             const VertexBuffer& tex_coord_buffer,
                             const VertexBuffer& normal_buffer,
                             const VertexBuffer& instance_buffer)
    {
        Create(coord_buffer, tex_coord_buffer, normal_buffer);

        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);

        glVertexArrayVertexBuffer(id_, /*slot*/3, instance_buffer.id_, /*offset*/ 0                  , /*stride*/sizeof(glm::mat4));
        glVertexArrayVertexBuffer(id_, /*slot*/4, instance_buffer.id_, /*offset*/ 1*sizeof(glm::vec4), /*stride*/sizeof(glm::mat4));
        glVertexArrayVertexBuffer(id_, /*slot*/5, instance_buffer.id_, /*offset*/ 2*sizeof(glm::vec4), /*stride*/sizeof(glm::mat4));
        glVertexArrayVertexBuffer(id_, /*slot*/6, instance_buffer.id_, /*offset*/ 3*sizeof(glm::vec4), /*stride*/sizeof(glm::mat4));
        
        glVertexArrayAttribBinding(id_, /*location*/3, /*slot*/ 3);
        glVertexArrayAttribBinding(id_, /*location*/4, /*slot*/ 4);
        glVertexArrayAttribBinding(id_, /*location*/5, /*slot*/ 5);
        glVertexArrayAttribBinding(id_, /*location*/6, /*slot*/ 6);
        
        glVertexArrayAttribFormat(id_, 3, 4, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribFormat(id_, 4, 4, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribFormat(id_, 5, 4, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribFormat(id_, 6, 4, GL_FLOAT, GL_FALSE, 0);

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(id_);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::Destroy()
    {
        glDeleteVertexArrays(1, &id_);
    }

}