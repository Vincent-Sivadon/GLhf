#include "Quad.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void Quad::Init(App *application)
{
    // Define the application context
    app = application;

    shader = Shader("/usr/local/share/GLtemplate/quad.vs", "/usr/local/share/GLtemplate/quad.fs");

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
    SetProjection(glm::perspective(glm::radians(45.0f), (float)app->WIDTH / (float)app->HEIGHT, 0.1f, 100.0f));

    // Model Matrix
    SetModel(glm::mat4(1.0f));

    // View matrix
    SetView(glm::mat4(1.0f));
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

void Quad::SetModel(const glm::mat4 &mat)
{
    shader.Bind(); // Use shader program
    model = mat;
    shader.SetUniform("model", model);
}

void Quad::SetView(const glm::mat4 &mat)
{
    shader.Bind(); // Use shader program
    view = mat;
    shader.SetUniform("view", view);
}

void Quad::SetProjection(const glm::mat4 &proj)
{
    shader.Bind();
    projection = proj;
    shader.SetUniform("projection", projection);
}