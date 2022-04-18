#pragma once

#include "Shape.h"

#include <math.h>
#include <string>

class Disk : public Shape
{
public:
    int numberOfTriangles = 8;

    GLfloat *CreateVertices();
    GLuint *CreateIndices();
};

GLfloat *Disk::CreateVertices()
{
    // Properties
    float delta = 2 * M_PI / numberOfTriangles;

    // Allocation
    GLfloat *vertices = new GLfloat[(numberOfTriangles + 1) * 3];

    // Middle point
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    for (int triangleID = 0; triangleID < numberOfTriangles; triangleID++)
    {
        vertices[3 * (triangleID + 1)] = cos((float)triangleID * delta);     // x coordinate
        vertices[3 * (triangleID + 1) + 1] = sin((float)triangleID * delta); // y coordinate
        vertices[3 * (triangleID + 1) + 2] = 0.0f;                           // z coordinate
    }

    verticesSize = 3 * (numberOfTriangles + 1) * sizeof(GLfloat);

    return vertices;
}

GLuint *Disk::CreateIndices()
{
    // Properties
    float delta = 2 * M_PI / numberOfTriangles;

    // Allocation
    GLuint *indices = new GLuint[numberOfTriangles * 3];

    // Indices indices
    unsigned int p = 2, q = 1;

    for (int triangleID = 0; triangleID < numberOfTriangles; triangleID++)
    {
        if (p == numberOfTriangles + 1)
            p = 1;
        indices[3 * triangleID] = 0;
        indices[3 * triangleID + 1] = p;
        indices[3 * triangleID + 2] = q;

        p++;
        q++;
    }

    indicesSize = 3 * numberOfTriangles * sizeof(GLuint);

    return indices;
}