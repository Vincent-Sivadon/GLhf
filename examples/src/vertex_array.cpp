/* Supposed to print a orange triangle on a green background */

#include "../include/GLhf.h"

#include <iostream>

class VAOTest : public GLhf::App
{
public:
    void Startup() override
    {
        shader.Create("data_triangle.vs", "data_triangle.fs");

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};

        unsigned int vbo;

        glGenBuffers(1, &vbo);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        vao.Create(0, 3);
    }

    void Render(double time) override
    {
        static const GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, green);

        shader.Bind();
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Shutdown() override
    {
        shader.Destroy();
        vao.Destroy();
    }

private:
    GLhf::Shader shader;
    GLhf::VertexArray vao;
};

DECLARE_MAIN(VAOTest);