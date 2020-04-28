#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <FD3D/SceneGraph/Component.h>
#include <FD3D/SceneGraph/SceneNode.h>

#include <FD3D/SceneGraph/Scene.h>

#include <FDCore/Macros.h>

namespace FD3D
{
    class FD_EXPORT AbstractBehavior : public Component
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

    class FD_EXPORT Behavior : public AbstractBehavior
    {
        protected:
            FD3D::Scene *m_scene;
            FD3D::SceneNode::id_type m_nodeId;

        public:
            Behavior();

            Behavior(FD3D::Scene *scene, FD3D::SceneNode::id_type nodeId);

            ~Behavior() override = default;

            FD3D::Scene *getScene() override;

            const FD3D::Scene *getScene() const override;

            void setScene(FD3D::Scene *scene) override;

            FD3D::SceneNode::id_type getNodeId() const override;

            void setNodeId(FD3D::SceneNode::id_type id) override;

            void init() override;
            void quit() override;
            void update() override;

            void onDisable() override;
            void onEnable() override;

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FD3D::AbstractBehavior);
generateTypeCode(FD3D::Behavior);

#endif // BEHAVIOR_H
