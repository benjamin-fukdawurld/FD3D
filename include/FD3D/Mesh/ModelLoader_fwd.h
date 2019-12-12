#ifndef MODELLOADER_FWD_H
#define MODELLOADER_FWD_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <FD3D/Utils/Vertex.h>
#include <FD3D/Mesh/Mesh.h>
#include <FD3D/Mesh/Model.h>

#include <FD3D/Material/Texture.h>

#include <functional>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

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
    }

    typedef std::function<Texture(TextureType, const std::string&)> TextureLoaderFunction;

    class DefaultMaterialGenerator
    {
        private:
            TextureLoaderFunction m_textureLoader;

        public:
            DefaultMaterialGenerator(TextureLoaderFunction textureLoader) :
                m_textureLoader(textureLoader)
            {}

            Material operator()(const aiMaterial *mat);

            Texture loadTexture(TextureType type, const std::string &path)
            {
                return m_textureLoader(type, path);
            }
    };

    template<typename VertexType>
    using VertexGeneratorFunction = std::function<VertexType(const aiMesh*, size_t)>;

    template<typename MeshType, typename VertexType = typename MeshType::VertexType>
    using MeshGeneratorFunction = std::function<MeshType(
                                                    const aiMesh*,
                                                    VertexGeneratorFunction<VertexType>
                                                )>;

    template<typename VertexType>
    VertexType generateVertex(const aiMesh *mesh, size_t vertexIndex);

    template<>
    Vertex generateVertex<Vertex>(const aiMesh *mesh, size_t vertexIndex);


    template<typename MeshType>
    MeshType generateMesh(const aiMesh *mesh)
    {
        return generateMesh<MeshType>(mesh, &generateVertex<typename MeshType::VertexType>);
    }

    template<typename MeshType, typename VertexGeneratorType>
    MeshType generateMesh(const aiMesh *mesh, VertexGeneratorType vertexGenerator);

    template<>
    Mesh<Vertex> generateMesh<
        Mesh<Vertex>,
        VertexGeneratorFunction<Vertex>
    >(const aiMesh *mesh, VertexGeneratorFunction<Vertex> vertexGenerator);


    template<typename ModelType>
    ModelType generateModel(const aiScene *scene, const aiNode *node, const std::string &directory)
    {
        return generateModel<ModelType>(scene, node, directory,
                                        &generateMesh<typename ModelType::MeshType>,
                                        &generateVertex<typename ModelType::VertexType>);
    }

    template<typename ModelType, typename MeshGeneratorType, typename VertexGeneratorFunction>
    ModelType generateModel(const aiScene *scene,
                            const aiNode *node,
                            const std::string &directory,
                            MeshGeneratorType meshGenerator,
                            VertexGeneratorFunction vertexGenerator);

    template<>
    Model<Mesh<Vertex>> generateModel<
        Model<Mesh<Vertex>>,
        MeshGeneratorFunction<Mesh<Vertex>>,
        VertexGeneratorFunction<Vertex>
    >(const aiScene *scene, const aiNode *node, const std::string &directory,
      MeshGeneratorFunction<Mesh<Vertex>> meshGenerator,
      VertexGeneratorFunction<Vertex> vertexGenerator);

    template<typename ModelType>
    ModelType loadModel(const aiScene *scene, const std::string &directory)
    {
        return loadModel<ModelType>(scene, directory,
                                    &generateMesh<typename ModelType::MeshType>,
                                    &generateVertex<typename ModelType::VertexType>);
    }

    template<typename ModelType, typename MeshGeneratorType, typename VertexGeneratorFunction>
    ModelType loadModel(const aiScene *scene,
                            const std::string &directory,
                            MeshGeneratorType meshGenerator,
                            VertexGeneratorFunction vertexGenerator);

    template<typename ModelType, typename MeshGeneratorType, typename VertexGeneratorFunction>
    ModelType loadModel(const aiScene *scene,
                            const aiNode *node,
                            const std::string &directory,
                            MeshGeneratorType meshGenerator,
                            VertexGeneratorFunction vertexGenerator);

    template<>
    Model<Mesh<Vertex>> loadModel<
        Model<Mesh<Vertex>>,
        MeshGeneratorFunction<Mesh<Vertex>>,
        VertexGeneratorFunction<Vertex>
    >(const aiScene *scene, const std::string &directory,
      MeshGeneratorFunction<Mesh<Vertex>> meshGenerator,
      VertexGeneratorFunction<Vertex> vertexGenerator);

    template<typename VertexType>
    struct DefaultVertexGenerator
    {
        VertexType operator()(const aiMesh *mesh, size_t vertexIndex);
    };

    template<typename MeshType>
    struct DefaultMeshGenerator
    {
        template<typename VertexType = typename MeshType::VertexType>
        MeshType operator()(const aiMesh *mesh)
        {
            return operator()(mesh, DefaultVertexGenerator<VertexType>());
        }

        template<typename VertexType = typename MeshType::VertexType>
        MeshType operator()(const aiMesh *mesh,
                            VertexGeneratorFunction<VertexType> vertexGenerator);
    };

    template<typename ModelType>
    struct DefaultModelGenerator
    {
        template<typename MeshType = typename ModelType::MeshType,
                 typename VertexType = typename ModelType::VertexType>
        ModelType operator()(const aiScene *scene,
                             const aiNode *node,
                             const std::string &directory)
        {
            return operator()(scene, node, directory,
                              DefaultMeshGenerator<MeshType>(),
                              DefaultVertexGenerator<VertexType>());
        }

        template<typename MeshType = typename ModelType::MeshType,
                 typename VertexType = typename ModelType::VertexType>
        ModelType operator()(const aiScene *scene,
                             const aiNode *node,
                             const std::string &directory,
                             MeshGeneratorFunction<MeshType> meshGenerator,
                             VertexGeneratorFunction<VertexType> vertexGenerator);
    };

    template<typename ModelType>
    struct DefaultModelLoader
    {
        template<typename MeshType = typename ModelType::MeshType,
                 typename VertexType = typename ModelType::VertexType>
        ModelType operator()(const aiScene *scene,
                             const std::string &directory)
        {
            return operator()<MeshType, VertexType>(scene, directory,
                                                    DefaultMeshGenerator<MeshType>(),
                                                    DefaultVertexGenerator<VertexType>());
        }

        template<typename MeshType = typename ModelType::MeshType,
                 typename VertexType = typename ModelType::VertexType>
        ModelType operator()(const aiScene *scene,
                             const std::string &directory,
                             MeshGeneratorFunction<MeshType> meshGenerator,
                             VertexGeneratorFunction<VertexType> vertexGenerator);
    };
}

#endif // MODELLOADER_FWD_H
