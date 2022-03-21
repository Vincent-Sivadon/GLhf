/* Supposed to print a blue triangle on a green background */

#include "../include/GLtemplate.h"

#include <iostream>

class ShaderTest : public App
{
public:
    void startup() override
    {
        shader = Shader("../tests/shaders/triangle.vs", "../tests/shaders/triangle.fs");

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    void render(double time) override
    {
        static const GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, green);

        shader.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void processInput()
    {
        exit(0);
    }

    void shutdown() override
    {
        shader.destroy();
        glDeleteVertexArrays(1, &vao);
    }

private:
    Shader shader;
    GLuint vao;
};

DECLARE_MAIN(ShaderTest);