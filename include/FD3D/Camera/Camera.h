#ifndef FD3D_CAMERA_H
#define FD3D_CAMERA_H

#include <FD3D/SceneGraph/SceneNode.h>
#include <FD3D/Utils/Transform.h>
#include <FD3D/Camera/Projection.h>

#include <FDCore/TypeInformation.h>

namespace FD3D
{
    class Camera : public Transform
    {
        public:
            Projection projection;

        public:
            Camera();

            glm::vec3 getTarget() const { return getBackward(); }

        protected:
            void generateMatrix() const override;
    };

    typedef EntityNode<Camera> CameraNode;
}

generateTypeCode(FD3D::Camera);
generateTypeCode(FD3D::CameraNode);

#endif // FD3D_CAMERA_H
