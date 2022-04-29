/* Example of the basic structure
 * to see the output, executes the binary
 * independantly from ctest */

#include "../include/GLtemplate.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class TextureExample : public App
{
public:
    void Startup() override
    {
        std::cout << "============================== Startup ==============================\n";

        int wi, he, nbr_channels;
        unsigned char *data = stbi_load("../resources/minion.jpg", &wi, &he, &nbr_channels, 0);
        texture.Create(wi, he, data);
        stbi_image_free(data);

        // Texture Quad
        static const GLfloat vertices[] = {
            // positions             // texture coords
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // top left
        };

        static const GLuint indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        shader = Shader("texture.vs", "texture.fs");
        vbo = VertexBuffer(vertices, sizeof(vertices));
        vao = VertexArray(0, 3, 1, 2);
        ebo = ElementBuffer(indices, sizeof(indices));
    }

    void Render(double time) override
    {
        texture.Bind();
        shader.Bind();
        vao.Bind();
        ebo.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

private:
    Shader shader;
    Texture2D texture;
    VertexArray vao;
    VertexBuffer vbo;
    ElementBuffer ebo;
};

DECLARE_MAIN(TextureExample);