#ifndef FD3D_ABSTRACTBEHAVIOR_H
#define FD3D_ABSTRACTBEHAVIOR_H

#include <FD3D/SceneGraph/Component.h>
#include <FD3D/SceneGraph/SceneNode.h>

#include <FD3D/SceneGraph/Scene.h>

#include <FDCore/Macros.h>
#include <FDCore/Object.h>

namespace FD3D
{
    class FD_EXPORT AbstractBehavior : public FDCore::Object
    {
        public:
            AbstractBehavior() = default;

            ~AbstractBehavior() override = default;

            virtual bool hasScene() const;

            virtual bool hasNode() const;

            virtual FD3D::SceneNodeProxy getNode();

            virtual FD3D::ConstSceneNodeProxy getNode() const;

            virtual FD3D::Scene *getScene() = 0;

            virtual const FD3D::Scene *getScene() const = 0;

            virtual void setScene(FD3D::Scene *scene) = 0;

            virtual FD3D::SceneNode::id_type getNodeId() const = 0;

            virtual void setNodeId(FD3D::SceneNode::id_type id) = 0;

            virtual void init() = 0;
            virtual void quit() = 0;
            virtual void update() = 0;

            virtual void onDisable() = 0;
            virtual void onEnable() = 0;

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FD3D::AbstractBehavior);

#endif // FD3D_ABSTRACTBEHAVIOR_H
