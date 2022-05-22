/* Texture relative features abstraction
 * (doesn't work for now) */

#pragma once

#include <GL/glew.h>

namespace GLhf
{

    class Texture2D
    {
    public:
        // Texture ID
        GLuint id_;

        // Texture image dimensions
        GLint width_, height_;

        // Texture Format
        GLuint internal_format_;
        GLuint image_format_;

        // Texture configuration
        GLuint wrap_s_;     // wrapping mode on S axis
        GLuint wrap_t_;     // wrapping mode on T axis
        GLuint filter_min_; // filtering mode if texture pixels < screen pixels
        GLuint filter_max_; // filtering mode if texture pixels > screen pixels

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