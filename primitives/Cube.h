#pragma once

#include "Shape.h"

#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GLhf 
{
        
    class Cube : public Shape
    {
    private:
        void CreateVertices(GLfloat **coords, GLfloat **texcoords) override;
        void CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **normals) override;
        GLuint *CreateElements() override;
        GLfloat *CreateCoords() override;
        GLfloat *CreateTexCoords() override;
        GLfloat *CreateNormals() override;
    };

    GLfloat* Cube::CreateCoords()
    {
        int coords_size = 6/*faces*/ * 2/*triangles*/ * 3/*vertices*/ * 3/*coords*/;
        GLfloat *coords = new GLfloat[coords_size]{
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f, 
            0.5f,  0.5f, -0.5f, 
            0.5f,  0.5f, -0.5f, 
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f, 
            0.5f,  0.5f,  0.5f, 
            0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f, 
            0.5f, -0.5f,  0.5f, 
            0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f, 
            0.5f,  0.5f,  0.5f, 
            0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
        };

        CoordsSize = coords_size * sizeof(GLfloat);
        return coords;
    }

    GLfloat *Cube::CreateTexCoords()
    {
        int texcoords_size = 6*2*3*2;
        GLfloat *texcoords = new GLfloat[texcoords_size] {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
          };

          TexCoordsSize = texcoords_size * sizeof(GLfloat);
          return texcoords;
    }

    GLfloat *Cube::CreateNormals()
    {
        int size = CoordsSize;
        GLfloat *normals = new GLfloat[size] {
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f, 
            0.0f,  0.0f, -1.0f, 
            0.0f,  0.0f, -1.0f, 
            0.0f,  0.0f, -1.0f, 
            0.0f,  0.0f, -1.0f, 

            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,

            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,

            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,

            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,

            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f        
        };

        return normals;
    }

    void Cube::CreateVertices(GLfloat **coords, GLfloat **texcoords)
    {
        *coords = CreateCoords();
        *texcoords = CreateTexCoords();
    }

    void Cube::CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **normals)
    {
        *coords = CreateCoords();
        *texcoords = CreateTexCoords();
        *normals = CreateNormals();
    }

    GLuint *Cube::CreateElements()
    {
        int size = 6/*faces*/ * 2/*triangles*/ * 3/*Elements*/;
        GLuint *elements = new GLuint[size]{
            0, 1, 2,
            3, 4, 5,
            6, 7, 8,
            9, 10, 11,
            12, 13, 14,
            15, 16, 17,
            18, 19, 20,
            21, 22, 23,
            24, 25, 26,
            27, 28, 29,
            30, 31, 32,
            33, 34, 35
        };

        ElementsSize = size * sizeof(GLuint);

        return elements;
    }

}