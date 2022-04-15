#pragma once

#include "Shape.h"

class Quad : public Shape
{
public:
    float width = 1.0f, height = 1.0f;

    void Create(int winWidth, int winHeight) override;
    void Destroy() override;

    void Draw() override;
};

void Quad::Create(int winWidth, int winHeight)
{
    shader = Shader("/usr/local/share/GLtemplate/shape.vs", "/usr/local/share/GLtemplate/shape.fs");

    // Cube vertices
    static const GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };
    GLuint indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Buffers
    vbo = VertexBuffer(vertices, sizeof(vertices));
    vao = VertexArray(0, 3);
    ebo = ElementBuffer(indices, sizeof(indices));

    // Projection Matrix
    SetProjection(glm::perspective(glm::radians(45.0f), (float)winWidth / (float)winHeight, 0.1f, 100.0f));

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

void Quad::Destroy()
{
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
    ebo.Destroy();
}

void Quad::Draw()
{
    shader.Bind();
    vao.Bind();
    ebo.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}