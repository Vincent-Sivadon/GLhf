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
    int size = (nbTriangles + 1) * (3 + 2);
    GLfloat *vertices = new GLfloat[size];

    // Middle point
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    for (int triangleID = 0; triangleID < nbTriangles; triangleID++)
    {
        vertices[(3+2) * (triangleID + 1)] = cos((float)triangleID * delta);     // x coordinate
        vertices[(3+2) * (triangleID + 1) + 1] = sin((float)triangleID * delta); // y coordinate
        vertices[(3+2) * (triangleID + 1) + 2] = 0.0f;                           // z coordinate

        vertices[(3+2) * (triangleID + 1) + 3] = vertices[(3+2) * (triangleID + 1)] / 2.0f + 0.5f;        // Tex coords
        vertices[(3+2) * (triangleID + 1) + 4] = vertices[(3+2) * (triangleID + 1) + 1] / 2.0f + 0.5f;    // Tex coords
    }

    verticesSize = size * sizeof(GLfloat);

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