/* Disk Primitive Class */

#pragma once

#include "Shape.h"

#include <math.h>
#include <string>

/* ************************* DISK CLASS ************************* */

class Disk : public Shape
{
public:
    int nbTriangles = 8;

    GLfloat *CreateVertices();
    GLuint *CreateIndices();
};

/* ************************************************************** */

GLfloat *Disk::CreateVertices()
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

GLuint *Disk::CreateIndices()
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