#ifndef FD3D_BEHAVIORCOMPONENT_H
#define FD3D_BEHAVIORCOMPONENT_H

#include <FD3D/Behavior/AbstractBehaviorComponent.h>

namespace FD3D
{
    class FD_EXPORT BehaviorComponent : public AbstractBehaviorComponent
    {
        protected:
            FD3D::Scene *m_scene;
            FD3D::SceneNode::id_type m_nodeId;

        public:
            BehaviorComponent();

            BehaviorComponent(FD3D::Scene *scene, FD3D::SceneNode::id_type nodeId);

            ~BehaviorComponent() override = 0;

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

generateTypeCode(FD3D::BehaviorComponent);

#endif // FD3D_BEHAVIORCOMPONENT_H
