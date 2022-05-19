/* */

#include "Shape.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GLhf 
{

    void Shape::Create()
    {
        // Vertex data
        GLfloat *coords, *texcoords, *normals;
        CreateVertices(&coords, &texcoords, &normals);
        GLuint *elements = CreateElements();

        // Shader
        shader.Create(vertexShaderPath, fragmentShaderPath);

        // Vertex Buffers
        CoordsBuffer.Create(coords, CoordsSize);
        TexCoordsBuffer.Create(texcoords, TexCoordsSize);
        NormalsBuffer.Create(normals, CoordsSize);
        VAO.Create(CoordsBuffer, TexCoordsBuffer, NormalsBuffer);
        ElementsBuffer.Create(elements, ElementsSize);

        // Projection Matrix
        SetProjection(glm::perspective(glm::radians(45.0f), 1800.0f / 950.0f, 0.1f, 1000.0f));

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

        delete coords;
        delete texcoords;
        delete normals;
        delete elements;
    }

    void Shape::Destroy()
    {
        shader.Destroy();
        VAO.Destroy();
        CoordsBuffer.Destroy();
        TexCoordsBuffer.Destroy();
        NormalsBuffer.Destroy();
        ElementsBuffer.Destroy();
    }

    void Shape::Draw()
    {
        texture.Bind();
        shader.Bind();
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, ElementsSize / sizeof(GLuint), GL_UNSIGNED_INT, 0);
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
        std::string dirPath = "../resources/shaders/primitives/";

        std::string newVertexPath = dirPath + vertexShaderName;
        strcpy(vertexShaderPath, newVertexPath.c_str());

        std::string newFragmentPath = dirPath + fragmentShaderName;
        strcpy(fragmentShaderPath, newFragmentPath.c_str());
    }

    void Shape::SetTexture(GLuint w, GLuint h, const GLubyte *data)
    {
        textured = 1;
        shader.SetUniform("textured", 1);
        texture.Create(w, h, data);
    }

    // ATTENTION : doit-être appelé après Create()
    void Shape::SetTexture(const char *image_path)
    {
        textured = 1;
        shader.SetUniform("textured", 1);
        texture.Create(image_path);
    }

    void Shape::UpdateTexture(const GLubyte *data)
    {
        texture.Update(data);
    }

    void Shape::SetTextureWrapMode(GLuint ws, GLuint wt)
    {
        texture.wrapS = ws;
        texture.wrapT = wt;
    }

}