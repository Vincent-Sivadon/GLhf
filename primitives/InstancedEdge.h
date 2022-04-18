#pragma once

#include "InstancedShape.h"

#include <math.h>
#include <string>

/* ************************* INSTANCED DISK CLASS ************************* */
class InstancedEdge : public InstancedShape
{
private:
    GLfloat *diskPositions;

public:
    int nbTriangles = 60;

    GLfloat *CreateVertices();
    GLuint *CreateIndices();

    void InitPositions(glm::vec2 *diskPositions, int nb);
    void EdgePos(int k, const glm::vec2 &a, const glm::vec2 &b);
};
/* ************************************************************************ */

void InstancedEdge::EdgePos(int k, const glm::vec2 &a, const glm::vec2 &b)
{
    // Delta
    float dx = abs(b.x - a.x);
    float dy = abs(b.y - a.y);

    // Position
    a.x < b.x ? positions[k].x = a.x + (dx / 2.0f) : positions[k].x = a.x - (dx / 2.0f);
    a.y < b.y ? positions[k].y = a.y + (dy / 2.0f) : positions[k].y = a.y - (dy / 2.0f);

    // Dimensions
    width[k] = sqrt(dx * dx + dy * dy);
    height[k] = 0.02f;

    // Rotation
    float alpha = (float)atan(dy / dx);
    if (a.x < b.x)
        a.y < b.y ? angle[k] = M_PI - alpha : angle[k] = alpha;
    else
        a.y < b.y ? angle[k] = alpha : angle[k] = M_PI - alpha;
}

void InstancedEdge::InitPositions(glm::vec2 *diskPositions, int nb)
{
    N = nb * (nb - 1) / 2;
    positions = new glm::vec2[N];
    width = new float[N];
    height = new float[N];
    angle = new float[N];

    int k = 0;

    // For every pair of nodes
    for (int i = 0; i < nb - 1; i++)
        for (int j = i + 1; j < nb; j++)
        {
            EdgePos(k, diskPositions[i], diskPositions[j]);
            k++;
        }
}

GLfloat *InstancedEdge::CreateVertices()
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

GLuint *InstancedEdge::CreateIndices()
{
    GLuint *indices = new GLuint[3 * 2]{
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    indicesSize = 3 * 2 * sizeof(GLuint);

    return indices;
}