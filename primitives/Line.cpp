/* */

#include "Line.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Line::Init(App *application, float x1, float y1, float x2, float y2)
{
    // Defines application context
    app = application;

    // Line color
    color = glm::vec3(1, 1, 1);

    // Coordinates
    modelView = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)app->WIDTH / (float)app->HEIGHT, 0.1f, 100.0f);

    // Shader
    shader = Shader("/usr/local/share/GLtemplate/line.vs", "/usr/local/share/GLtemplate/line.fs");

    // Vertices
    static const GLfloat vertices[] = {
        x1,
        y1,
        0.0f,
        x2,
        y2,
        0.0f};

    // Buffers
    vbo = VertexBuffer(vertices, sizeof(vertices));
    vao = VertexArray(0, 3);
}

void Line::Destroy()
{
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
}

void Line::SetModelView(glm::mat4 mv)
{
    modelView = mv;
}

void Line::SetProjection(glm::mat4 proj)
{
    projection = proj;
}

void Line::SetColor(float r, float g, float b)
{
    color = glm::vec3(r, g, b);
}

void Line::Draw()
{
    shader.Bind();
    shader.SetUniform("modelView", modelView);
    shader.SetUniform("projection", projection);
    shader.SetUniform("color", color);

    vao.Bind();
    glDrawArrays(GL_LINES, 0, 2);
}