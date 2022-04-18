/* */

#include "InstancedShape.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void InstancedShape::Create()
{
    if (N <= 0)
        throw "Trying to create InstancedShape with N<=0";

    SetDefaultProperties();

    shader = Shader(vertexShaderPath, fragmentShaderPath);

    GLfloat *vertices = CreateVertices();
    GLuint *indices = CreateIndices();

    // Model Matrix
    modelMatrices = new glm::mat4[N];
    for (int i = 0; i < N; i++)
    {
        modelMatrices[i] = glm::mat4(1.0f);
        modelMatrices[i] = glm::translate(modelMatrices[i], glm::vec3(positions[i], 0.0f));
        modelMatrices[i] = glm::rotate(modelMatrices[i], angle[i], glm::vec3(0.0f, 0.0f, -1.0f));
        modelMatrices[i] = glm::scale(modelMatrices[i], glm::vec3(width[i], height[i], 1.0f));
    }

    // Vertex Buffers
    vbo = VertexBuffer(vertices, verticesSize);
    instancedVBO = VertexBuffer(modelMatrices, N * sizeof(glm::mat4));

    // Vertex Array
    vbo.Bind();
    vao = VertexArray(0, 3);

    instancedVBO.Bind();
    // glBindBuffer(GL_ARRAY_BUFFER, instancedVBO.ID); // this attribute comes from a different vertex buffer
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(3 * sizeof(glm::vec4)));

    // tell OpenGL this is an instanced vertex attribute.
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);

    // Element buffer
    ebo = ElementBuffer(indices, indicesSize);

    // Projection Matrix
    SetProjection(glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 0.1f, 100.0f));

    // View matrix
    SetView(glm::mat4(1.0f));

    // Color
    SetColor(color.x, color.y, color.z);

    delete vertices;
    delete indices;
}

void InstancedShape::Destroy()
{
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
    instancedVBO.Destroy();
    ebo.Destroy();

    delete positions;
    delete width;
    delete height;
    delete angle;
    delete modelMatrices;
}

void InstancedShape::Draw()
{
    shader.Bind();
    vao.Bind();
    ebo.Bind();
    glDrawElementsInstanced(GL_TRIANGLES, indicesSize / sizeof(GLuint), GL_UNSIGNED_INT, 0, N);
}

void InstancedShape::SetShaderNames(std::string vertexShaderName, std::string fragmentShaderName)
{
    std::string dirPath = "/usr/local/share/GLtemplate/";

    std::string newVertexPath = dirPath + vertexShaderName;
    strcpy(vertexShaderPath, newVertexPath.c_str());

    std::string newFragmentPath = dirPath + fragmentShaderName;
    strcpy(fragmentShaderPath, newFragmentPath.c_str());
}