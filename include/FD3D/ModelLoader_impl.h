#ifndef MODELLOADER_IMPL_H
#define MODELLOADER_IMPL_H

#include <FD3D/ModelLoader_fwd.h>

namespace FD3D
{
    template<typename VertexType>
    VertexType DefaultVertexGenerator<VertexType>::operator()(const aiMesh *mesh,
                                                              size_t vertexIndex)
    {
        return generateVertex<VertexType>(mesh, vertexIndex);
    }

    template<typename MeshType>
    template<typename VertexType>
    MeshType DefaultMeshGenerator<MeshType>::operator()(const aiMesh *mesh,
                        VertexGeneratorFunction<VertexType> vertexGenerator)
    {
        return generateMesh<MeshType, VertexGeneratorFunction<VertexType>>(mesh, vertexGenerator);
    }

    template<typename ModelType>
    template<typename MeshType, typename VertexType>
    ModelType DefaultModelGenerator<ModelType>::operator()(const aiScene *scene,
                         const aiNode *node,
                         const std::string &directory,
                         MeshGeneratorFunction<MeshType> meshGenerator,
                         VertexGeneratorFunction<VertexType> vertexGenerator)
    {
        return generateModel<
                    MeshGeneratorFunction<MeshType>,
                    VertexGeneratorFunction<VertexType>
                >(scene, node, directory, meshGenerator, vertexGenerator);
    }

    template<typename ModelType>
    template<typename MeshType, typename VertexType>
    ModelType DefaultModelLoader<ModelType>::operator()(const aiScene *scene,
                         const std::string &directory,
                         MeshGeneratorFunction<MeshType> meshGenerator,
                         VertexGeneratorFunction<VertexType> vertexGenerator)
    {
        return loadModel<ModelType,
                         MeshGeneratorFunction<MeshType>,
                         VertexGeneratorFunction<VertexType>>(
            scene, directory, meshGenerator, vertexGenerator
        );
    }
}

#endif // MODELLOADER_IMPL_H
