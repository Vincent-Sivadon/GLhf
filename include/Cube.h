#pragma once

#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"

#include "Shader.h"
#include "Texture.h"

namespace GLhf
{

    class Cube
    {
    private:
        /* Buffers */
        VertexBuffer CoordsBuffer_;
        VertexBuffer TexCoordsBuffer_;
        VertexBuffer NormalsBuffer_;
        ElementBuffer ElementsBuffer_;
        VertexArray VertexArray_;

        /* Shader */
        Shader Shader_;

        /* Uniforms */
        std::string TextureFile_{"../resources/white.png"};
        Texture2D Texture_;
        glm::vec3 Color_{1.0f, 1.0f, 1.0f};
        glm::vec3 Position_{0.0f, 0.0f, 0.0f};
        float Scale_{1.0f};

        /* Matrices */
        glm::mat4 ProjectionMatrix_;
        glm::mat4 ModelMatrix_;
        glm::mat4 ViewMatrix_;

        /* Initialize Buffers */
        void CreateElementBuffer();
        void CreateCoordsBuffer();
        void CreateTexCoordsBuffer();
        void CreateNormalsBuffer();

    public:
        Cube() {}
        ~Cube();

        /* Set Properties */
        void SetColor(float r, float g, float b);
        void SetPositions(float x, float y, float z);
        void SetTexture(const std::string& filename);

        /* Set Matrices */
        void SetModel(const glm::mat4& mat);
        void SetView(const glm::mat4& mat);
        void SetProjection(const glm::mat4& mat);

        /* Binds for draw calls */
        void Bind();
    };

    Cube::Cube()
    {
        /* Create Buffers */
        CreateCoordsBuffer();
        CreateTexCoordsBuffer();
        CreateNormalsBuffer();
        CreateElementBuffer();

        /* Create Texture */
        SetTexture(TextureFile_);

        /* Model Matrix */
        ModelMatrix_ = glm::mat4(1.0f);
        ModelMatrix_ = glm::translate(ModelMatrix_, Position_);
        // ModelMatrix_ = glm::rotate(ModelMatrix_, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix_ = glm::scale(ModelMatrix_, glm::vec3(Scale_));

        /* View Matrix */
        ViewMatrix_ = glm::mat4(1.0f);

        /* Create Shader */
        Shader_.Create("../resources/shaders/cube.vs", "../resources/shaders/cube.fs");

        /* Set Uniforms */
        Shader_.SetUniform("color", Color_);
        Shader_.SetUniform("model", ModelMatrix_);
        Shader_.SetUniform("view", ViewMatrix_);
    }

    Cube::~Cube()
    {
        CoordsBuffer_.Destroy();
        TexCoordsBuffer_.Destroy();
        NormalsBuffer_.Destroy();
        ElementsBuffer_.Destroy();
        VertexArray_.Destroy();
        // Texture.Destroy() ?
    }

    void Cube::SetColor(float r, float g, float b)
    {
        Color_ = glm::vec3(r, g, b);
    }

    void Cube::SetPositions(float x, float y, float z)
    {
        Position_ = glm::vec3(x, y, z);
    }

    void Cube::SetTexture(const std::string& filename)
    {
        TextureFile_ = filename;
    }

    void Cube::SetModel(const glm::mat4& mat)
    {
        Shader_.Bind(); // Use shader program
        ModelMatrix_ = mat;
        Shader_.SetUniform("model", ModelMatrix_);
    }

    void Cube::SetView(const glm::mat4& mat)
    {
        Shader_.Bind(); // Use shader program
        ViewMatrix_ = mat;
        Shader_.SetUniform("view", ViewMatrix_);
    }

    void Cube::SetProjection(const glm::mat4& mat)
    {
        Shader_.Bind(); // Use shader program
        ProjectionMatrix_ = mat;
        Shader_.SetUniform("projection", ProjectionMatrix_);
    }

    void Cube::Bind()
    {
        Texture_.Bind();
        Shader_.Bind();
        VertexArray_.Bind();
    }
}