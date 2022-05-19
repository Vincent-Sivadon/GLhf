/* Instancing Shape : one model will be stored in GPU, but N instances will be drawn */

#pragma once

#include "Shape.h"

#include "Shader.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include <math.h>

namespace GLhf 
{

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
        char vertexShaderPath[100] = "instanced_shape.vs";
        char fragmentShaderPath[100] = "shape.fs";

        void CreateVertices(GLfloat **coords, GLfloat **texcoords) = 0;
        void CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **normals) = 0;
        GLuint *CreateElements() = 0;
        GLfloat *CreateCoords() = 0;
        GLfloat *CreateTexCoords() = 0;
        GLfloat *CreateNormals() = 0;

        virtual void SetDefaultProperties() = 0;
        void SetDimensions(float w, float h);

        void UpdateModelMatrices();

        void Create() override;
        void Destroy() override;

        void Draw() override;

        void SetShaderNames(std::string vertexShaderName, std::string fragmentShaderName) override;
    };

}