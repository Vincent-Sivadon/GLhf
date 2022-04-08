/* Supposed to print a orange triangle on a green background */

#include "../include/GLtemplate.h"

#include <iostream>

class VBOTest : public App
{
public:
    void startup() override
    {
        shader = Shader("../tests/shaders/data_triangle.vs", "../tests/shaders/data_triangle.fs");

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};

        vbo = VertexBuffer(vertices, sizeof(vertices));
        vao = VertexArray(0, 3);
    }

    void render(double time) override
    {
        static const GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, green);

        shader.bind();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void processInput()
    {
        // exit(0);
    }

    void shutdown() override
    {
        shader.destroy();
        vao.destroy();
    }

private:
    Shader shader;
    VertexArray vao;
    VertexBuffer vbo;
};

DECLARE_MAIN(VBOTest);