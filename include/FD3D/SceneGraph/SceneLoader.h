#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <functional>

#include <FD3D/Texture.h>

#include <FD3D/Scene.h>

namespace FD3D
{
    namespace internal
    {
        const aiScene *importScene(Assimp::Importer &importer,
                                   const std::string &path,
                                   unsigned int flags);
    }

    class AbstractSceneLoader
    {
        protected:
            Assimp::Importer m_importer;

        public:
            AbstractSceneLoader();
            virtual ~AbstractSceneLoader();

            Scene loadModel(const std::string &path,
                            unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs);

            virtual SceneNode loadMeshNode() = 0;
            virtual SceneNode loadModelNode() = 0;
            virtual SceneNode loadMaterialNode() = 0;
            virtual SceneNode loadAnimationNode() = 0;
            virtual SceneNode loadCameraNode() = 0;
            virtual SceneNode loadLightNode() = 0;
    };

    class SceneLoader : public AbstractSceneLoader
    {
        public:
            typedef std::function<Texture(TextureType, const std::string&)> TextureLoaderFunction;

        public:
            SceneLoader();
    };
}

#endif // SCENELOADER_H
