#pragma once

#include "Shape.h"

#include <math.h>

class InstancedDisk : public Shape
{
private:
    VertexBuffer instancedVBO;

public:
    int N;
    glm::vec2 *positions;

    // char vertexShaderPath[100] = "/usr/local/share/GLtemplate/instanced_shape.vs";

    float radius = 1.0f;

    void Create() override;
    void Destroy() override;

    void Draw() override;
};

void InstancedDisk::Create()
{
    assert(N > 0);
    assert(positions != nullptr);

    shader = Shader(vertexShaderPath, fragmentShaderPath);

    // Vertices
    static const GLfloat vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.707107f, -0.707107, 0.0f,
        0.0f, -1.0f, 0.0f,
        -0.707107, -0.707107, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -0.707107, 0.707107, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.707107, 0.707107, 0.0f};

    static const GLuint indices[] = {
        0, 2, 1,
        0, 3, 2,
        0, 4, 3,
        0, 5, 4,
        0, 6, 5,
        0, 7, 6,
        0, 8, 7,
        0, 1, 8};

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
    vbo = VertexBuffer(vertices, sizeof(vertices));
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
    ebo = ElementBuffer(indices, sizeof(indices));

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
    glDrawElementsInstanced(GL_TRIANGLES, 3 * 8, GL_UNSIGNED_INT, 0, N);
}