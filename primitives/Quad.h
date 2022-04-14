#pragma once

#include "GLtemplate.h"

class Quad
{
private:
    Shader shader;
    VertexArray vao;
    VertexBuffer vbo;
    ElementBuffer ebo;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    App *app;

public:
    void Init(App *application);
    void Destroy();

    void Draw();

    void SetModel(const glm::mat4 &mat);
    void SetView(const glm::mat4 &mat);
    void SetProjection(const glm::mat4 &proj);

    float GetViewX() { return view[0][0]; }
};