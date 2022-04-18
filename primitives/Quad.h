#pragma once

#include "Shape.h"

class Quad : public Shape
{
private:
    GLfloat *CreateVertices() override;
    GLuint *CreateIndices() override;
};

GLfloat *Quad::CreateVertices()
{
    GLfloat *vertices = new GLfloat[3 * 4]{
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };

    verticesSize = 3 * 4 * sizeof(GLfloat);

    return vertices;
}

GLuint *Quad::CreateIndices()
{
    GLuint *indices = new GLuint[3 * 2]{
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    indicesSize = 3 * 2 * sizeof(GLuint);

    return indices;
}