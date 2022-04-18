#pragma once

#include "Shape.h"

#include "Shader.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include <math.h>

/* ************************* INSTANCED SHAPE CLASS ************************* */
class InstancedShape : public Shape
{
protected:
    VertexBuffer instancedVBO;

public:
    // Nb of instances
    int N;
    float *height;
    float *width;
    float *angle;

    // To define model matrices
    glm::vec2 *positions;

    virtual GLfloat *CreateVertices() = 0;
    virtual GLuint *CreateIndices() = 0;

    void Create() override;
    void Destroy() override;

    void Draw() override;
};
/* ************************************************************************ */