#include "Quad.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void Quad::Init()
{
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

    vbo = VertexBuffer(vertices, sizeof(vertices));
    vao = VertexArray(0, 3);
    ebo = ElementBuffer(indices, sizeof(indices));

    // Projection Matrix
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    // Model View Matrix
    modelView = glm::mat4(1.0f);
    modelView = glm::translate(modelView, glm::vec3(0.0f, 0.0f, -4.0f)); // Camera
}

void Quad::Destroy()
{
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
    ebo.Destroy();
}

void Quad::Draw(double ct)
{
    // Set uniforms
    // ------------
    shader.Bind(); // Use shader program
    shader.SetUniform("modelView", modelView);
    shader.SetUniform("projection", projection);

    // Draw Call
    // ---------
    vao.Bind();
    ebo.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Quad::ModelViewTranslatation(glm::vec3 vec)
{
    // Declaration
    modelView = glm::mat4(1.0f);

    // Camera
    modelView = glm::translate(modelView, glm::vec3(0.0f, 0.0f, -4.0f));

    // Translation by pos
    modelView = glm::translate(modelView, vec);
}
