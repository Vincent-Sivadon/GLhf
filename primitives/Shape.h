/* */

#pragma once

#include "GLtemplate.h"

class Shape
{
protected:
    Shader shader;
    VertexArray vao;
    VertexBuffer vbo;
    ElementBuffer ebo;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

public:
    virtual ~Shape() = default;

    glm::vec3 pos;
    glm::vec3 color;
    float angle = 0.0f;

    virtual void Create(int winWidth, int winHeight) = 0;
    virtual void Destroy() = 0;

    virtual void Draw() = 0;

    void SetModel(const glm::mat4 &mat);
    void SetView(const glm::mat4 &mat);
    void SetProjection(const glm::mat4 &proj);

    void SetPosition(glm::vec3 position);
    void SetPosition(float x, float y, float z);
    void SetPosition(float x, float y);

    void SetColor(float r, float g, float b);
};

void Shape::SetModel(const glm::mat4 &mat)
{
    shader.Bind(); // Use shader program
    model = mat;
    shader.SetUniform("model", model);
}

void Shape::SetView(const glm::mat4 &mat)
{
    shader.Bind(); // Use shader program
    view = mat;
    shader.SetUniform("view", view);
}

void Shape::SetProjection(const glm::mat4 &proj)
{
    shader.Bind();
    projection = proj;
    shader.SetUniform("projection", projection);
}

void Shape::SetPosition(glm::vec3 position)
{
    pos = position;
    model = glm::translate(model, pos);
}

void Shape::SetPosition(float x, float y, float z)
{
    pos = glm::vec3(x, y, z);
    model = glm::translate(model, pos);
}

void Shape::SetPosition(float x, float y)
{
    pos = glm::vec3(x, y, 0.0f);
    model = glm::translate(model, pos);
    SetModel(model);
}

void Shape::SetColor(float r, float g, float b)
{
    color = glm::vec3(r, g, b);
    shader.Bind();
    shader.SetUniform("color", color);
}