#pragma once

#include "InstancedShape.h"

#include <math.h>
#include <string>
#include <algorithm>

/* ************************* INSTANCED DISK CLASS ************************* */
class InstancedDisk : public InstancedShape
{
public:
    int nbTriangles = 60;

    GLfloat *CreateVertices();
    GLuint *CreateIndices();

    void SetDefaultProperties();
};
/* ************************************************************************ */

void InstancedDisk::SetDefaultProperties()
{
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
            float x = 1 * (2 * (float)rand() / (float)RAND_MAX - 1);
            float y = 1 * (2 * (float)rand() / (float)RAND_MAX - 1);
            positions[i] = glm::vec2(x, y);
        }
    }
}

GLfloat *CreateDiskVertices(int nbTriangles, int &verticesSize)
{
    // Properties
    float delta = 2 * M_PI / nbTriangles;

    // Allocation
    GLfloat *vertices = new GLfloat[(nbTriangles + 1) * 3];

    // Middle point
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    for (int triangleID = 0; triangleID < nbTriangles; triangleID++)
    {
        vertices[3 * (triangleID + 1)] = cos((float)triangleID * delta);     // x coordinate
        vertices[3 * (triangleID + 1) + 1] = sin((float)triangleID * delta); // y coordinate
        vertices[3 * (triangleID + 1) + 2] = 0.0f;                           // z coordinate
    }

    verticesSize = 3 * (nbTriangles + 1) * sizeof(GLfloat);

    return vertices;
}

GLuint *CreateDiskIndices(int nbTriangles, int &indicesSize)
{
    // Properties
    float delta = 2 * M_PI / nbTriangles;

    // Allocation
    GLuint *indices = new GLuint[nbTriangles * 3];

    // Indices indices
    unsigned int p = 2, q = 1;

    for (int triangleID = 0; triangleID < nbTriangles; triangleID++)
    {
        if (p == nbTriangles + 1)
            p = 1;
        indices[3 * triangleID] = 0;
        indices[3 * triangleID + 1] = p;
        indices[3 * triangleID + 2] = q;

        p++;
        q++;
    }

    indicesSize = 3 * nbTriangles * sizeof(GLuint);

    return indices;
}

GLfloat *InstancedDisk::CreateVertices()
{
    return CreateDiskVertices(nbTriangles, verticesSize);
}

GLuint *InstancedDisk::CreateIndices()
{
    return CreateDiskIndices(nbTriangles, indicesSize);
}