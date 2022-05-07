/* */

#pragma once

#include "Shader.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"

#include <cstring>
#include <string>

namespace GLhf 
{
        
    class Shape
    {
    protected:
        Texture2D texture;
        Shader shader;
        VertexArray vao;
        VertexBuffer vbo;
        ElementBuffer ebo;

        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        int verticesSize;
        int indicesSize;

        int textureDefined = 0;

    public:
        virtual ~Shape() = default;

        char vertexShaderPath[100] = "shape.vs";
        char fragmentShaderPath[100] = "shape.fs";

        // Properties
        glm::vec3 pos;
        glm::vec3 color{1.0f, 1.0f, 1.0f};
        float angle = 0.0f;
        float width = 1.0f;
        float height = 1.0f;

        virtual GLfloat *CreateVertices() = 0;
        virtual GLuint *CreateIndices() = 0;

        virtual void Create();
        virtual void Destroy();

        virtual void Draw();

        void SetModel(const glm::mat4 &mat);
        void SetView(const glm::mat4 &mat);
        void SetProjection(const glm::mat4 &proj);

        void SetPosition(glm::vec3 position);
        void SetPosition(float x, float y, float z);
        void SetPosition(float x, float y);

        void SetColor(float r, float g, float b);

        void SetTexture(GLuint w, GLuint h, const GLubyte *data);
        void SetTexture(const char *image_path);
        void UpdateTexture(const GLubyte *data);
        void SetTextureWrapMode(GLuint ws, GLuint wt);

        virtual void SetShaderNames(std::string vertexShaderName, std::string fragmentShaderName);
    };

}