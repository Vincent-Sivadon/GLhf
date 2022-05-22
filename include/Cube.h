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
        void SetTexture(const std::string& filename);

        /* Set Matrices */
        void SetModel(const glm::mat4& mat);
        void SetView(const glm::mat4& mat);
        void SetProjection(const glm::mat4& mat);

        /* Binds for draw calls */
        void Bind() const;

        /* Get */
        inline int ElementsBufferSize()  const { return element_buffer_.Size();  }
        inline int CoordsBufferSize()    const { return coord_buffer_.Size();    }
        inline int TexCoordsBufferSize() const { return tex_coord_buffer_.Size(); }
        inline int NormalsBufferSize()   const { return normal_buffer_.Size();   }

    private:
        /* Buffers */
        VertexBuffer coord_buffer_;
        VertexBuffer tex_coord_buffer_;
        VertexBuffer normal_buffer_;
        ElementBuffer element_buffer_;
        VertexArray vertex_array_;

        /* Shader */
        Shader shader_;

        /* Uniforms */
        std::string texture_file_{"../resources/white.png"};
        Texture2D texture_;
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