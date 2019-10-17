#ifndef FD3D_MODELLOADER_H
#define FD3D_MODELLOADER_H

#include <iostream>
#include <queue>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <FD3D/Texture.h>

namespace FD3D
{
    class ModelLoader
    {
        protected:
            Assimp::Importer m_importer;

        public:
            ModelLoader();

            template<typename T>
            T loadModel(const std::string &path,
                        unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs);

        protected:

            template<typename T>
            bool processNodes(const aiScene *scene, T &result);

            template<typename T>
            bool processMesh(const aiMesh *mesh, const aiScene *scene, T &result);
    };

    template<typename T>
    T ModelLoader::loadModel(const std::string &path, unsigned int flags)
    {
        T result;
        const aiScene *scene = m_importer.ReadFile(path, flags);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cerr << "ERROR::ASSIMP::" << m_importer.GetErrorString() << std::endl;
            return result;
        }
        std::string directory = path.substr(0, path.find_last_of('/'));

        if(processNodes(scene, result))
            return T();

        return result;
    }

    template<typename T>
    bool ModelLoader::processNodes(const aiScene *scene, T &result)
    {
        std::queue<const aiNode*> todo;
        todo.push(scene->mRootNode);

        while(!todo.empty())
        {
            const aiNode *current = todo.front();
            todo.pop();

            for(unsigned int i = 0; i < current->mNumChildren; i++)
                todo.push(current->mChildren[i]);

            for(unsigned int i = 0; i < current->mNumMeshes; i++)
            {
                if(!processMesh(scene->mMeshes[current->mMeshes[i]], scene, result))
                    return false;
            }
        }

        return true;
    }

    template<typename T>
    bool ModelLoader::processMesh(const aiMesh *mesh, const aiScene *scene, T &result)
    {
        typedef typename T::MeshType::VertexType VertexType;

        std::vector<VertexType> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            VertexType vertex;
            /*
             *
             */
            vertices.push_back(vertex);
        }
        // process indices


        // process material
        if(mesh->mMaterialIndex > 0)
        {

        }
    }
}

#endif // FD3D_MODELLOADER_H
