/* */

#pragma once

#include "Shader.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include <cstring>
#include <string>

/* ************************* SHAPE CLASS ************************* */
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

    virtual void Create();
    virtual void Destroy();

    virtual void Draw();

    void SetModel(const glm::mat4 &mat);
    void SetView(const glm::mat4 &mat);
    void SetProjection(const glm::mat4 &proj);

    void SetPosition(glm::vec3 position);
    void SetPosition(float x, float y, float z);
    void SetPosition(float x, float y);

    void SetColor(float r, float g, float b);

    virtual void SetShaderNames(std::string vertexShaderName, std::string fragmentShaderName);
};
/* ***************************************************************** */
