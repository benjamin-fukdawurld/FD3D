#ifndef ABSTRACTBEHAVIORGENERATOR_H
#define ABSTRACTBEHAVIORGENERATOR_H

#include <FD3D/Behavior/AbstractBehavior.h>

#include <FDCore/BaseResource.h>

namespace FD3D
{
    class AbstractBehaviorGenerator : public FDCore::BaseResource
    {
        public:
            using BaseResource::BaseResource;

            ~AbstractBehaviorGenerator() override = default;

            virtual std::unique_ptr<AbstractBehavior> generateBehavior(void *data) = 0;
            virtual std::unique_ptr<AbstractBehavior> generateBehavior(FD3D::Scene &scene,
                                                                       FD3D::Scene::node_id_type nodeId,
                                                                       void *data);
            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FD3D::AbstractBehaviorGenerator);


#endif // ABSTRACTBEHAVIORGENERATOR_H
