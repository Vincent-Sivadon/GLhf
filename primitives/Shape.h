/* */

#pragma once

#include "GLtemplate.h"

#include <cstring>
#include <string>

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

    int verticesSize;
    int indicesSize;

public:
    virtual ~Shape() = default;

    char vertexShaderPath[100] = "/usr/local/share/GLtemplate/shape.vs";
    char fragmentShaderPath[100] = "/usr/local/share/GLtemplate/shape.fs";

    // Properties
    glm::vec3 pos;
    glm::vec3 color{1.0f, 1.0f, 1.0f};
    float angle = 0.0f;
    float width = 1.0f;
    float height = 1.0f;

    virtual GLfloat *CreateVertices() = 0;
    virtual GLuint *CreateIndices() = 0;

    void Create();
    void Destroy();

    void Draw();

    void SetModel(const glm::mat4 &mat);
    void SetView(const glm::mat4 &mat);
    void SetProjection(const glm::mat4 &proj);

    void SetPosition(glm::vec3 position);
    void SetPosition(float x, float y, float z);
    void SetPosition(float x, float y);

    void SetColor(float r, float g, float b);

    void SetShaderNames(std::string vertexShaderName, std::string fragmentShaderName);
};

void Shape::Create()
{
    GLfloat *vertices = CreateVertices();
    GLuint *indices = CreateIndices();

    shader = Shader(vertexShaderPath, fragmentShaderPath);

    // Buffers
    vbo = VertexBuffer(vertices, verticesSize);
    vao = VertexArray(0, 3);
    ebo = ElementBuffer(indices, indicesSize);

    // Projection Matrix
    SetProjection(glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 0.1f, 100.0f));

    // Model Matrix
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));
    SetModel(model);

    // View matrix
    SetView(glm::mat4(1.0f));

    // Color
    SetColor(color.x, color.y, color.z);
}

void Shape::Destroy()
{
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
    ebo.Destroy();
}

void Shape::Draw()
{
    shader.Bind();
    vao.Bind();
    ebo.Bind();
    glDrawElements(GL_TRIANGLES, indicesSize / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

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

void Shape::SetShaderNames(std::string vertexShaderName, std::string fragmentShaderName)
{
    std::string dirPath = "/usr/local/share/GLtemplate/";

    std::string newVertexPath = dirPath + vertexShaderName;
    strcpy(vertexShaderPath, newVertexPath.c_str());

    std::string newFragmentPath = dirPath + fragmentShaderName;
    strcpy(fragmentShaderPath, newFragmentPath.c_str());
}