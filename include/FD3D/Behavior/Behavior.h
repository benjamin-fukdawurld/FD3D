#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <FD3D/SceneGraph/Component.h>
#include <FD3D/SceneGraph/SceneNode.h>

#include <FD3D/SceneGraph/Scene.h>

namespace FD3D
{
    class Behavior : public Component
    {
        protected:
            FD3D::Scene *m_scene;
            FD3D::SceneNode::id_type m_nodeId;

        public:
            Behavior();

            Behavior(FD3D::Scene *scene, FD3D::SceneNode::id_type nodeId);

            ~Behavior() override = default;

            bool hasScene() const;

            FD3D::Scene *getScene();

            const FD3D::Scene *getScene() const;

            void setScene(FD3D::Scene *scene);

            bool hasNode() const;

            FD3D::SceneNode::id_type getNodeId() const;

            void setNodeId(FD3D::SceneNode::id_type id);

            FD3D::SceneNodeProxy getNode();

            FD3D::ConstSceneNodeProxy getNode() const;

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
