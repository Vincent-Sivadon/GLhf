/* Texture relative features abstraction
 * (doesn't work for now) */

#pragma once

#include <glad/glad.h>

namespace GLhf
{

    class Texture2D
    {
    public:
        // Texture ID
        GLuint ID;

        // Texture image dimensions
        GLint width, height;

        // Texture Format
        GLuint internalFormat;
        GLuint imageFormat;

        // Texture configuration
        GLuint wrapS;     // wrapping mode on S axis
        GLuint wrapT;     // wrapping mode on T axis
        GLuint filterMin; // filtering mode if texture pixels < screen pixels
        GLuint filterMax; // filtering mode if texture pixels > screen pixels

        // Constructor (sets defalt texture modes)
        Texture2D();

        // Generates texture from image data
        void Create(const char * image_path);
        void Create(GLuint w, GLuint h, const GLubyte *data);
        
        void Update(const GLubyte *data);

        // Binds the texture as the current actvie GL_TEXTURE_2D object
        void Bind() const;
        void Unbind() const;
    };

}