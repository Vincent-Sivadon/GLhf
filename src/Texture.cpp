#include <iostream>

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Constructor (sets default texture modes)
Texture2D::Texture2D()
    : width(0), height(0),
      internalFormat(GL_RGB), imageFormat(GL_RGB),
      wrapS(GL_REPEAT), wrapT(GL_REPEAT),
      filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
}

// Generates texture from image data
void Texture2D::Create(GLuint w, GLuint h, const GLubyte *data)
{
    // Redefine dimensions
    width = w;
    height = h;

    // Create texture
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
                 width, height,
                 0, imageFormat, GL_UNSIGNED_BYTE, data);

    // Set texture wraping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Create(const char *image_path)
{
    // Redefine dimensions
    int nbr_channels;
    GLubyte *data = stbi_load(image_path, &width, &height, &nbr_channels, 0);

    // Create texture
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // Set texture wraping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

void Texture2D::Update(const GLubyte *data)
{
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
}

// Binds the texture as the current active GL_TEXTURE_2D texture object
void Texture2D::Bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

// Binds the texture as the current active GL_TEXTURE_2D texture object
void Texture2D::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}