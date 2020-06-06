#include <FD3D/Material/Material.h>

#include <iostream>

FD3D::Material::Material() :
    FD3D::Material("")
{}

FD3D::Material::Material(std::string_view resourceName) :
    Material(resourceName, "")
{}

FD3D::Material::Material(std::string_view resourceName, std::string_view resourcePath) :
    FDCore::BaseResource(resourceName, resourcePath),
    m_name(""),
    m_ambientColor(1.0f, 1.0f, 1.0f),
    m_diffuseColor(1.0f, 1.0f, 1.0f),
    m_specularColor(1.0f, 1.0f, 1.0f),
    m_emissiveColor(1.0f, 1.0f, 1.0f),
    m_transparentColor(1.0f, 1.0f, 1.0f),
    m_shininess(0.0f),
    m_shininessStrength(1.0f),
    m_opacity(1.0f),
    m_refractionIndex(1.0f),
    m_fieldsFlag(MaterialFields::None),
    m_blendingFunc(0),
    m_shaddingMode(ShadingMode::Invalid)
{}

bool FD3D::Material::load()
{
    return true;
}

bool FD3D::Material::isLoaded() const
{
    return true;
}

void FD3D::Material::release()
{
    m_fieldsFlag = 0;
}

bool FD3D::Material::hasName() const
{
    return m_fieldsFlag[MaterialFields::HasName];
}

const std::string &FD3D::Material::getName() const
{
    return m_name;
}

void FD3D::Material::setName(std::string_view name)
{
    m_name = name;
    m_fieldsFlag |= MaterialFields::HasName;
}

bool FD3D::Material::hasAmbientColor() const
{
    return m_fieldsFlag[MaterialFields::HasAmbientColor];
}

glm::vec3 &FD3D::Material::getAmbientColor()
{
    return m_ambientColor;
}

const glm::vec3 &FD3D::Material::getAmbientColor() const
{
    return m_ambientColor;
}

void FD3D::Material::setAmbientColor(const glm::vec3 &ambient)
{
    m_ambientColor = ambient;
    m_fieldsFlag |= MaterialFields::HasAmbientColor;
}

bool FD3D::Material::hasDiffuseColor() const
{
    return m_fieldsFlag[MaterialFields::HasDiffuseColor];
}

glm::vec3 &FD3D::Material::getDiffuseColor()
{
    return m_diffuseColor;
}

const glm::vec3 &FD3D::Material::getDiffuseColor() const
{
    return m_diffuseColor;
}

void FD3D::Material::setDiffuseColor(const glm::vec3 &diffuse)
{
    m_diffuseColor = diffuse;
    m_fieldsFlag |= MaterialFields::HasDiffuseColor;
}

bool FD3D::Material::hasSpecularColor() const
{
    return m_fieldsFlag[MaterialFields::HasSpecularColor];
}

glm::vec3 &FD3D::Material::getSpecularColor()
{
    return m_specularColor;
}

const glm::vec3 &FD3D::Material::getSpecularColor() const
{
    return m_specularColor;
}

void FD3D::Material::setSpecularColor(const glm::vec3 &specular)
{
    m_specularColor = specular;
    m_fieldsFlag |= MaterialFields::HasSpecularColor;
}

bool FD3D::Material::hasEmissiveColor() const
{
    return m_fieldsFlag[MaterialFields::HasEmissiveColor];
}

glm::vec3 &FD3D::Material::getEmissiveColor()
{
    return m_emissiveColor;
}

const glm::vec3 &FD3D::Material::getEmissiveColor() const
{
    return m_emissiveColor;
}

void FD3D::Material::setEmissiveColor(const glm::vec3 &emissive)
{
    m_emissiveColor = emissive;
    m_fieldsFlag |= MaterialFields::HasEmissiveColor;
}

bool FD3D::Material::hasTransparentColor() const
{
    return m_fieldsFlag[MaterialFields::HasTransparentColor];
}

glm::vec3 &FD3D::Material::getTransparentColor()
{
    return m_transparentColor;
}

const glm::vec3 &FD3D::Material::getTransparentColor() const
{
    return m_transparentColor;
}

void FD3D::Material::setTransparentColor(const glm::vec3 &transparent)
{
    m_transparentColor = transparent;
    m_fieldsFlag |= MaterialFields::HasTransparentColor;
}

bool FD3D::Material::hasShininess() const
{
    return m_fieldsFlag[MaterialFields::HasShininess];
}

float FD3D::Material::getShininess() const
{
    return m_shininess;
}

void FD3D::Material::setShininess(float shininess)
{
    m_shininess = shininess;
    m_fieldsFlag |= MaterialFields::HasShininess;
}

bool FD3D::Material::hasShininessStrength() const
{
    return m_fieldsFlag[MaterialFields::HasShininessStrength];
}

float FD3D::Material::getShininessStrength() const
{
    return m_shininessStrength;
}

void FD3D::Material::setShininessStrength(float strength)
{
    m_shininessStrength = strength;
    m_fieldsFlag |= MaterialFields::HasShininessStrength;
}

bool FD3D::Material::hasOpacity() const
{
    return m_fieldsFlag[MaterialFields::HasOpacity];
}

float FD3D::Material::getOpacity() const
{
    return m_opacity;
}

void FD3D::Material::setOpacity(float opacity)
{
    m_opacity = opacity;
    m_fieldsFlag |= MaterialFields::HasOpacity;
}

bool FD3D::Material::hasRefractionIndex() const
{
    return m_fieldsFlag[MaterialFields::HasRefractionIndex];
}

float FD3D::Material::getRefractionIndex() const
{
    return m_refractionIndex;
}

void FD3D::Material::setRefractionIndex(float index)
{
    m_refractionIndex = index;
    m_fieldsFlag |= MaterialFields::HasRefractionIndex;
}

bool FD3D::Material::hasShaddingMode() const
{
    return m_fieldsFlag[MaterialFields::HasShadingMode];
}

FD3D::ShadingMode FD3D::Material::getShaddingMode() const
{
    return m_shaddingMode;
}

void FD3D::Material::setShaddingMode(FD3D::ShadingMode mode)
{
    m_shaddingMode = mode;
    m_fieldsFlag |= MaterialFields::HasShadingMode;
}

bool FD3D::Material::hasBlending() const
{
    return m_blendingFunc == static_cast<uint16_t>(BlendingOption::NoBlending);
}

FD3D::BlendingOption FD3D::Material::getSourceBlendingFactor() const
{
    return static_cast<BlendingOption>(m_blendingFunc & static_cast<uint16_t>(BlendingOption::SourceMask));
}

FD3D::BlendingOption FD3D::Material::getDestBlendingFactor() const
{
    return static_cast<BlendingOption>(m_blendingFunc & static_cast<uint16_t>(BlendingOption::DestMask));
}

FD3D::BlendingOption FD3D::Material::getBlendingOperator() const
{
    return static_cast<BlendingOption>(m_blendingFunc & static_cast<uint16_t>(BlendingOption::OperatorMask));
}

void FD3D::Material::setSourceBlendingFactor(FD3D::BlendingOption func)
{
    m_blendingFunc = (static_cast<uint16_t>(func) & static_cast<uint16_t>(BlendingOption::SourceMask))
        | (m_blendingFunc &
            (static_cast<uint16_t>(BlendingOption::DestMask) | static_cast<uint16_t>(BlendingOption::OperatorMask)));
}

void FD3D::Material::setDestBlendingFactor(FD3D::BlendingOption func)
{
    m_blendingFunc = (static_cast<uint16_t>(func) & static_cast<uint16_t>(BlendingOption::DestMask))
        | (m_blendingFunc &
           (static_cast<uint16_t>(BlendingOption::SourceMask) | static_cast<uint16_t>(BlendingOption::OperatorMask)));
}

void FD3D::Material::setBlendingOperator(FD3D::BlendingOption func)
{
    m_blendingFunc = (static_cast<uint16_t>(func) & static_cast<uint16_t>(BlendingOption::OperatorMask))
        | (m_blendingFunc &
           (static_cast<uint16_t>(BlendingOption::SourceMask) | static_cast<uint16_t>(BlendingOption::DestMask)));
}

void FD3D::Material::setBlendingOptions(FD3D::BlendingOption src, FD3D::BlendingOption dst, FD3D::BlendingOption op)
{
    m_blendingFunc = (static_cast<uint16_t>(op) & static_cast<uint16_t>(BlendingOption::OperatorMask))
        | (static_cast<uint16_t>(src) & static_cast<uint16_t>(BlendingOption::SourceMask))
        | (static_cast<uint16_t>(dst) & static_cast<uint16_t>(BlendingOption::DestMask));
}

void FD3D::Material::setBlendingOptions(uint16_t options)
{
    m_blendingFunc = options;
}

bool FD3D::Material::isWireframe() const
{
    return m_fieldsFlag[MaterialFields::IsWireframe];
}

void FD3D::Material::setWireframe(bool value)
{
    if(value)
    m_fieldsFlag |= MaterialFields::IsWireframe;
    else
    m_fieldsFlag -= MaterialFields::IsWireframe;
}

bool FD3D::Material::isTwoSided() const
{
    return m_fieldsFlag[MaterialFields::isTwoSided];
}

void FD3D::Material::setTwoSided(bool value)
{
    if(value)
    m_fieldsFlag |= MaterialFields::isTwoSided;
    else
    m_fieldsFlag -= MaterialFields::isTwoSided;
}

bool FD3D::Material::hasTextures(FD3D::TextureType type) const
{
    return m_textureMap.find(type) == m_textureMap.end();
}

FD3D::Material::texture_map &FD3D::Material::getTextureMap()
{
    return m_textureMap;
}

const FD3D::Material::texture_map &FD3D::Material::getTextureMap() const
{
    return m_textureMap;
}

FD3D::Material::texture_vector &FD3D::Material::getTextures(FD3D::TextureType type)
{
    return m_textureMap[type];
}

const FD3D::Material::texture_vector &FD3D::Material::getTextures(FD3D::TextureType type) const
{
    auto it = m_textureMap.find(type);
    return it->second;
}

bool FD3D::Material::fromMaterial(const aiMaterial *mat, FDCore::ResourceManager &mgr)
{
    m_fieldsFlag = 0;
    aiColor3D color;
    aiString str;
    float num;
    int i;

    if(mat->Get(AI_MATKEY_NAME, str) == AI_SUCCESS)
        setName(str.C_Str());

    if(mat->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
        setAmbientColor({color.r, color.g, color.b});

    if(mat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
        setDiffuseColor({color.r, color.g, color.b});

    if(mat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
        setSpecularColor({color.r, color.g, color.b});

    if(mat->Get(AI_MATKEY_COLOR_EMISSIVE, color) == AI_SUCCESS)
        setEmissiveColor({color.r, color.g, color.b});

    if(mat->Get(AI_MATKEY_COLOR_TRANSPARENT, color) == AI_SUCCESS)
        setTransparentColor({color.r, color.g, color.b});

    if(mat->Get(AI_MATKEY_SHININESS, num) == AI_SUCCESS)
        setShininess(num);

    if(mat->Get(AI_MATKEY_SHININESS_STRENGTH, num) == AI_SUCCESS)
        setShininessStrength(num);

    if(mat->Get(AI_MATKEY_OPACITY, num) == AI_SUCCESS)
        setOpacity(num);

    if(mat->Get(AI_MATKEY_REFRACTI, num) == AI_SUCCESS)
        setRefractionIndex(num);

    if(mat->Get(AI_MATKEY_ENABLE_WIREFRAME, i) == AI_SUCCESS)
        setWireframe(i != 0);

    if(mat->Get(AI_MATKEY_TWOSIDED, i) == AI_SUCCESS)
        setTwoSided(i != 0);

    aiShadingMode shad;
    if(mat->Get(AI_MATKEY_SHADING_MODEL, shad) == AI_SUCCESS)
        setShaddingMode(internal::shadingModeFromAssimpMode(shad));

    aiBlendMode blend;
    if(mat->Get(AI_MATKEY_BLEND_FUNC, blend) == AI_SUCCESS)
        m_blendingFunc = internal::blendingFunctionFromAssimpMode(blend);

    addTextures(mat, mgr, FD3D::TextureType::None);
    addTextures(mat, mgr, FD3D::TextureType::Height);
    addTextures(mat, mgr, FD3D::TextureType::Ambient);
    addTextures(mat, mgr, FD3D::TextureType::Diffuse);
    addTextures(mat, mgr, FD3D::TextureType::Invalid);
    addTextures(mat, mgr, FD3D::TextureType::Normals);
    addTextures(mat, mgr, FD3D::TextureType::Opacity);
    addTextures(mat, mgr, FD3D::TextureType::Emissive);
    addTextures(mat, mgr, FD3D::TextureType::LightMap);
    addTextures(mat, mgr, FD3D::TextureType::Specular);
    addTextures(mat, mgr, FD3D::TextureType::Shininess);
    addTextures(mat, mgr, FD3D::TextureType::Reflection);
    addTextures(mat, mgr, FD3D::TextureType::Displacement);

    return true;
}

const char *FD3D::Material::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::Material>::code;
}

size_t FD3D::Material::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::Material>::hash();
}

bool FD3D::Material::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FD3D::Material>::hash()
            || FDCore::BaseResource::matchTypeCodeHash(hash);
}

void FD3D::Material::addTextures(const aiMaterial *mat, FDCore::ResourceManager &mgr, FD3D::TextureType type)
{
    aiTextureType t = internal::textureTypeToAssimpType(type);
    texture_vector &v = m_textureMap[type];
    for(size_t i = 0, imax = mat->GetTextureCount(t); i < imax; ++i)
    {
        aiString path;
        mat->GetTexture(t, static_cast<unsigned int>(i), &path);
        AbstractResource *res = mgr[path.C_Str()];
        if(res == nullptr)
        {
            std::cerr << "Unable find texture '" << path.C_Str() << "'" << std::endl;
            continue;
        }
        v.push_back(static_cast<AbstractTexture*>(res));
    }
}

aiShadingMode FD3D::internal::shadingModeToAssimpMode(FD3D::ShadingMode mode)
{
    switch(mode)
    {
        case ShadingMode::Flat:
        return aiShadingMode_Flat;

        case ShadingMode::Gouraud:
        return aiShadingMode_Gouraud;

        case ShadingMode::Phong:
        return aiShadingMode_Phong;

        case ShadingMode::Blinn:
        return aiShadingMode_Blinn;

        case ShadingMode::Toon:
        return aiShadingMode_Toon;

        case ShadingMode::OrenNayar:
        return aiShadingMode_OrenNayar;

        case ShadingMode::Minnaert:
        return aiShadingMode_Minnaert;

        case ShadingMode::CookTorrance:
        return aiShadingMode_CookTorrance;

        case ShadingMode::Fresnel:
        return aiShadingMode_Fresnel;

        case ShadingMode::NoShading:
        case ShadingMode::Invalid:
        return aiShadingMode_NoShading;
    }

    return aiShadingMode_NoShading;
}

FD3D::ShadingMode FD3D::internal::shadingModeFromAssimpMode(aiShadingMode mode)
{
    switch(mode)
    {
        case aiShadingMode_Flat:
        return ShadingMode::Flat;

        case aiShadingMode_Gouraud:
        return ShadingMode::Gouraud;

        case aiShadingMode_Phong:
        return ShadingMode::Phong;

        case aiShadingMode_Blinn:
        return ShadingMode::Blinn;

        case aiShadingMode_Toon:
        return ShadingMode::Toon;

        case aiShadingMode_OrenNayar:
        return ShadingMode::OrenNayar;

        case aiShadingMode_Minnaert:
        return ShadingMode::Minnaert;

        case aiShadingMode_CookTorrance:
        return ShadingMode::CookTorrance;

        case aiShadingMode_Fresnel:
        return ShadingMode::Fresnel;

        case aiShadingMode_NoShading:
        return ShadingMode::NoShading;

        default:
        return ShadingMode::Invalid;
    }
}

aiBlendMode FD3D::internal::blendingFunctionToAssimpMode(uint16_t opt)
{
    constexpr uint16_t additive =
        static_cast<uint16_t>(BlendingOption::SourceColor)
        | static_cast<uint16_t>(BlendingOption::DestColor)
        | static_cast<uint16_t>(BlendingOption::OperatorAdd);

    if(static_cast<uint16_t>(opt) == additive)
        return aiBlendMode_Additive;

    return aiBlendMode_Default;
}

uint16_t FD3D::internal::blendingFunctionFromAssimpMode(aiBlendMode opt)
{
    if(opt == aiBlendMode_Additive)
    {
        return static_cast<uint16_t>(BlendingOption::SourceColor)
                | static_cast<uint16_t>(BlendingOption::DestColor)
                | static_cast<uint16_t>(BlendingOption::OperatorAdd);
    }

    return static_cast<uint16_t>(BlendingOption::NoBlending);
}

std::string_view FD3D::shadingModeToString(FD3D::ShadingMode mode)
{
    switch(mode)
    {
        case ShadingMode::Flat:
        return "Flat";

        case ShadingMode::Gouraud:
        return "Gouraud";

        case ShadingMode::Phong:
        return "Phong";

        case ShadingMode::Blinn:
        return "Blinn";

        case ShadingMode::Toon:
        return "Toon";

        case ShadingMode::OrenNayar:
        return "OrenNayar";

        case ShadingMode::Minnaert:
        return "Minnaert";

        case ShadingMode::CookTorrance:
        return "CookTorrance";

        case ShadingMode::Fresnel:
        return "Fresnel";

        case ShadingMode::NoShading:
        return "NoShading";

        case ShadingMode::Invalid:
        return "Invalid";
    }

    return "Invalid";
}

FD3D::ShadingMode FD3D::shadingModeFromString(std::string_view str)
{
    if(str == "Flat")
    return ShadingMode::Flat;

    if(str == "Gouraud")
    return ShadingMode::Gouraud;

    if(str == "Phong")
    return ShadingMode::Phong;

    if(str == "Blinn")
    return ShadingMode::Blinn;

    if(str == "Toon")
    return ShadingMode::Toon;

    if(str == "OrenNayar")
    return ShadingMode::OrenNayar;

    if(str == "Minnaert")
    return ShadingMode::Minnaert;

    if(str == "CookTorrance")
    return ShadingMode::CookTorrance;

    if(str == "Fresnel")
    return ShadingMode::Fresnel;

    if(str == "NoShading")
    return ShadingMode::NoShading;

    return ShadingMode::Invalid;
}

std::string_view FD3D::blendingOptionToString(FD3D::BlendingOption opt)
{
    switch(opt)
    {
        case BlendingOption::SourceInvalid:
        return "SourceInvalid";

        case BlendingOption::SourceZero:
        return "SourceZero";

        case BlendingOption::SourceOne:
        return "SourceOne";

        case BlendingOption::SourceColor:
        return "SourceColor";

        case BlendingOption::SourceAlpha:
        return "SourceAlpha";

        case BlendingOption::SourceOneMinusColor:
        return "SourceOneMinusColor";

        case BlendingOption::SourceOneMinusAlpha:
        return "SourceOneMinusAlpha";

        case BlendingOption::SourceConstantColor:
        return "SourceConstantColor";

        case BlendingOption::SourceConstantAlpha:
        return "SourceConstantAlpha";

        case BlendingOption::SourceOneMinusConstantColor:
        return "SourceOneMinusConstantColor";

        case BlendingOption::SourceOneMinusConstantAlpha:
        return "SourceOneMinusConstantAlpha";

        case BlendingOption::DestInvalid:
        return "DestInvalid";

        case BlendingOption::DestZero:
        return "DestZero";

        case BlendingOption::DestOne:
        return "DestOne";

        case BlendingOption::DestColor:
        return "DestColor";

        case BlendingOption::DestAlpha:
        return "DestAlpha";

        case BlendingOption::DestOneMinusColor:
        return "DestOneMinusColor";

        case BlendingOption::DestOneMinusAlpha:
        return "DestOneMinusAlpha";

        case BlendingOption::DestConstantColor:
        return "DestConstantColor";

        case BlendingOption::DestConstantAlpha:
        return "DestConstantAlpha";

        case BlendingOption::DestOneMinusConstantColor:
        return "DestOneMinusConstantColor";

        case BlendingOption::DestOneMinusConstantAlpha:
        return "DestOneMinusConstantAlpha";

        case BlendingOption::OperatorInvalid:
        return "OperatorInvalid";

        case BlendingOption::OperatorAdd:
        return "OperatorAdd";

        case BlendingOption::OperatorSubstract:
        return "OperatorSubstract";

        case BlendingOption::OperatorReverseSubstract:
        return "OperatorReverseSubstract";

        case BlendingOption::OperatorMin:
        return "OperatorMin";

        case BlendingOption::OperatorMax:
        return "OperatorMax";

        case BlendingOption::NoBlending:
        return "NoBlending";

        default:
        return "Invalid";
    }
}

FD3D::BlendingOption FD3D::blendingOptionFromString(std::string_view str)
{
    if(str == "SourceInvalid")
    return BlendingOption::SourceInvalid;

    if(str == "SourceZero")
    return BlendingOption::SourceZero;

    if(str == "SourceOne")
    return BlendingOption::SourceOne;

    if(str == "SourceColor")
    return BlendingOption::SourceColor;

    if(str == "SourceAlpha")
    return BlendingOption::SourceAlpha;

    if(str == "SourceOneMinusColor")
    return BlendingOption::SourceOneMinusColor;

    if(str == "SourceOneMinusAlpha")
    return BlendingOption::SourceOneMinusAlpha;

    if(str == "SourceConstantColor")
    return BlendingOption::SourceConstantColor;

    if(str == "SourceConstantAlpha")
    return BlendingOption::SourceConstantAlpha;

    if(str == "SourceOneMinusConstantColor")
    return BlendingOption::SourceOneMinusConstantColor;

    if(str == "SourceOneMinusConstantAlpha")
    return BlendingOption::SourceOneMinusConstantAlpha;

    if(str == "DestInvalid")
    return BlendingOption::DestInvalid;

    if(str == "DestZero")
    return BlendingOption::DestZero;

    if(str == "DestOne")
    return BlendingOption::DestOne;

    if(str == "DestColor")
    return BlendingOption::DestColor;

    if(str == "DestAlpha")
    return BlendingOption::DestAlpha;

    if(str == "DestOneMinusColor")
    return BlendingOption::DestOneMinusColor;

    if(str == "DestOneMinusAlpha")
    return BlendingOption::DestOneMinusAlpha;

    if(str == "DestConstantColor")
    return BlendingOption::DestConstantColor;

    if(str == "DestConstantAlpha")
    return BlendingOption::DestConstantAlpha;

    if(str == "DestOneMinusConstantColor")
    return BlendingOption::DestOneMinusConstantColor;

    if(str == "DestOneMinusConstantAlpha")
    return BlendingOption::DestOneMinusConstantAlpha;

    if(str == "OperatorInvalid")
    return BlendingOption::OperatorInvalid;

    if(str == "OperatorAdd")
    return BlendingOption::OperatorAdd;

    if(str == "OperatorSubstract")
    return BlendingOption::OperatorSubstract;

    if(str == "OperatorReverseSubstract")
    return BlendingOption::OperatorReverseSubstract;

    if(str == "OperatorMin")
    return BlendingOption::OperatorMin;

    if(str == "OperatorMax")
    return BlendingOption::OperatorMax;

    if(str == "NoBlending")
    return BlendingOption::NoBlending;

    return BlendingOption::Invalid;
}
