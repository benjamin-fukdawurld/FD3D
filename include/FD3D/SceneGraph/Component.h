#ifndef FD3D_COMPONENT_H
#define FD3D_COMPONENT_H

#include <FDCore/Identifiable.h>
#include <FDCore/TypeInformation.h>

#include <string>

#include <FD3D/SceneGraph/Element.h>

namespace FD3D
{
    class FD_EXPORT Component : public Element
    {
        protected:
            std::string m_name;

        public:
            Component();
            ~Component() override;

            const std::string &getName() const;
            void setName(const std::string &name);

            const char *getTypeCode() const override;
            size_t getTypeCodeHash() const override;
            bool matchTypeCodeHash(size_t hash) const override;
    };

    template<typename AssetType>
    class AssetComponent: public Component
    {
        public:
            typedef AssetType asset_type;

        protected:
            asset_type *m_asset;

        public:
            AssetComponent() : AssetComponent(nullptr) {}
            AssetComponent(asset_type *asset): Component(), m_asset(asset) {}
            ~AssetComponent() override = default;

            bool hasAsset() const { return m_asset != nullptr; }
            asset_type *getAsset() { return m_asset; }
            const asset_type *getAsset() const { return m_asset; }
            void setAsset(asset_type *asset) { m_asset = asset; }

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };

    template<typename AssetType>
    const char *AssetComponent<AssetType>::getTypeCode() const
    {
        return FDCore::TypeCodeHelper<AssetComponent<asset_type>>::code;
    }

    template<typename AssetType>
    size_t AssetComponent<AssetType>::getTypeCodeHash() const
    {
        return FDCore::TypeCodeHelper<AssetComponent<asset_type>>::hash();
    }

    template<typename AssetType>
    bool AssetComponent<AssetType>::matchTypeCodeHash(size_t hash) const
    {
        return hash == FDCore::TypeCodeHelper<AssetComponent<asset_type>>::hash()
                                                                         || Component::matchTypeCodeHash(hash);
    }
}

generateTypeCode(FD3D::Component)

#endif // FD3D_COMPONENT_H
