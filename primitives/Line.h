/* Line primitive */

#pragma once

#include "GLtemplate.h"

class Line
{
private:
    Shader shader;
    VertexBuffer vbo;
    VertexArray vao;

    glm::mat4 projection;
    glm::mat4 modelView;

    glm::vec3 color;

    App *app;

public:
    void Init(App *application, float x1, float y1, float x2, float y2);
    void Destroy();

    void SetModelView(glm::mat4 mv);
    void SetProjection(glm::mat4 proj);
    void SetColor(float r, float g, float b);

    glm::vec3 getColor() { return color; }

    void Draw();
};