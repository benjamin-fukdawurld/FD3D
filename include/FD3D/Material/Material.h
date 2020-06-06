#ifndef FD3D_MATERIAL_H
#define FD3D_MATERIAL_H

#include <unordered_map>
#include <glm/vec3.hpp>

#include <FDCore/ResourceManager.h>
#include <FDCore/BaseResource.h>
#include <FDCore/EnumFlag.h>

#include <FD3D/Material/AbstractTexture.h>


namespace FD3D
{
    enum class ShadingMode: uint8_t
    {
        Invalid,
        NoShading,
        Flat,
        Gouraud,
        Phong,
        Blinn,
        Toon,
        OrenNayar,
        Minnaert,
        CookTorrance,
        Fresnel
    };

    FD_EXPORT std::string_view shadingModeToString(ShadingMode mode);
    FD_EXPORT ShadingMode shadingModeFromString(std::string_view str);

    enum class BlendingOption: uint16_t
    {
        SourceInvalid = 0,
        SourceZero = 1,
        SourceOne = 2,
        SourceColor = 3,
        SourceAlpha = 4,
        SourceOneMinusColor = 5,
        SourceOneMinusAlpha = 6,
        SourceConstantColor = 7,
        SourceConstantAlpha = 8,
        SourceOneMinusConstantColor = 9,
        SourceOneMinusConstantAlpha = 10,
        DestInvalid = 16,
        DestZero = 32,
        DestOne = 48,
        DestColor = 64,
        DestAlpha = 80,
        DestOneMinusColor = 96,
        DestOneMinusAlpha = 112,
        DestConstantColor = 128,
        DestConstantAlpha = 144,
        DestOneMinusConstantColor = 160,
        DestOneMinusConstantAlpha = 176,
        OperatorInvalid = 256,
        OperatorAdd = 512,
        OperatorSubstract = 768,
        OperatorReverseSubstract = 1024,
        OperatorMin = 1280,
        OperatorMax = 1536,
        SourceMask = 15,
        DestMask = 240,
        OperatorMask = 3840,
        NoBlending = SourceInvalid | DestInvalid | OperatorInvalid,
        Invalid = 32768
    };

    FD_EXPORT std::string_view blendingOptionToString(BlendingOption opt);
    FD_EXPORT BlendingOption blendingOptionFromString(std::string_view str);

    namespace internal
    {
        aiShadingMode shadingModeToAssimpMode(ShadingMode mode);
        ShadingMode shadingModeFromAssimpMode(aiShadingMode mode);
        aiBlendMode blendingFunctionToAssimpMode(uint16_t opt);
        uint16_t blendingFunctionFromAssimpMode(aiBlendMode opt);
    }

    class FD_EXPORT Material : public FDCore::BaseResource
    {
        private:
            enum class MaterialFields: uint16_t
            {
                None = 0,
                HasName = 1,
                HasAmbientColor = 2,
                HasDiffuseColor = 4,
                HasSpecularColor = 8,
                HasEmissiveColor = 16,
                HasTransparentColor = 32,
                HasShininess = 64,
                HasShininessStrength = 128,
                HasOpacity = 256,
                HasRefractionIndex = 512,
                HasShadingMode = 1024,
                IsWireframe = 2048,
                isTwoSided = 4096
            };

            typedef  FDCore::EnumFlag<MaterialFields> MaterialFieldsFlag;

        public:
            typedef FD3D::AbstractTexture* texture_pointer;
            typedef std::vector<texture_pointer> texture_vector;
            typedef std::unordered_map<TextureType, texture_vector> texture_map;

        protected:
            texture_map m_textureMap;
            std::string m_name;
            glm::vec3 m_ambientColor;
            glm::vec3 m_diffuseColor;
            glm::vec3 m_specularColor;
            glm::vec3 m_emissiveColor;
            glm::vec3 m_transparentColor;

            float m_shininess;
            float m_shininessStrength;
            float m_opacity;
            float m_refractionIndex;

            MaterialFieldsFlag m_fieldsFlag;
            uint16_t m_blendingFunc;
            ShadingMode m_shaddingMode;


        public:
            Material();
            Material(std::string_view resourceName);
            Material(std::string_view resourceName, std::string_view resourcePath);
            ~Material() override = default;
            
            bool load() override;
            bool isLoaded() const override;
            void release() override;

            bool hasName() const;
            const std::string &getName() const;
            void setName(std::string_view name);

            bool hasAmbientColor() const;
            glm::vec3 &getAmbientColor();
            const glm::vec3 &getAmbientColor() const;
            void setAmbientColor(const glm::vec3 &ambient);

            bool hasDiffuseColor() const;
            glm::vec3 &getDiffuseColor();
            const glm::vec3 &getDiffuseColor() const;
            void setDiffuseColor(const glm::vec3 &diffuse);

            bool hasSpecularColor() const;
            glm::vec3 &getSpecularColor();
            const glm::vec3 &getSpecularColor() const;
            void setSpecularColor(const glm::vec3 &specular);

            bool hasEmissiveColor() const;
            glm::vec3 &getEmissiveColor();
            const glm::vec3 &getEmissiveColor() const;
            void setEmissiveColor(const glm::vec3 &emissive);

            bool hasTransparentColor() const;
            glm::vec3 &getTransparentColor();
            const glm::vec3 &getTransparentColor() const;
            void setTransparentColor(const glm::vec3 &transparent);

            bool hasShininess() const;
            float getShininess() const;
            void setShininess(float shininess);

            bool hasShininessStrength() const;
            float getShininessStrength() const;
            void setShininessStrength(float strength);

            bool hasOpacity() const;
            float getOpacity() const;
            void setOpacity(float opacity);

            bool hasRefractionIndex() const;
            float getRefractionIndex() const;
            void setRefractionIndex(float index);

            bool hasShaddingMode() const;
            ShadingMode getShaddingMode() const;
            void setShaddingMode(ShadingMode mode);

            bool hasBlending() const;
            BlendingOption getSourceBlendingFactor() const;
            BlendingOption getDestBlendingFactor() const;
            BlendingOption getBlendingOperator() const;
            void setSourceBlendingFactor(BlendingOption func);
            void setDestBlendingFactor(BlendingOption func);
            void setBlendingOperator(BlendingOption func);
            void setBlendingOptions(BlendingOption src, BlendingOption dst, BlendingOption op);
            void setBlendingOptions(uint16_t options);

            bool isWireframe() const;
            void setWireframe(bool value);
            void enableWireframe() { setWireframe(true); }
            void disableWireframe() { setWireframe(false); }

            bool isTwoSided() const;
            void setTwoSided(bool value);
            void enableTwoSided() { setTwoSided(true); }
            void disableTwoSided() { setTwoSided(false); }

            bool hasTextures(TextureType type) const;

            texture_map &getTextureMap();

            const texture_map &getTextureMap() const;

            texture_vector &getTextures(TextureType type);

            const texture_vector &getTextures(TextureType type) const;

            texture_vector &operator[](TextureType type)
            {
                return getTextures(type);
            }

            const texture_vector &operator[](TextureType type) const
            {
                return getTextures(type);
            }

            bool fromMaterial(const aiMaterial *mat, FDCore::ResourceManager &mgr);

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;

        private:
            void addTextures(const aiMaterial *mat, FDCore::ResourceManager &mgr, TextureType type);
    };

    //typedef AssetComponent<FD3D::Material> MaterialComponent;
}

generateTypeCode(FD3D::Material);

#endif // FD3D_MATERIAL_H
