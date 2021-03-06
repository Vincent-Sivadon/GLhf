/* Instancing Shape : one model will be stored in GPU, but N instances will be drawn */

#include "InstancedShape.h"

#include <GLFW/glfw3.h>
#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GLhf 
{

    void InstancedShape::Create()
    {
        if (N <= 0)
            throw "Trying to create InstancedShape with N<=0";

        SetDefaultProperties();

        shader.Create(vertexShaderPath, fragmentShaderPath);

        GLfloat *coords, *texcoords;
        CreateVertices(&coords, &texcoords);
        GLuint *elements = CreateElements();

        // Model Matrix
        modelMatrices = new glm::mat4[N];
        for (int i = 0; i < N; i++)
        {
            modelMatrices[i] = glm::mat4(1.0f);
            modelMatrices[i] = glm::translate(modelMatrices[i], glm::vec3(positions[i], 0.0f));
            modelMatrices[i] = glm::rotate(modelMatrices[i], angle[i], glm::vec3(0.0f, 0.0f, -1.0f));
            modelMatrices[i] = glm::scale(modelMatrices[i], glm::vec3(width[i], height[i], 1.0f));
        }

        // Vertex Buffers
        CoordsBuffer.Create(coords, CoordsSize);
        TexCoordsBuffer.Create(texcoords, TexCoordsSize);
        instancedVBO.Create(modelMatrices, N * sizeof(glm::mat4));
        // Vertex Array
        VAO.Create(CoordsBuffer, TexCoordsBuffer);

        instancedVBO.Bind();
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)0);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(3 * sizeof(glm::vec4)));

        // tell OpenGL this is an instanced vertex attribute.
        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);

        // Element buffer
        ElementsBuffer.Create(elements, ElementsSize);

        // Projection Matrix
        SetProjection(glm::perspective(glm::radians(45.0f), 1800.0f / 950.0f, 0.1f, 1000.0f));

        // View matrix
        SetView(glm::mat4(1.0f));

        // Color
        SetColor(color.x, color.y, color.z);

        delete coords;
        delete elements;
    }

    void InstancedShape::UpdateModelMatrices()
    {
        // Model Matrix
        for (int i = 0; i < N; i++)
        {
            modelMatrices[i] = glm::mat4(1.0f);
            modelMatrices[i] = glm::translate(modelMatrices[i], glm::vec3(positions[i], 0.0f));
            modelMatrices[i] = glm::rotate(modelMatrices[i], angle[i], glm::vec3(0.0f, 0.0f, -1.0f));
            modelMatrices[i] = glm::scale(modelMatrices[i], glm::vec3(width[i], height[i], 1.0f));
        }

        instancedVBO.UpdateData(modelMatrices, N * sizeof(glm::mat4));
    }


    void InstancedShape::Destroy()
    {
        shader.Destroy();
        VAO.Destroy();
        CoordsBuffer.Destroy();
        instancedVBO.Destroy();
        ElementsBuffer.Destroy();

        delete positions;
        delete width;
        delete height;
        delete angle;
        delete modelMatrices;
    }

    void InstancedShape::Draw()
    {
        shader.Bind();
        VAO.Bind();
        ElementsBuffer.Bind();
        glDrawElementsInstanced(GL_TRIANGLES, ElementsSize / sizeof(GLuint), GL_UNSIGNED_INT, 0, N);
    }

    void InstancedShape::SetShaderNames(const std::string vertexShaderName, const std::string fragmentShaderName)
    {
        strcpy(vertexShaderPath, vertexShaderName.c_str());
        strcpy(fragmentShaderPath, fragmentShaderName.c_str());
    }

    void InstancedShape::SetDimensions(float w, float h)
    {
        if (width != nullptr)
            throw "InstancedShape.width already assigned";
        if (height != nullptr)
            throw "InstancedShape.height already assigned";

        width = new float[N];
        for (int i = 0; i < N; i++)
            width[i] = w;

        height = new float[N];
        for (int i = 0; i < N; i++)
            height[i] = h;
    }

}