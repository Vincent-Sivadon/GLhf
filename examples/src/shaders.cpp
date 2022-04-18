/* Supposed to print a blue triangle on a green background */

#include "../include/GLtemplate.h"

#include <iostream>

class ShaderTest : public App
{
public:
    void Startup() override
    {
        shader = Shader("../tests/shaders/triangle.vs", "../tests/shaders/triangle.fs");

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    void Render(double time) override
    {
        static const GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, green);

        shader.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Shutdown() override
    {
        shader.Destroy();
        glDeleteVertexArrays(1, &vao);
    }

private:
    Shader shader;
    GLuint vao;
};

DECLARE_MAIN(ShaderTest);