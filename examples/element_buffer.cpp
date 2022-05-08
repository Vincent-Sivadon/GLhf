/* Supposed to print a orange quad on a green background */

#include <GLhf/GLhf.h>

#include <iostream>

class EBOTest : public GLhf::App
{
public:
    void Startup() override
    {
        shader.Create("../tests/shaders/data_triangle.vs", "../tests/shaders/data_triangle.fs");

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

        vbo.Create(vertices, sizeof(vertices));
        vao.Create(0, 3);
        ebo.Create(indices, sizeof(indices));
    }

    void Render(double time) override
    {
        static const GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, green);

        shader.Bind();
        vao.Bind();
        ebo.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void Shutdown() override
    {
        shader.Destroy();
        vao.Destroy();
        vbo.Destroy();
        ebo.Destroy();
    }

private:
    GLhf::Shader shader;
    GLhf::VertexArray vao;
    GLhf::VertexBuffer vbo;
    GLhf::ElementBuffer ebo;
};

DECLARE_MAIN(EBOTest);