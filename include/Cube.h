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
    public:
        void Create();
        Cube() {}
        ~Cube();

        /* Set Properties */
        void SetColor(float r, float g, float b);
        void SetPosition(float x, float y, float z);
        void SetTexture(Texture2D& texture);

        /* Set Matrices */
        void SetModel(const glm::mat4& mat);
        void SetView(const glm::mat4& mat);
        void SetProjection(const glm::mat4& mat);
        void SetCameraPos(const glm::vec3& camera_pos);

        /* Binds for draw calls */
        void Bind() const;

        /* Update */
        void UpdateCoordsBuffer(std::vector<glm::vec3>* positions);

        /* Get */
        inline int ElementsBufferSize()  const { return element_buffer_.Size();  }
        inline int CoordsBufferSize()    const { return coord_buffer_.Size();    }
        inline int TexCoordsBufferSize() const { return tex_coord_buffer_.Size(); }
        inline int NormalsBufferSize()   const { return normal_buffer_.Size();   }

    protected:
        /* Buffers */
        VertexBuffer coord_buffer_;
        VertexBuffer tex_coord_buffer_;
        VertexBuffer normal_buffer_;
        ElementBuffer element_buffer_;
        VertexArray vertex_array_;

        /* Shader */
        Shader shader_;

        /* Uniforms */
        Texture2D * texture_;
        glm::vec3 color_{1.0f, 1.0f, 1.0f};
        glm::vec3 position_{0.0f, 0.0f, 0.0f};
        float scale_{1.0f};

        /* Matrices */
        glm::mat4 projection_matrix_;
        glm::mat4 model_matrix_{1.0f};
        glm::mat4 view_matrix_{1.0f};

        /* Initialize Buffers */
        void CreateElementsBuffer();
        void CreateCoordsBuffer();
        void CreateTexCoordsBuffer();
        void CreateNormalsBuffer();
        void CreateVertexArray();
    };

} // namespace GLhf