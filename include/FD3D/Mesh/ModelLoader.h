#ifndef FD3D_MODELLOADER_H
#define FD3D_MODELLOADER_H

#include <queue>
#include <optional>

#include <FD3D/Material/Texture.h>

#include <FD3D/Mesh/ModelLoader_impl.h>

namespace FD3D
{
    class ModelLoader
    {
        public:
            typedef std::function<Texture(TextureType, const std::string&)> TextureLoaderFunction;

        protected:
            Assimp::Importer m_importer;

        public:
            ModelLoader() {}

            template<typename T>
            T loadModel(const std::string &path,
                        unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs);
    };

    template<typename T>
    T ModelLoader::loadModel(const std::string &path, unsigned int flags)
    {
        T result;
        const aiScene *scene = internal::importScene(m_importer, path, flags);
        if(!scene)
            return result;

        std::string directory = path.substr(0, path.find_last_of('/'));
        DefaultModelLoader<T> loader;

        return loader(scene, directory);
    }
}

#endif // FD3D_MODELLOADER_H
