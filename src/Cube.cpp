#include "Cube.h"

#include <glm/gtc/matrix_transform.hpp>
#include <string.h>

namespace GLhf
{

    void Cube::Create()
    {
        /* Create Buffers */
        CreateCoordsBuffer();
        CreateTexCoordsBuffer();
        CreateNormalsBuffer();
        CreateVertexArray();
        CreateElementsBuffer();

        /* Model Matrix */
        model_matrix_ = glm::translate(model_matrix_, position_);
        // model_matrix_ = glm::rotate(model_matrix_, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        model_matrix_ = glm::scale(model_matrix_, glm::vec3(scale_));

        /* Create Shader */
        shader_.Create("shape.vs", "shape.fs");

        /* Set Properties */
        SetColor(color_.x, color_.y, color_.z);
        SetModel(model_matrix_);
        SetView(view_matrix_);
    }

    Cube::~Cube()
    {
        coord_buffer_.Destroy();
        tex_coord_buffer_.Destroy();
        normal_buffer_.Destroy();
        element_buffer_.Destroy();
        vertex_array_.Destroy();
    }

    void Cube::SetColor(float r, float g, float b)
    {
        shader_.Bind();
        color_ = glm::vec3(r, g, b);
        shader_.SetUniform("color", color_);
    }

    void Cube::SetPosition(float x, float y, float z)
    {
        position_ = glm::vec3(x, y, z);
    }

    void Cube::SetTexture(Texture2D& texture)
    {
        texture_ = &texture;
    }

    void Cube::SetModel(const glm::mat4& mat)
    {
        shader_.Bind(); // Use shader program
        model_matrix_ = mat;
        shader_.SetUniform("model", model_matrix_);
    }

    void Cube::SetView(const glm::mat4& mat)
    {
        shader_.Bind(); // Use shader program
        view_matrix_ = mat;
        shader_.SetUniform("view", view_matrix_);
    }

    void Cube::SetProjection(const glm::mat4& mat)
    {
        shader_.Bind(); // Use shader program
        projection_matrix_ = mat;
        shader_.SetUniform("projection", projection_matrix_);
    }

    void Cube::SetCameraPos(const glm::vec3& camera_pos)
    {
        shader_.Bind();
        shader_.SetUniform("camera_pos", camera_pos);
    }

    void Cube::Bind() const
    {
        texture_->Bind();
        shader_.Bind();
        vertex_array_.Bind();
    }

    void Cube::CreateCoordsBuffer()
    {
        int coords_count = 6/*faces*/ * 2/*triangles*/ * 3/*vertices*/ * 3/*coords*/;
        GLfloat *coords = new GLfloat[coords_count]{
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f, 
            0.5f,  0.5f, -0.5f, 
            0.5f,  0.5f, -0.5f, 
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f, 
            0.5f,  0.5f,  0.5f, 
            0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f, 
            0.5f, -0.5f,  0.5f, 
            0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f, 
            0.5f,  0.5f,  0.5f, 
            0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
        };

        coord_buffer_.Create(coords, coords_count * sizeof(GLfloat));
    }

    void Cube::CreateTexCoordsBuffer()
    {
        int texcoords_count = 6/*faces*/*2/*triangles*/*3/*vertices*/*2/*tex_coords*/;
        GLfloat *texcoords = new GLfloat[texcoords_count] {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
          };

        tex_coord_buffer_.Create(texcoords, texcoords_count * sizeof(GLfloat));

    }

    void Cube::CreateNormalsBuffer()
    {
        int normals_count = 6/*faces*/ * 2/*triangles*/ * 3/*vertices*/ * 3/*coords*/;
        GLfloat *normals = new GLfloat[normals_count] {
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f, 
            0.0f,  0.0f, -1.0f, 
            0.0f,  0.0f, -1.0f, 
            0.0f,  0.0f, -1.0f, 
            0.0f,  0.0f, -1.0f, 

            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,

            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,

            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,

            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,

            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f        
        };

        normal_buffer_.Create(normals, normals_count * sizeof(GLfloat));
    }

    void Cube::CreateElementsBuffer()
    {
        int elements_count = 6/*faces*/ * 2/*triangles*/ * 3/*Elements*/;
        GLuint *elements = new GLuint[elements_count]{
            0, 1, 2,
            3, 4, 5,
            6, 7, 8,
            9, 10, 11,
            12, 13, 14,
            15, 16, 17,
            18, 19, 20,
            21, 22, 23,
            24, 25, 26,
            27, 28, 29,
            30, 31, 32,
            33, 34, 35
        };

        element_buffer_.Create(elements, elements_count * sizeof(GLuint));
    }

    void Cube::CreateVertexArray()
    {
        vertex_array_.Create(coord_buffer_, tex_coord_buffer_, normal_buffer_);
    }

    void Cube::UpdateCoordsBuffer(std::vector<glm::vec3>* positions)
    {
        float size = 3 * positions->size();

        glm::vec3* glm_data = reinterpret_cast<glm::vec3 *>(positions);
        float* data = reinterpret_cast<float*>(glm_data);

        coord_buffer_.UpdateData(data, size);
    }
}