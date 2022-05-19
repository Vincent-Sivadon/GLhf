/* Instanced Shape : represent edges in a graph
/* For now it needs to be initialized with InitCompleteGraph :
/* It takes a glm::vec2 *diskPositions where each vec2 represent a Disk pos
/* and will add an edge between every Disk to create a complete graph */

#pragma once

#include "InstancedShape.h"

#include <math.h>
#include <string>
#include <iostream>

typedef unsigned long long u64;

namespace GLhf 
{
        

    /* ************************* INSTANCED DISK CLASS ************************* */
    class InstancedEdge : public InstancedShape
    {
    private:
        glm::vec2 *diskPositions;

    public:
        int nbTriangles = 60;

        void CreateVertices(GLfloat **coords, GLfloat **texcoords) override;
        void CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **normals) override;
        GLuint *CreateElements() override;
        GLfloat *CreateCoords() override;
        GLfloat *CreateTexCoords() override;
        GLfloat *CreateNormals() override;

        void SetDefaultProperties();

        void InitCompleteGraph(glm::vec2 *diskPos, int nb);
        void InitFromEdges(std::vector<std::pair<u64, u64>>& edges, glm::vec2 *diskPos);
        void InitFromEdges(u64 * edges, u64 nb_edges, glm::vec2 *diskPos);
        void EdgePos(int k, const glm::vec2 &a, const glm::vec2 &b);

        void UpdateModelMatrices(u64 * edges, glm::vec2 *diskPos);
    };
    /* ************************************************************************ */

    void InstancedEdge::SetDefaultProperties()
    {
        // For now an InstancedEdge needs to be initialized as a complete graph
        // with InitCompleteGraph
        if (positions == nullptr)
            throw "'InitCompleteGraph(...) must be explicitly called before Create(...)  (for now)";
    }

    /* Init edge k according to the 2 disks positions a and b */
    void InstancedEdge::EdgePos(int k, const glm::vec2 &a, const glm::vec2 &b)
    {
        // Delta
        float dx = abs(b.x - a.x);
        float dy = abs(b.y - a.y);

        // Position
        a.x < b.x ? positions[k].x = a.x + (dx / 2.0f) : positions[k].x = a.x - (dx / 2.0f);
        a.y < b.y ? positions[k].y = a.y + (dy / 2.0f) : positions[k].y = a.y - (dy / 2.0f);

        // Dimensions
        width[k] = sqrt(dx * dx + dy * dy);
        height[k] = 0.001f;

        // Rotation
        float alpha = (float)atan(dy / dx);
        if (a.x < b.x)
            a.y < b.y ? angle[k] = M_PI - alpha : angle[k] = alpha;
        else
            a.y < b.y ? angle[k] = alpha : angle[k] = M_PI - alpha;
    }

    void InstancedEdge::InitCompleteGraph(glm::vec2 *diskPos, int nb)
    {
        if (diskPos == nullptr)
            throw "InstancedDisk.positions is nullptr when trying to init InstancedEdges with InitPositions";

        diskPositions = diskPos;

        N = nb * (nb - 1) / 2;
        positions = new glm::vec2[N];
        width = new float[N];
        height = new float[N];
        angle = new float[N];

        int k = 0;

        // For every pair of nodes
        for (int i = 0; i < nb - 1; i++)
            for (int j = i + 1; j < nb; j++)
            {
                EdgePos(k, diskPositions[i], diskPositions[j]);
                k++;
            }
    }

    void InstancedEdge::InitFromEdges(std::vector<std::pair<u64, u64>>& edges, glm::vec2 *diskPos)
    {
        if (diskPos == nullptr)
            throw "InstancedDisk.positions is nullptr when trying to init InstancedEdges with InitPositions";

        diskPositions = diskPos;

        N = edges.size();
        positions = new glm::vec2[N];
        width = new float[N];
        height = new float[N];
        angle = new float[N];

        int k = 0;

        for (const auto& edge : edges)
        {
            EdgePos(k, diskPositions[edge.first], diskPositions[edge.second]);
            k++;
        }
    }

    void InstancedEdge::InitFromEdges(u64 * edges, u64 nb_edges, glm::vec2 *diskPos)
    {
        if (diskPos == nullptr)
            throw "InstancedDisk.positions is nullptr when trying to init InstancedEdges with InitPositions";
        if (edges == nullptr)
            throw "Trying to init InstancedEdge with nullptr edges";

        diskPositions = diskPos;

        positions = new glm::vec2[N];
        width = new float[N];
        height = new float[N];
        angle = new float[N];

        for (int i=0 ; i<nb_edges ; i++)
            EdgePos(i, diskPositions[edges[2*i]], diskPositions[edges[2*i+1]]);
    }

    void InstancedEdge::UpdateModelMatrices(u64 * edges, glm::vec2 *diskPos)
    {
        // Update position
        for (int i=0 ; i<N ; i++)
            EdgePos(i, diskPositions[edges[2*i]], diskPositions[edges[2*i+1]]);

        // Update model matrices
        for (int i = 0; i < N; i++)
        {
            modelMatrices[i] = glm::mat4(1.0f);
            modelMatrices[i] = glm::translate(modelMatrices[i], glm::vec3(positions[i], 0.0f));
            modelMatrices[i] = glm::rotate(modelMatrices[i], angle[i], glm::vec3(0.0f, 0.0f, -1.0f));
            modelMatrices[i] = glm::scale(modelMatrices[i], glm::vec3(width[i], height[i], 1.0f));
        }

        // Upload data
        instancedVBO.UpdateData(modelMatrices, N * sizeof(glm::mat4));
    }

    GLfloat *InstancedEdge::CreateCoords()
    {
        int size = 3*4;
        GLfloat *coords = new GLfloat[size]{
            0.5f, 0.5f, 0.0f,   
            0.5f, -0.5f, 0.0f,  
            -0.5f, -0.5f, 0.0f, 
            -0.5f, 0.5f, 0.0f
        };

        CoordsSize = size * sizeof(GLfloat);
        return coords;
    }

    GLfloat *InstancedEdge::CreateTexCoords()
    {
        int size = 2 * 4;
        GLfloat *texcoords = new GLfloat[size] {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
        };

        TexCoordsSize = size * sizeof(GLfloat);
        return texcoords;
    }

    GLfloat *InstancedEdge::CreateNormals()
    {
        int size = TexCoordsSize;
        GLfloat *normals = new GLfloat[size];

        return normals;
    }

    void InstancedEdge::CreateVertices(GLfloat **coords, GLfloat **texcoords)
    {
        *coords = CreateCoords();
        *texcoords = CreateTexCoords();
    }
    void InstancedEdge::CreateVertices(GLfloat **coords, GLfloat **texcoords, GLfloat **normals)
    {

    }

    GLuint *InstancedEdge::CreateElements()
    {
        GLuint *elements = new GLuint[3 * 2]{
            // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        ElementsSize = 3 * 2 * sizeof(GLuint);

        return elements;
    }

}