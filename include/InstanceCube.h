#pragma once

#include "Cube.h"

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace GLhf
{

    class InstanceCube : public Cube
    {
    public:
        void Create(const std::vector<glm::vec3>& positions);

        int nb_of_instances_;
        
        void Bind();

    private:
        VertexBuffer instance_buffer_;
        std::vector<glm::vec3> positions_;

        void CreateInstanceBuffer();
        void CreateVertexArray();
        
    };

    void InstanceCube::Create(const std::vector<glm::vec3>& positions)
    {
        nb_of_instances_ = positions.size();
        positions_ = std::move(positions);

        /* Create Buffers */
        CreateInstanceBuffer();
        CreateCoordsBuffer();
        CreateTexCoordsBuffer();
        CreateNormalsBuffer();
        CreateVertexArray();
        CreateElementsBuffer();

        /* Create Shader */
        shader_.Create("instance_shape.vs", "shape.fs");

        /* Set Properties */
        SetColor(color_.x, color_.y, color_.z);
        SetView(view_matrix_);
    }

    void InstanceCube::CreateInstanceBuffer()
    {
        std::vector<glm::mat4> model_matrices(nb_of_instances_);
        for (int i = 0; i < nb_of_instances_; i++)
        {
            model_matrices[i] = glm::mat4(1.0f);
            model_matrices[i] = glm::translate(model_matrices[i], positions_[i]);
            model_matrices[i] = glm::scale(model_matrices[i], glm::vec3(scale_));
        }        

        instance_buffer_.Create(&model_matrices[0], nb_of_instances_ * sizeof(glm::mat4));
    }
   
    void InstanceCube::Bind()
    {
        texture_->Bind();
        shader_.Bind();
        vertex_array_.Bind();
    }

    void InstanceCube::CreateVertexArray()
    {
        vertex_array_.Create(coord_buffer_, tex_coord_buffer_, normal_buffer_, instance_buffer_);
    }
}