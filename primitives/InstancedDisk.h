#pragma once

#include "InstancedShape.h"

#include <math.h>
#include <string>
#include <unistd.h>
#include <algorithm>

namespace GLhf 
{

    /* ************************* INSTANCED DISK CLASS ************************* */
    class InstancedDisk : public InstancedShape
    {
    private:
        int posRange = 1;
        GLfloat *coords;
    public:
        int nbTriangles = 60;

        void CreateVertices(GLfloat **coords, GLfloat **texcoords) override;
        void CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **normals) override;
        GLuint *CreateElements() override;
        GLfloat *CreateCoords() override;
        GLfloat *CreateTexCoords() override;
        GLfloat *CreateNormals() override;

        void SetDefaultProperties();
        void SetPosRange(int range);
    };
    /* ************************************************************************ */

    void InstancedDisk::SetPosRange(int range)
    {
        posRange = range;
    }

    void InstancedDisk::SetDefaultProperties()
    {
        srand(getpid());

        float defaultWidth = 0.05f;
        float defaultHeight = 0.05f;
        float defaultAngle = 0.0f;

        if (width == nullptr)
        {
            width = new float[N];
            for (int i = 0; i < N; i++)
                width[i] = defaultWidth;
        }

        if (height == nullptr)
        {
            height = new float[N];
            for (int i = 0; i < N; i++)
                height[i] = defaultHeight;
        }

        if (angle == nullptr)
        {
            angle = new float[N];
            for (int i = 0; i < N; i++)
                angle[i] = defaultAngle;
        }

        // Defines random positions if not already defined
        if (positions == nullptr)
        {
            positions = new glm::vec2[N];
            for (int i = 0; i < N; i++)
            {
                // Between -1 et 1
                float x = posRange * (2 * (float)rand() / (float)RAND_MAX - 1);
                float y = posRange * (2 * (float)rand() / (float)RAND_MAX - 1);
                positions[i] = glm::vec2(x, y);
            }
        }
    }

    GLfloat *InstancedDisk::CreateCoords()
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

    GLfloat *InstancedDisk::CreateTexCoords()
    {
        // Properties
        float delta = 2 * M_PI / nbTriangles;

        // Allocation
        int size = (nbTriangles + 1) * 2;
        GLfloat *texcoords = new GLfloat[size];

        for (int triangleID = 0; triangleID < nbTriangles; triangleID++)
        {
            texcoords[2 * (triangleID + 1)] = coords[2 * (triangleID + 1)] / 2.0f + 0.5f;        // Tex coords
            texcoords[2 * (triangleID + 1) + 1] = coords[2 * (triangleID + 1) + 1] / 2.0f + 0.5f;    // Tex coords
        }

        TexCoordsSize = size * sizeof(GLfloat);
        return texcoords;
    }

    GLfloat *InstancedDisk::CreateNormals()
    {
        int size = TexCoordsSize;
        GLfloat *normals = new GLfloat[size];

        return normals;
    }

    GLuint *InstancedDisk::CreateElements()
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
    
    void InstancedDisk::CreateVertices(GLfloat **coords, GLfloat **texcoords)
    {
        *coords = CreateCoords();
        *texcoords = CreateTexCoords();
    }
    void InstancedDisk::CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **normals)
    {
    }

}