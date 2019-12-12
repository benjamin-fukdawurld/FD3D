#include <FD3D/SceneGraph/SceneLoader.h>

#include <iostream>

#include <assimp/scene.h>


static aiTextureType toAssimpType(FD3D::TextureType type)
{
    switch (type)
    {
        case FD3D::TextureType::None:
            return aiTextureType_NONE;

        case FD3D::TextureType::Height:
            return aiTextureType_HEIGHT;

        case FD3D::TextureType::Ambient:
            return aiTextureType_AMBIENT;

        case FD3D::TextureType::Diffuse:
            return aiTextureType_DIFFUSE;

        case FD3D::TextureType::Normals:
            return aiTextureType_NORMALS;

        case FD3D::TextureType::Opacity:
            return aiTextureType_OPACITY;

        case FD3D::TextureType::Emissive:
            return aiTextureType_EMISSIVE;

        case FD3D::TextureType::LightMap:
            return aiTextureType_LIGHTMAP;

        case FD3D::TextureType::Specular:
            return aiTextureType_SPECULAR;

        case FD3D::TextureType::Shininess:
            return aiTextureType_SHININESS;

        case FD3D::TextureType::Reflection:
            return aiTextureType_REFLECTION;

        case FD3D::TextureType::Displacement:
            return aiTextureType_DISPLACEMENT;

        case FD3D::TextureType::Invalid:
            return aiTextureType_UNKNOWN;
    }

    return aiTextureType_UNKNOWN;
}




FD3D::AbstractSceneLoader::AbstractSceneLoader() {}

FD3D::AbstractSceneLoader::~AbstractSceneLoader() {}

FD3D::Scene FD3D::AbstractSceneLoader::loadScene(const std::string &path, unsigned int flags)
{
    Scene result;
    m_scene = internal2::importScene(m_importer, path, flags);
    if(!m_scene)
        return result;

    m_directory = path.substr(0, path.find_last_of('/'));

    return result;
}

bool FD3D::AbstractSceneLoader::loadMaterials()
{
    for(size_t i = 0, imax = m_scene->mNumMaterials; i < imax; ++i)
    {
        if(!loadMaterial(m_scene->mMaterials[i]))
            return false;
    }

    return true;
}

bool FD3D::AbstractSceneLoader::loadMaterial(const aiMaterial *in)
{
    Material out;
    auto textureLoop = [in, &out, this](TextureType type)
    {
        aiTextureType t = toAssimpType(type);
        for(size_t i = 0, imax = in->GetTextureCount(t); i < imax; ++i)
        {
            aiString path;
            in->GetTexture(t, static_cast<unsigned int>(i), &path);
            std::string texpath = this->getDirectory() + path.C_Str();

            uint32_t tex = 0;
            auto it = m_textures.find(texpath);
            if(it != m_textures.end())
                tex = it->second;
            else
            {
                tex = this->loadTexture(texpath);
                if(tex == 0)
                {
                    std::cerr << "Unable to load texture '" << texpath << "'" << std::endl;
                    return false;
                }

                m_textures[texpath] = tex;
            }

            out.getTextures(type).push_back(tex);
        }

        return true;
    };

    if(
       !(
           textureLoop(FD3D::TextureType::None)
        && textureLoop(FD3D::TextureType::Height)
        && textureLoop(FD3D::TextureType::Ambient)
        && textureLoop(FD3D::TextureType::Diffuse)
        && textureLoop(FD3D::TextureType::Invalid)
        && textureLoop(FD3D::TextureType::Normals)
        && textureLoop(FD3D::TextureType::Opacity)
        && textureLoop(FD3D::TextureType::Emissive)
        && textureLoop(FD3D::TextureType::LightMap)
        && textureLoop(FD3D::TextureType::Specular)
        && textureLoop(FD3D::TextureType::Shininess)
        && textureLoop(FD3D::TextureType::Reflection)
        && textureLoop(FD3D::TextureType::Displacement)
        )
       )
       return false;

    aiColor3D color;
    aiString name;
    float shininess;

    if(in->Get(AI_MATKEY_NAME, name) == AI_SUCCESS)
        out.setName(name.C_Str());

    if(in->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
        out.setShininess(shininess);

    if(in->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
        out.setDiffuseColor({color.r, color.g, color.b});

    if(in->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
        out.setAmbientColor({color.r, color.g, color.b});

    if(in->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
        out.setSpecularColor({color.r, color.g, color.b});

    m_materials.push_back(std::move(out));

    return true;
}

bool FD3D::AbstractSceneLoader::loadLight(const aiLight *in)
{
    Light out;
    out.setName(in->mName.C_Str());
    out.setPosition(
        {
            in->mPosition.x,
            in->mPosition.y,
            in->mPosition.z
        }
    );

    out.setDirection(
        {
            in->mDirection.x,
            in->mDirection.y,
            in->mDirection.z
        }
    );

    out.setUp(
        {
            in->mUp.x,
            in->mUp.y,
            in->mUp.z
        }
    );

    out.setAmbientColor(
        {
            in->mColorAmbient.r,
            in->mColorAmbient.g,
            in->mColorAmbient.b,
            1.0f
        }
    );

    out.setDiffuseColor(
        {
            in->mColorDiffuse.r,
            in->mColorDiffuse.g,
            in->mColorDiffuse.b,
            1.0f
        }
    );

    out.setSpecularColor(
        {
            in->mColorSpecular.r,
            in->mColorSpecular.g,
            in->mColorSpecular.b,
            1.0f
        }
    );

    return true;
}

const aiScene *FD3D::internal2::importScene(Assimp::Importer &importer,
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
