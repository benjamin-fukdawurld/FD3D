#include <FD3D/Material/MaterialComponent.h>

#include <iostream>

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

FD3D::MaterialComponent::MaterialComponent(FD3D::Material *mat) :
    AssetComponent<FD3D::Material>(mat),
    m_ambientColor(1.0f, 1.0f, 1.0f),
    m_diffuseColor(1.0f, 1.0f, 1.0f),
    m_specularColor(1.0f, 1.0f, 1.0f),
    m_shininess(1.0f),
    m_opacity(1.0f)
{}

FD3D::MaterialComponent::~MaterialComponent() {}

glm::vec3 &FD3D::MaterialComponent::getAmbientColor()
{
    return m_ambientColor;
}

const glm::vec3 &FD3D::MaterialComponent::getAmbientColor() const
{
    return m_ambientColor;
}

void FD3D::MaterialComponent::setAmbientColor(const glm::vec3 &ambient)
{
    m_ambientColor = ambient;
}

glm::vec3 &FD3D::MaterialComponent::getDiffuseColor()
{
    return m_diffuseColor;
}

const glm::vec3 &FD3D::MaterialComponent::getDiffuseColor() const
{
    return m_diffuseColor;
}

void FD3D::MaterialComponent::setDiffuseColor(const glm::vec3 &diffuse)
{
    m_diffuseColor = diffuse;
}

glm::vec3 &FD3D::MaterialComponent::getSpecularColor()
{
    return m_specularColor;
}

const glm::vec3 &FD3D::MaterialComponent::getSpecularColor() const
{
    return m_specularColor;
}

void FD3D::MaterialComponent::setSpecularColor(const glm::vec3 &specular)
{
    m_specularColor = specular;
}

float FD3D::MaterialComponent::getShininess() const
{
    return m_shininess;
}

void FD3D::MaterialComponent::setShininess(float shininess)
{
    m_shininess = shininess;
}

float FD3D::MaterialComponent::getOpacity() const
{
    return m_opacity;
}

void FD3D::MaterialComponent::setOpacity(float opacity)
{
    m_opacity = opacity;
}

const char *FD3D::MaterialComponent::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::MaterialComponent>::code;
}

size_t FD3D::MaterialComponent::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::MaterialComponent>::hash();
}

bool FD3D::MaterialComponent::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FD3D::MaterialComponent>::hash()
            || FD3D::Component::matchTypeCodeHash(hash);
}

bool FD3D::load(const aiMaterial *in, FD3D::MaterialComponent &out, const std::string &directory,
                std::function<uint32_t(std::string)> textureLoader)
{
    auto textureLoop = [in, &out, &directory, textureLoader](TextureType type)
    {
        aiTextureType t = toAssimpType(type);
        for(size_t i = 0, imax = in->GetTextureCount(t); i < imax; ++i)
        {
            aiString path;
            in->GetTexture(t, static_cast<unsigned int>(i), &path);
            uint32_t tex = textureLoader(directory + path.C_Str());
            if(tex == 0)
            {
                std::cerr << "Unable to load texture '" << path.C_Str() << "'" << std::endl;
                continue;
            }
            out.getTextures(type).push_back(tex);
        }
    };

    textureLoop(FD3D::TextureType::None);
    textureLoop(FD3D::TextureType::Height);
    textureLoop(FD3D::TextureType::Ambient);
    textureLoop(FD3D::TextureType::Diffuse);
    textureLoop(FD3D::TextureType::Invalid);
    textureLoop(FD3D::TextureType::Normals);
    textureLoop(FD3D::TextureType::Opacity);
    textureLoop(FD3D::TextureType::Emissive);
    textureLoop(FD3D::TextureType::LightMap);
    textureLoop(FD3D::TextureType::Specular);
    textureLoop(FD3D::TextureType::Shininess);
    textureLoop(FD3D::TextureType::Reflection);
    textureLoop(FD3D::TextureType::Displacement);

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

    float opacity = 1.0;
    if(in->Get(AI_MATKEY_OPACITY, opacity) == AI_SUCCESS)
        out.setOpacity(opacity);

    return true;
}
