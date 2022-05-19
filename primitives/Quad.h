#pragma once

#include "Shape.h"

namespace GLhf 
{
        
    class Quad : public Shape
    {
    private:
        void CreateVertices(GLfloat **coords, GLfloat **texcoords) override;
        void CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **normals) override;
        GLuint *CreateElements() override;
        GLfloat *CreateCoords() override;
        GLfloat *CreateTexCoords() override;
        GLfloat *CreateNormals() override;
    };

    GLfloat *Quad::CreateCoords()
    {
        int size = 3*4;
        GLfloat *coords = new GLfloat[size]{
            0.5f, 0.5f, 0.0f,   
            0.5f, -0.5f, 0.0f,  
            -0.5f, -0.5f, 0.0f, 
            -0.5f, 0.5f, 0.0f
        };

        CoordsSize = size * sizeof(GLfloat);
        return coords;
    }

    GLfloat *Quad::CreateTexCoords()
    {
        int size = 2 * 4;
        GLfloat *texcoords = new GLfloat[size] {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
        };

        TexCoordsSize = size * sizeof(GLfloat);
        return texcoords;
    }

    GLfloat *Quad::CreateNormals()
    {
        int size = TexCoordsSize;
        GLfloat *normals = new GLfloat[size];

        return normals;
    }

    void Quad::CreateVertices(GLfloat **coords, GLfloat **texcoords)
    {
        *coords = CreateCoords();
        *texcoords = CreateTexCoords();
    }
    void Quad::CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **normals)
    {
    }

    GLuint *Quad::CreateElements()
    {
        GLuint *elements = new GLuint[3 * 2]{
            // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        ElementsSize = 3 * 2 * sizeof(GLuint);

        return elements;
    }

}