#pragma once

#include "Shape.h"

#include <math.h>

class InstancedDisk : public Shape
{
private:
    VertexBuffer instancedVBO;

public:
    float N;
    glm::vec2 *positions;

    float radius = 1.0f;

    void Create() override;
    void Destroy() override;

    void Draw() override;
};

void InstancedDisk::Create()
{
    assert(N > 0);
    assert(positions != nullptr);

    shader = Shader("/usr/local/share/GLtemplate/instanced_shape.vs", "/usr/local/share/GLtemplate/shape.fs");

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

    // Vertex Buffers
    vbo = VertexBuffer(vertices, sizeof(vertices));
    instancedVBO = VertexBuffer(positions, N * sizeof(glm::vec2));

    // Vertex Array
    vbo.Bind();
    vao = VertexArray(0, 3);

    instancedVBO.Bind();
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, instancedVBO.ID); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1); // tell OpenGL this is an instanced vertex attribute.

    // Element buffer
    ebo = ElementBuffer(indices, sizeof(indices));

    // Projection Matrix
    SetProjection(glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 0.1f, 100.0f));

    // Model Matrix
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, -1.0f));
    model = glm::scale(model, glm::vec3(radius, radius, 1.0f));
    SetModel(model);

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