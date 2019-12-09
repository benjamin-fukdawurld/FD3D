#ifndef FD3D_CAMERA_H
#define FD3D_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

#include <FD3D/SceneNode.h>

#include <FDCore/TypeInformation.h>

namespace FD3D
{
    class Camera
    {
        protected:
            mutable glm::mat4 m_mat;
            glm::vec3 m_position;
            glm::quat m_rotation;
            mutable bool m_isUpToDate;

        public:
            Camera();

            const float *getPtr() const;

            operator const glm::mat4x4 &() const { return getMatrix(); }

            const glm::mat4x4 &getMatrix() const;

            glm::vec3 &getPosition();
            const glm::vec3 &getPosition() const;
            void setPosition(const glm::vec3 &position);

            void translate(const glm::vec3 &v);

            glm::vec3 getEulerAngles() const;

            glm::quat &getRotation();
            const glm::quat &getRotation() const;
            void setRotation(const glm::vec3 &eulerAngles);
            void setRotation(const glm::quat &q);

            void rotate(const glm::vec3 &eulerAngles);
            void rotate(const glm::quat &q);

            glm::vec3 getUpVector() const;
            glm::vec3 getTarget() const;


        protected:
            void generateMatrix() const;
    };

    typedef EntityNode<Camera> CameraNode;

}

generateTypeCode(FD3D::Camera);
generateTypeCode(FD3D::CameraNode);

#endif // FD3D_CAMERA_H
