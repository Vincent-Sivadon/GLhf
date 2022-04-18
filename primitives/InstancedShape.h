/* Instancing Shape : one model will be stored in GPU, but N instances will be drawn */

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
    glm::mat4 *modelMatrices;

    // Shaders (override Shape members)
    char vertexShaderPath[100] = "/usr/local/share/GLtemplate/instanced_shape.vs";
    char fragmentShaderPath[100] = "/usr/local/share/GLtemplate/shape.fs";

    virtual GLfloat *CreateVertices() = 0;
    virtual GLuint *CreateIndices() = 0;

    virtual void SetDefaultProperties() = 0;

    void Create() override;
    void Destroy() override;

    void Draw() override;

    void SetShaderNames(std::string vertexShaderName, std::string fragmentShaderName) override;
};

/* ************************************************************************ */