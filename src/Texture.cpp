#include <iostream>

#include "Texture.h"

// Constructor (sets default texture modes)
Texture2D::Texture2D()
    : width(0), height(0),
      internalFormat(GL_RGB), imageFormat(GL_RGB),
      wrapS(GL_REPEAT), wrapT(GL_REPEAT),
      filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
    glGenTextures(1, &this->ID);
}

// Generates texture from image data
void Texture2D::Generate(GLuint w, GLuint h, const GLubyte *data)
{
    // Redefine dimensions
    width = w;
    height = h;

    // Create texture
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
                 width, height,
                 0, imageFormat, GL_UNSIGNED_BYTE, data);

    // Set texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Binds the texture as the current active GL_TEXTURE_2D texture object
void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}