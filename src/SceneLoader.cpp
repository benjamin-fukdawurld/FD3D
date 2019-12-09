#include <FD3D/SceneLoader.h>

#include <iostream>

#include <assimp/scene.h>

FD3D::AbstractSceneLoader::AbstractSceneLoader() {}

FD3D::AbstractSceneLoader::~AbstractSceneLoader() {}

FD3D::Scene FD3D::AbstractSceneLoader::loadModel(const std::string &path, unsigned int flags)
{
    Scene result;
    const aiScene *scene = internal::importScene(m_importer, path, flags);
    if(!scene)
        return result;

    std::string directory = path.substr(0, path.find_last_of('/'));


    return result;
}

const aiScene *FD3D::internal::importScene(Assimp::Importer &importer,
                                           const std::string &path,
                                           unsigned int flags)
{
    const aiScene *scene = importer.ReadFile(path, flags);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    return scene;
}
