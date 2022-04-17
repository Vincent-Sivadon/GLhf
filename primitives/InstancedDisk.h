#pragma once

#include "Shape.h"

#include <math.h>

class InstancedDisk : public Shape
{
private:
    VertexBuffer instancedVBO;

public:
    int N;
    int numberOfTriangles = 30;

    glm::vec2 *positions;

    float radius = 1.0f;

    void Create() override;
    void Destroy() override;

    void Draw() override;

    void CreateVertices(GLfloat *&vertices, GLuint *&indices);
};

void InstancedDisk::Create()
{
    assert(N > 0);
    assert(positions != nullptr);

    shader = Shader(vertexShaderPath, fragmentShaderPath);

    GLfloat *vertices;
    GLuint *indices;
    CreateVertices(vertices, indices);

    // Model Matrix
    glm::mat4 modelMatrices[N];
    for (int i = 0; i < N; i++)
    {
        modelMatrices[i] = glm::mat4(1.0f);
        modelMatrices[i] = glm::translate(modelMatrices[i], glm::vec3(positions[i], 0.0f));
        modelMatrices[i] = glm::scale(modelMatrices[i], glm::vec3(radius, radius, 1.0f));
        modelMatrices[i] = glm::rotate(modelMatrices[i], angle, glm::vec3(0.0f, 0.0f, -1.0f));
    }

    // Vertex Buffers
    vbo = VertexBuffer(vertices, 3 * (numberOfTriangles + 1) * sizeof(GLfloat));
    instancedVBO = VertexBuffer(modelMatrices, N * sizeof(glm::mat4));

    // Vertex Array
    vbo.Bind();
    vao = VertexArray(0, 3);

    instancedVBO.Bind();
    // glBindBuffer(GL_ARRAY_BUFFER, instancedVBO.ID); // this attribute comes from a different vertex buffer
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
    ebo = ElementBuffer(indices, 3 * numberOfTriangles * sizeof(GLuint));

    // Projection Matrix
    SetProjection(glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 0.1f, 100.0f));

    // View matrix
    SetView(glm::mat4(1.0f));

    // Color
    SetColor(color.x, color.y, color.z);

    delete positions;
}

void InstancedDisk::Destroy()
{
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
    instancedVBO.Destroy();
    ebo.Destroy();
}

void InstancedDisk::Draw()
{
    shader.Bind();
    vao.Bind();
    ebo.Bind();
    glDrawElementsInstanced(GL_TRIANGLES, 3 * numberOfTriangles, GL_UNSIGNED_INT, 0, N);
}

void InstancedDisk::CreateVertices(GLfloat *&vertices, GLuint *&indices)
{
    // Properties
    float delta = 2 * M_PI / numberOfTriangles;

    // Allocation
    vertices = new GLfloat[(numberOfTriangles + 1) * 3]; // N + 1 points à 3 coords
    indices = new GLuint[numberOfTriangles * 3];         // N triangles à 3 points

    // Middle point
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    // Indices indices
    unsigned int p = 2, q = 1;

    for (int triangleID = 0; triangleID < numberOfTriangles; triangleID++)
    {
        vertices[3 * (triangleID + 1)] = cos((float)triangleID * delta);     // x coordinate
        vertices[3 * (triangleID + 1) + 1] = sin((float)triangleID * delta); // y coordinate
        vertices[3 * (triangleID + 1) + 2] = 0.0f;                           // z coordinate

        if (p == numberOfTriangles + 1)
            p = 1;
        indices[3 * triangleID] = 0;
        indices[3 * triangleID + 1] = p;
        indices[3 * triangleID + 2] = q;

        p++;
        q++;
    }
}
