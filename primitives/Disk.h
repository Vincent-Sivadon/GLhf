#pragma once

#include "Shape.h"

#include <math.h>
#include <string>

class Disk : public Shape
{
public:
    float radius = 1.0f;

    int numberOfTriangles = 30;

    void Create() override;
    void Destroy() override;

    void Draw() override;

    void CreateVertices(GLfloat *&vertices, GLuint *&indices);
};

void Disk::Create()
{
    shader = Shader(vertexShaderPath, fragmentShaderPath);

    GLfloat *vertices;
    GLuint *indices;
    CreateVertices(vertices, indices);

    // Buffers
    vbo = VertexBuffer(vertices, 3 * (numberOfTriangles + 1) * sizeof(GLfloat));
    vao = VertexArray(0, 3);
    ebo = ElementBuffer(indices, 3 * numberOfTriangles * sizeof(GLuint));

    // Projection Matrix
    SetProjection(glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 0.1f, 100.0f));

    // Model Matrix
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, -1.0f));
    model = glm::scale(model, glm::vec3(radius, radius, 1.0f));
    SetModel(model);

    // View matrix
    SetView(glm::mat4(1.0f));

    // Color
    SetColor(color.x, color.y, color.z);
}

void Disk::Destroy()
{
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
    ebo.Destroy();
}

void Disk::Draw()
{
    shader.Bind();
    vao.Bind();
    ebo.Bind();
    glDrawElements(GL_TRIANGLES, 3 * numberOfTriangles, GL_UNSIGNED_INT, 0);
}

void Disk::CreateVertices(GLfloat *&vertices, GLuint *&indices)
{
    // Properties
    float delta = 2 * M_PI / numberOfTriangles;

    // Allocation
    vertices = new GLfloat[(numberOfTriangles + 1) * 3]; // N + 1 points à 3 coords
    indices = new GLuint[numberOfTriangles * 3];         // N triangles à 3 points

    // Middle point
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    // Indices indices
    unsigned int p = 2, q = 1;

    for (int triangleID = 0; triangleID < numberOfTriangles; triangleID++)
    {
        vertices[3 * (triangleID + 1)] = cos((float)triangleID * delta);     // x coordinate
        vertices[3 * (triangleID + 1) + 1] = sin((float)triangleID * delta); // y coordinate
        vertices[3 * (triangleID + 1) + 2] = 0.0f;                           // z coordinate

        if (p == numberOfTriangles + 1)
            p = 1;
        indices[3 * triangleID] = 0;
        indices[3 * triangleID + 1] = p;
        indices[3 * triangleID + 2] = q;

        p++;
        q++;
    }
}
