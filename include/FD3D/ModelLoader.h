#ifndef FD3D_MODELLOADER_H
#define FD3D_MODELLOADER_H

#include <queue>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <FD3D/Texture.h>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <FD3D/Vertex.h>
#include <FD3D/Model.h>

namespace FD3D
{
    namespace internal
    {
        const aiScene *importScene(Assimp::Importer &importer, const std::string &path,
                            unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs);

        glm::vec3 getVertexPosition(const aiMesh *mesh, size_t vertexIndex);

        glm::vec3 getVertexNormal(const aiMesh *mesh, size_t vertexIndex);

        glm::vec2 getVertexTextureCoordinates(const aiMesh *mesh, size_t vertexIndex, size_t textureIndex);

        std::vector<uint32_t> getMeshIndices(const aiMesh *mesh);

        template<typename NodeCallable, typename ...Args>
        bool browseNodes(const aiScene *scene, NodeCallable nodeProcessor, Args ...args)
        {
            std::queue<const aiNode*> todo;
            todo.push(scene->mRootNode);

            while(!todo.empty())
            {
                const aiNode *current = todo.front();
                todo.pop();

                for(unsigned int i = 0; i < current->mNumChildren; i++)
                    todo.push(current->mChildren[i]);

                if(!nodeProcessor(scene, current, args...))
                    return false;
            }

            return true;
        }

        Vertex defaultVertexGenerator(const aiMesh *mesh, size_t vertexIndex);

        template<typename MeshType, typename VertexGenerator, typename ...Args>
        MeshType defaultMeshGenerator(const aiMesh *mesh, VertexGenerator vertexGenerator, Args ...args)
        {
            typedef typename MeshType::VertexType VertexType;
            std::vector<VertexType> v;
            std::vector<Texture> t;
            v.reserve(mesh->mNumVertices);
            for(size_t i = 0; i < mesh->mNumVertices; ++i)
            {
                v.push_back(vertexGenerator(mesh, i, args...));
            }

            return MeshType{v, getMeshIndices(mesh), t};
        }

        template<typename MeshType>
        Model<MeshType> defaultModelGenerator(const aiScene *scene, const std::string &directory)
        {
            Model<MeshType> result;
            result.setDirectory(directory);

            browseNode(scene, [](const aiScene *scene, const aiNode *node, Model<MeshType> *model){
                for(size_t i = 0; i < node->mNumMeshes; i++)
                    model->addMesh(
                        defaultMeshGenerator<MeshType>(
                            scene->mMeshes[node->mMeshes[i]],
                            defaultVertexGenerator
                        )
                    );
            }, &result);

            return result;
        }
    }

    class ModelLoader
    {
        protected:
            Assimp::Importer m_importer;

        public:
            ModelLoader();

            template<typename T>
            T loadModel(const std::string &path,
                        unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs);

        /*protected:

            template<typename T>
            bool processNodes(const aiScene *scene, T &result);

            template<typename T>
            bool processMesh(const aiMesh *mesh, const aiScene *scene, T &result);*/
    };

    template<typename T>
    T ModelLoader::loadModel(const std::string &path, unsigned int flags)
    {
        T result;
        const aiScene *scene = internal::importScene(m_importer, path, flags);
        if(!scene)
            return result;

        std::string directory = path.substr(0, path.find_last_of('/'));

        return internal::defaultModelGenerator<T>(scene);
    }

    /*template<typename T>
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
    }*/

    /*template<typename T>
    bool ModelLoader::processMesh(const aiMesh *mesh, const aiScene *scene, T &result)
    {
        typedef typename T::MeshType::VertexType VertexType;

        std::vector<VertexType> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            VertexType vertex;
            vertices.push_back(vertex);
        }
        // process indices


        // process material
        if(mesh->mMaterialIndex > 0)
        {

        }
    }*/
}

#endif // FD3D_MODELLOADER_H
