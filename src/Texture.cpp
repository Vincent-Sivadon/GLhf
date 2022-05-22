#include <iostream>

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace GLhf
{
        
    // Constructor (sets default texture modes)
    Texture2D::Texture2D()
        : width_(0), height_(0),
        internal_format_(GL_RGB), image_format_(GL_RGB),
        wrap_s_(GL_REPEAT), wrap_t_(GL_REPEAT),
        filter_min_(GL_NEAREST), filter_max_(GL_LINEAR)
    {
    }

    // Generates texture from image data
    void Texture2D::Create(GLuint w, GLuint h, const GLubyte *data)
    {
        // Redefine dimensions
        width_ = w;
        height_ = h;

        // Create texture
        glGenTextures(1, &id_);
        glBindTexture(GL_TEXTURE_2D, id_);
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format_,
                    width_, height_,
                    0, image_format_, GL_UNSIGNED_BYTE, data);

        // Set texture wraping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_);
        // Set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max_);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
        GLubyte *data = stbi_load(image_path, &width_, &height_, &nbr_channels, 0);

        // Create texture
        glGenTextures(1, &id_);
        glBindTexture(GL_TEXTURE_2D, id_);
        // Set texture wraping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_);
        // Set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max_);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
            throw "Failed to load texture";

        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }

    void Texture2D::Update(const GLubyte *data)
    {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, data);
    }

    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Texture2D::Bind() const
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->id_);
    }

    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Texture2D::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}