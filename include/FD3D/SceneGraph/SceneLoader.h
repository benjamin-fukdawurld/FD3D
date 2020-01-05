#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/light.h>
#include <assimp/scene.h>

#include <functional>

#include <FD3D/SceneGraph/Scene.h>
#include <FD3D/SceneGraph/Component.h>
#include <FD3D/Material/Material.h>
#include <FD3D/Light/Light.h>
#include <FD3D/Mesh/Mesh.h>
#include <FD3D/Camera/Camera.h>

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
            std::vector<Component::id_type> m_materials;
            std::vector<SceneNode::id_type> m_lights;
            std::vector<SceneNode::id_type> m_cameras;
            std::vector<Component::id_type> m_meshes;
            FDCore::AssociativeContainer<std::string, uint32_t> m_textures;

        public:
            AbstractSceneLoader();
            virtual ~AbstractSceneLoader();

            bool loadScene(Scene &result, const std::string &path,
                            unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs);

            bool loadMaterials(Scene &out);
            bool loadMeshes(Scene &out);
            bool loadLights(Scene &out);
            bool loadCameras(Scene &out);
            bool loadNodes(Scene &out);

            const std::string &getDirectory() const { return m_directory; }
            void setDirectory(const std::string &dir) { m_directory = dir; }

        protected:
            virtual uint32_t loadTexture(const std::string &path) = 0;
            virtual uint32_t loadEmbeddedTexture(const aiTexture *tex) = 0;

            virtual bool loadMaterial(const aiMaterial *in, Scene &out);
            virtual bool loadLight(const aiLight *in, Scene &out);
            virtual bool loadCamera(const aiCamera *in, Scene &out);
            virtual bool loadMesh(const aiMesh *in, Scene &out);
            virtual Scene::id_type loadNode(const aiNode *in, Scene &out, Scene::id_type parent);

        private:
            virtual AbstractMesh *createMesh() = 0;
    };

    class SceneLoader : public AbstractSceneLoader
    {
        protected:
            std::function<uint32_t(const std::string &)> m_textureLoader;
            std::function<uint32_t(const aiTexture*)> m_embeddedTextureLoader;

        public:
            std::function<uint32_t(const std::string &)> getTextureLoader();
            void setTextureLoader(std::function<uint32_t(const std::string &)> loader);

            std::function<uint32_t(const aiTexture*)> getEmbeddedTextureLoader();
            void setEmbeddedTextureLoader(std::function<uint32_t(const aiTexture*)> loader);

        private:
            uint32_t loadTexture(const std::string &path) override;
            uint32_t loadEmbeddedTexture(const aiTexture *tex) override;
            AbstractMesh *createMesh() override;
    };
}

#endif // SCENELOADER_H