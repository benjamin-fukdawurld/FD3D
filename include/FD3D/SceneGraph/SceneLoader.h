#ifndef FD3D_SCENELOADER_H
#define FD3D_SCENELOADER_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/light.h>
#include <assimp/scene.h>

#include <functional>

#include <FD3D/SceneGraph/SceneManager.h>
#include <FD3D/SceneGraph/Scene.h>
#include <FD3D/SceneGraph/Component.h>
#include <FD3D/Material/MaterialComponent.h>
#include <FD3D/Light/Light.h>
#include <FD3D/Mesh/MeshComponent.h>
#include <FD3D/Camera/Camera.h>

#include <FDCore/AssociativeContainer.h>

#include <FDCore/Macros.h>

namespace FD3D
{
    namespace internal2
    {
        const aiScene *importScene(Assimp::Importer &importer,
                                   const std::string &path,
                                   unsigned int flags);
    }

    class FD_EXPORT AbstractSceneLoader
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
            virtual Scene::node_id_type loadNode(const aiNode *in, Scene &out, Scene::node_id_type parent);

        private:
            virtual AbstractMeshComponent *createMesh() = 0;
    };

    class FD_EXPORT SceneLoader final : public AbstractSceneLoader
    {
        private:
            std::function<uint32_t(const std::string &)> m_textureLoader;
            std::function<uint32_t(const aiTexture*)> m_embeddedTextureLoader;
            std::function<AbstractMeshComponent*()> m_meshAllocator;

        public:
            std::function<uint32_t(const std::string &)> getTextureLoader()
            {
                return m_textureLoader;
            }

            template<typename TextureLoader>
            void setTextureLoader(TextureLoader loader)
            {
                m_textureLoader = loader;
            }

            template<typename TextureLoader, typename ...Args>
            void setTextureLoader(TextureLoader loader, Args ...args)
            {
                m_textureLoader = std::bind(loader, args..., std::placeholders::_1);
            }

            std::function<uint32_t(const aiTexture*)> getEmbeddedTextureLoader()
            {
                return m_embeddedTextureLoader;
            }

            template<typename TextureLoader>
            void setEmbeddedTextureLoader(TextureLoader loader)
            {
                m_embeddedTextureLoader = loader;
            }

            template<typename TextureLoader, typename ...Args>
            void setEmbeddedTextureLoader(TextureLoader loader, Args ...args)
            {
                m_embeddedTextureLoader = std::bind(loader, args..., std::placeholders::_1);
            }



            template<typename MeshAllocator>
            void setMeshAllocator(MeshAllocator allocator)
            {
                m_meshAllocator = allocator;
            }

            template<typename MeshAllocator, typename ...Args>
            void setMeshAllocator(MeshAllocator allocator, Args ...args)
            {
                m_meshAllocator = std::bind(allocator, args...);
            }

        private:
            uint32_t loadTexture(const std::string &path) override final;
            uint32_t loadEmbeddedTexture(const aiTexture *tex) override final;
            AbstractMeshComponent *createMesh() override final;

        public:
            static AbstractMeshComponent *defaultMeshAllocator();
    };

    namespace internal
    {
        FD3D::LightType lightTypeFromAsimpType(aiLightSourceType type);
        glm::vec3 vec3FromAssimpVec3(aiVector3D v);
        glm::vec4 vec4FromAssimpColor3D(aiColor3D c);
    }

    class FD_EXPORT AssetImporter
    {
        protected:
            Assimp::Importer m_importer;
            const aiScene *m_scene;
            std::string m_directory;

            // Resources
            std::vector<std::unique_ptr<Material>> m_materials;
            std::vector<std::unique_ptr<AbstractMesh>> m_meshes;
            std::unordered_map<std::string, std::unique_ptr<AbstractTexture>> m_textures;

            // Components
            std::vector<std::unique_ptr<FD3D::Light>> m_lights;
            std::vector<std::unique_ptr<FD3D::Camera>> m_cameras;
            std::vector<std::unique_ptr<FD3D::Transform>> m_transforms;
            std::vector<std::unique_ptr<AssetComponent<AbstractMesh>>> m_meshComponents;
            std::vector<std::pair<Scene::node_id_type, Scene::component_id_type>> m_meshBindings;

            // Nodes
            std::vector<std::unique_ptr<FD3D::SceneNode>> m_nodes;

            // Callables
            std::function<std::unique_ptr<AbstractMesh>()> m_meshAllocator;
            std::function<std::unique_ptr<AbstractTexture>(const aiScene*, std::string_view, std::string_view)> m_textureLoader;

        public:
            AssetImporter()
            {}

            virtual ~AssetImporter() = default;

            bool import(std::string_view path, SceneManager &mgr, Scene::node_id_type where = 0,
                        unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs);

            template<typename MeshAllocator>
            void setMeshAllocator(MeshAllocator allocator)
            {
                m_meshAllocator = allocator;
            }

            template<typename MeshAllocator, typename ...Args>
            void setMeshAllocator(MeshAllocator allocator, Args ...args)
            {
                m_meshAllocator = std::bind(allocator, args...);
            }

            template<typename TextureAllocator>
            void setTextureAllocator(TextureAllocator allocator)
            {
                m_textureLoader = allocator;
            }

            template<typename TextureAllocator, typename ...Args>
            void setTextureAllocator(TextureAllocator allocator, Args ...args)
            {
                m_textureLoader = std::bind(allocator, args..., std::placeholders::_1);
            }


            static bool isEmbeddedTexture(std::string_view path);

            template<typename MeshType>
            static std::enable_if_t<std::is_base_of_v<AbstractMesh, MeshType>,
            std::unique_ptr<AbstractMesh>> defaultMeshAllocator()
            {
                return std::make_unique<MeshType>();
            }

            template<typename TextureType, typename EmbeddedTextureType>
            static std::enable_if_t<
                std::is_base_of_v<AbstractTexture, TextureType>
                && std::is_base_of_v<AbstractTexture, EmbeddedTextureType>,
            std::unique_ptr<AbstractTexture>> defaultTextureLoader(const aiScene *scene, std::string_view directory, std::string_view name);

        protected:
            virtual bool loadNodes();
            virtual bool loadCameras();
            virtual bool loadMaterials();
            virtual bool loadLights();
            virtual bool loadMeshes();

            virtual bool loadTextures(const aiMaterial *mat, FD3D::TextureType type, Material &out);
            virtual bool loadMaterial(const aiMaterial *mat, FD3D::Material &out);
            virtual bool loadCamera(const aiCamera *cam, Camera &out);
            virtual bool loadLight(const aiLight *light, Light &out);
            virtual bool loadMesh(const aiMesh *mesh, AbstractMesh &out);
            virtual bool loadNode(const aiNode *node, SceneNode *parent, ObjectNode &out);
            virtual bool loadTransform(const aiMatrix4x4 &mat, Transform &trans);
    };

    template<typename TextureType, typename EmbeddedTextureType>
    std::enable_if_t<std::is_base_of_v<AbstractTexture, TextureType> && std::is_base_of_v<AbstractTexture, EmbeddedTextureType>,
    std::unique_ptr<AbstractTexture>> AssetImporter::defaultTextureLoader(const aiScene *scene, std::string_view directory, std::string_view name)
    {
        std::unique_ptr<AbstractTexture> result;
        std::string path(directory);
        path += '/';
        path += name;

        if(isEmbeddedTexture(name))
        {
            size_t index = std::stoul(path.c_str() + 1);
            result  = new EmbeddedTextureType(name, path, scene->mTextures[index]);
        }
        else
            result = new TextureType(name, path);

        if(!result->load())
            result.reset();

        return result;
    }
}

#endif // FD3D_SCENELOADER_H
