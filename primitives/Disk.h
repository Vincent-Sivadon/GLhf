/* Disk Primitive Class */

#pragma once

#include "Shape.h"

#include <math.h>
#include <string>

namespace GLhf 
{
        
    /* ************************* DISK CLASS ************************* */

    class Disk : public Shape
    {
    private:
        GLfloat *Coords;
    public:
        int nbTriangles = 8;

        void CreateVertices(GLfloat **coords, GLfloat **texcoords) override;
        void CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **normals) override;
        GLuint *CreateElements() override;
        GLfloat *CreateCoords() override;
        GLfloat *CreateTexCoords() override;
        GLfloat *CreateNormals() override;

        void SetNumberOfTriangles(int n);
    };

    /* ************************************************************** */

    void Disk::SetNumberOfTriangles(int n)
    {
        if (n<=0)
            throw "Disk nbTriangles was set to n<=0";
        nbTriangles = n;
    }


    GLfloat *Disk::CreateCoords()
    {
        // Properties
        float delta = 2 * M_PI / nbTriangles;

        // Allocation
        int size = (nbTriangles + 1) * 3;
        GLfloat *coords = new GLfloat[size];

        // Middle point
        coords[0] = 0.0f;
        coords[1] = 0.0f;
        coords[2] = 0.0f;

        for (int triangleID = 0; triangleID < nbTriangles; triangleID++)
        {
            coords[3 * (triangleID + 1)] = cos((float)triangleID * delta);     // x coordinate
            coords[3 * (triangleID + 1) + 1] = sin((float)triangleID * delta); // y coordinate
            coords[3 * (triangleID + 1) + 2] = 0.0f;                           // z coordinate
        }

        CoordsSize = size * sizeof(GLfloat);
        return coords;
    }

    GLfloat *Disk::CreateTexCoords()
    {
        // Properties
        float delta = 2 * M_PI / nbTriangles;

        // Allocation
        int size = (nbTriangles + 1) * 2;
        GLfloat *texcoords = new GLfloat[size];

        for (int triangleID = 0; triangleID < nbTriangles; triangleID++)
        {
            texcoords[2 * (triangleID + 1)] = Coords[3 * (triangleID + 1)] / 2.0f + 0.5f;
            texcoords[2 * (triangleID + 1) + 1] = Coords[3 * (triangleID + 1) + 1] / 2.0f + 0.5f;
        }

        TexCoordsSize = size * sizeof(GLfloat);
        return texcoords;
    }

    GLfloat *Disk::CreateNormals()
    {
        int size = TexCoordsSize;
        GLfloat *normals = new GLfloat[size];

        return normals;
    }

    GLuint *Disk::CreateElements()
    {
        // Properties
        float delta = 2 * M_PI / nbTriangles;

        // Allocation
        GLuint *elements = new GLuint[nbTriangles * 3];

        // Indices elements
        unsigned int p = 2, q = 1;

        for (int triangleID = 0; triangleID < nbTriangles; triangleID++)
        {
            if (p == nbTriangles + 1)
                p = 1;
            elements[3 * triangleID] = 0;
            elements[3 * triangleID + 1] = p;
            elements[3 * triangleID + 2] = q;

            p++;
            q++;
        }

        ElementsSize = 3 * nbTriangles * sizeof(GLuint);

        return elements;
    }
    
    void Disk::CreateVertices(GLfloat **coords, GLfloat **texcoords)
    {
        *coords = CreateCoords();
        Coords = *coords;
        *texcoords = CreateTexCoords();
    }

    void Disk::CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **norrmals)
    {
    }
}