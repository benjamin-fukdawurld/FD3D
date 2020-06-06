#ifndef FD3D_BASEBEHAVIOR_H
#define FD3D_BASEBEHAVIOR_H


#include <FD3D/Behavior/AbstractBehavior.h>

namespace FD3D
{
    class FD_EXPORT BaseBehavior : public AbstractBehavior
    {
        protected:

            FD3D::Scene *m_scene;
            FD3D::SceneNode::id_type m_nodeId;

        public:
            BaseBehavior();

            BaseBehavior(FD3D::Scene *scene, FD3D::SceneNode::id_type nodeId);

            ~BaseBehavior() override = 0;

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

generateTypeCode(FD3D::BaseBehavior);

#endif // FD3D_BASEBEHAVIOR_H
