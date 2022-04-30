/* */

#include "Shape.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Shape::Create()
{
    GLfloat *vertices = CreateVertices();
    GLuint *indices = CreateIndices();

    shader = Shader(vertexShaderPath, fragmentShaderPath);

    // Buffers
    vbo = VertexBuffer(vertices, verticesSize);
    vao = VertexArray(0, 3, 1, 2);
    ebo = ElementBuffer(indices, indicesSize);

    // Projection Matrix
    SetProjection(glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 0.1f, 100.0f));

    // Model Matrix
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));
    SetModel(model);

    // View matrix
    SetView(glm::mat4(1.0f));

    // Color
    SetColor(color.x, color.y, color.z);

    delete vertices;
    delete indices;
}

void Shape::Destroy()
{
    shader.Destroy();
    vao.Destroy();
    vbo.Destroy();
    ebo.Destroy();
}

void Shape::Draw()
{
    texture.Bind();
    shader.Bind();
    vao.Bind();
    ebo.Bind();
    glDrawElements(GL_TRIANGLES, indicesSize / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void Shape::SetModel(const glm::mat4 &mat)
{
    shader.Bind(); // Use shader program
    model = mat;
    shader.SetUniform("model", model);
}

void Shape::SetView(const glm::mat4 &mat)
{
    shader.Bind(); // Use shader program
    view = mat;
    shader.SetUniform("view", view);
}

void Shape::SetProjection(const glm::mat4 &proj)
{
    shader.Bind();
    projection = proj;
    shader.SetUniform("projection", projection);
}

void Shape::SetPosition(glm::vec3 position)
{
    pos = position;
    model = glm::translate(model, pos);
}

void Shape::SetPosition(float x, float y, float z)
{
    pos = glm::vec3(x, y, z);
    model = glm::translate(model, pos);
}

void Shape::SetPosition(float x, float y)
{
    pos = glm::vec3(x, y, 0.0f);
    model = glm::translate(model, pos);
    SetModel(model);
}

void Shape::SetColor(float r, float g, float b)
{
    color = glm::vec3(r, g, b);
    shader.Bind();
    shader.SetUniform("color", color);
}

void Shape::SetShaderNames(std::string vertexShaderName, std::string fragmentShaderName)
{
    std::string dirPath = "/usr/local/share/GLtemplate/";

    std::string newVertexPath = dirPath + vertexShaderName;
    strcpy(vertexShaderPath, newVertexPath.c_str());

    std::string newFragmentPath = dirPath + fragmentShaderName;
    strcpy(fragmentShaderPath, newFragmentPath.c_str());
}

void Shape::SetTexture(GLuint w, GLuint h, const GLubyte *data)
{
    textureDefined = 1;
    shader.SetUniform("textureDefined", 1);
    texture.Create(w, h, data);
}

// ATTENTION : doit-être appelé après Create()
void Shape::SetTexture(const char *image_path)
{
    textureDefined = 1;
    shader.SetUniform("textureDefined", 1);
    texture.Create(image_path);
}

void Shape::UpdateTexture(const GLubyte *data)
{
    texture.Update(data);
}
