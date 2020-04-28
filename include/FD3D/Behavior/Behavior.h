#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <FD3D/SceneGraph/Component.h>
#include <FD3D/SceneGraph/SceneNode.h>

#include <FD3D/SceneGraph/Scene.h>

#include <FDCore/Macros.h>

namespace FD3D
{
    class FD_EXPORT Behavior : public Component
    {
        protected:
            FD3D::Scene *m_scene;
            FD3D::SceneNode::id_type m_nodeId;

        public:
            Behavior();

            Behavior(FD3D::Scene *scene, FD3D::SceneNode::id_type nodeId);

            ~Behavior() override = default;

            virtual bool hasScene() const;

            virtual FD3D::Scene *getScene();

            virtual const FD3D::Scene *getScene() const;

            virtual void setScene(FD3D::Scene *scene);

            virtual bool hasNode() const;

            virtual FD3D::SceneNode::id_type getNodeId() const;

            virtual void setNodeId(FD3D::SceneNode::id_type id);

            virtual FD3D::SceneNodeProxy getNode();

            virtual FD3D::ConstSceneNodeProxy getNode() const;

            virtual void init();
            virtual void quit();
            virtual void update();

            virtual void onDisable();
            virtual void onEnable();

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FD3D::Behavior);

#endif // BEHAVIOR_H
