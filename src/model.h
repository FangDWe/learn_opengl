#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<vector>
#include"src/shader.h"
#include"src/stb_image.h"

namespace MModel{
    struct Vertex
    {
        glm::vec3 pos;
        glm::vec3 norm;
        glm::vec2 tex;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
    };
    

    struct Texture {
        unsigned int id;
        std::string type;
        aiString path;
    };


    class Mesh {
        public:
            std::vector<Vertex> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<Texture> m_textures;
            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
            void Draw(ShaderProgma shader);
        private:
            unsigned int VAO, VBO, EBO;
            void setupMesh();
    };


    class Model{
        public:
        Model(std::string path, bool gamma);
        void Draw(ShaderProgma shader);
        bool gammaCorrection;
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;
    private:
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path);
    };
}