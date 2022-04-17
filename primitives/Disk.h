#pragma once

#include "Shape.h"

#include <math.h>
#include <string>

class Disk : public Shape
{
public:
    float radius = 1.0f;

    void Create() override;
    void Destroy() override;

    void Draw() override;
};

void Disk::Create()
{
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

    // Buffers
    vbo = VertexBuffer(vertices, sizeof(vertices));
    vao = VertexArray(0, 3);
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
}

void Disk::Destroy()
{
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
    ebo.Destroy();
}

void Disk::Draw()
{
    shader.Bind();
    vao.Bind();
    ebo.Bind();
    glDrawElements(GL_TRIANGLES, 3 * 8, GL_UNSIGNED_INT, 0);
}