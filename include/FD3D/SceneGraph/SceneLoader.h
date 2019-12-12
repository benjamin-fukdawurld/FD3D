#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/light.h>

#include <functional>

#include <FD3D/SceneGraph/Scene.h>
#include <FD3D/SceneGraph/Component.h>
#include <FD3D/Material/Material.h>
#include <FD3D/Light/Light.h>

#include <FDCore/AssociativeContainer.h>

namespace FD3D
{
    namespace internal2
    {
        const aiScene *importScene(Assimp::Importer &importer,
                                   const std::string &path,
                                   unsigned int flags);
    }

    class AbstractSceneLoader
    {
        protected:
            Assimp::Importer m_importer;
            const aiScene *m_scene;
            std::string m_directory;
            std::vector<FD3D::Material> m_materials;
            std::vector<FD3D::Light> m_lights;
            std::unordered_map<std::string, uint32_t> m_textures;

        public:
            AbstractSceneLoader();
            virtual ~AbstractSceneLoader();

            Scene loadScene(const std::string &path,
                            unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs);

            bool loadMaterials();

            const std::string &getDirectory() const { return m_directory; }
            void setDirectory(const std::string &dir) { m_directory = dir; }

        protected:
            virtual uint32_t loadTexture(const std::string &path) = 0;

            virtual bool loadMaterial(const aiMaterial *in);
            virtual bool loadLight(const aiLight *in);

            /*virtual SceneNode loadMeshNode() = 0;
            virtual SceneNode loadModelNode() = 0;
            virtual SceneNode loadAnimationNode() = 0;
            virtual SceneNode loadCameraNode() = 0;
            virtual SceneNode loadLightNode() = 0;*/
    };

    class SceneLoader : public AbstractSceneLoader
    {
        /*public:
            typedef std::function<Texture(TextureType, const std::string&)> TextureLoaderFunction;

        public:
            SceneLoader();*/
    };
}

#endif // SCENELOADER_H
