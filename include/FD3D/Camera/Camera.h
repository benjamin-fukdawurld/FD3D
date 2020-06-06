#ifndef FD3D_CAMERA_H
#define FD3D_CAMERA_H

#include <FD3D/SceneGraph/SceneNode.h>
#include <FD3D/Utils/Transform.h>
#include <FD3D/Camera/Projection.h>

#include <FDCore/TypeInformation.h>
#include <FDCore/ResourceManager.h>
#include <FDCore/Macros.h>

#include <assimp/camera.h>

namespace FD3D
{
    class FD_EXPORT Camera : public Transform
    {
        public:
            Projection projection;

        public:
            Camera() = default;

            glm::vec3 getTarget() const { return getBackward(); }
            void setTarget(const glm::vec3 &target);

            void update() const override;

            const char *getTypeCode() const override;
            size_t getTypeCodeHash() const override;
            bool matchTypeCodeHash(size_t hash) const override;

            static glm::mat4 generateLookAtMatrix(const glm::vec3 &position,
                                                  const glm::vec3 &target,
                                                  const glm::vec3 &up);

            bool fromCamera(const aiCamera *cam);
    };

    typedef EntityNode<Camera> CameraNode;
}

generateTypeCode(FD3D::Camera);
generateTypeCode(FD3D::CameraNode);

#endif // FD3D_CAMERA_H
