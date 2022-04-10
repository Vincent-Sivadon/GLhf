#pragma once

#include "GLtemplate.h"

class Quad
{
private:
    Shader shader;
    VertexArray vao;
    VertexBuffer vbo;
    ElementBuffer ebo;

    glm::mat4 projection;
    glm::mat4 modelView;

public:
    void Init();
    void Destroy();

    void Draw(double ct);

    void ModelViewTranslatation(glm::vec3 vec);
};