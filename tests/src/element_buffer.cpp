/* Supposed to print a orange quad on a green background */

#include "../include/GLtemplate.h"

#include <iostream>

class EBOTest : public App
{
public:
    void startup() override
    {
        shader = Shader("../tests/shaders/data_triangle.vs", "../tests/shaders/data_triangle.fs");

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
    }

    void render(double time) override
    {
        static const GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, green);

        shader.bind();
        vao.bind();
        ebo.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void processInput()
    {
        // exit(0);
    }

    void shutdown() override
    {
        shader.destroy();
        vao.destroy();
        vbo.destroy();
        ebo.destroy();
    }

private:
    Shader shader;
    VertexArray vao;
    VertexBuffer vbo;
    ElementBuffer ebo;
};

DECLARE_MAIN(EBOTest);