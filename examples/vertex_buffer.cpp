/* Supposed to print a orange triangle on a green background */

#include <GLhf/GLhf.h>

#include <iostream>

class VBOTest : public GLhf::App
{
public:
    void Startup() override
    {
        shader.Create("../tests/shaders/data_triangle.vs", "../tests/shaders/data_triangle.fs");

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};

        vbo.Create(vertices, sizeof(vertices));
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
    GLhf::VertexBuffer vbo;
};

DECLARE_MAIN(VBOTest);