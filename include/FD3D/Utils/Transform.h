#ifndef FD3D_TRANSFORM_H
#define FD3D_TRANSFORM_H

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

#include <FD3D/SceneGraph/SceneNode.h>
#include <FD3D/SceneGraph/Component.h>

#include <FDCore/Macros.h>

#include <assimp/matrix4x4.h>

namespace FD3D
{
    class FD_EXPORT Transform : public FD3D::Component
    {
        protected:
            mutable glm::mat4 m_mat;
            glm::vec3 m_position;
            glm::vec3 m_scale;
            glm::quat m_rotation;
            mutable bool m_isUpToDate;

        public:
            Transform();

            Transform(const glm::vec3 &position,
                      const glm::vec3 &scale,
                      const glm::quat &rotation);

            ~Transform() override = default;

            const float *getMatrixPtr() const;

            operator const glm::mat4x4 &() const { return getMatrix(); }

            const glm::mat4x4 &getMatrix() const;

            glm::vec3 &getPosition();
            const glm::vec3 &getPosition() const;
            void setPosition(const glm::vec3 &position);
            void translate(const glm::vec3 &translation);

            glm::vec3 &getScale();
            const glm::vec3 &getScale() const;
            void setScale(const glm::vec3 &scale);
            void setScaleFactor(float scaleFactor);
            void scale(float factor);
            void scale(const glm::vec3 &scale);

            glm::vec3 getEulerAngles() const;

            glm::quat &getRotation();
            const glm::quat &getRotation() const;
            void setRotation(const glm::vec3 &eulerAngles);
            void setRotation(const glm::quat &q);

            void rotate(const glm::vec3 &eulerAngles);
            void rotate(const glm::quat &q);

            glm::vec3 getForward() const;
            glm::vec3 getBackward() const;
            glm::vec3 getLeft() const;
            glm::vec3 getRight() const;
            glm::vec3 getUp() const;
            glm::vec3 getDown() const;

            void invalidate() const;
            bool isUpToDate() const;
            virtual void update() const;

            const char *getTypeCode() const override;
            size_t getTypeCodeHash() const override;
            bool matchTypeCodeHash(size_t hash) const override;

            static glm::mat4 generateMatrix(const glm::vec3 &position,
                                            const glm::vec3 &scale,
                                            const glm::quat &rotation);

            bool fromMatrix(const aiMatrix4x4 &mat);
    };

    typedef EntityNode<Transform> ObjectNode;
}

generateTypeCode(FD3D::Transform);
generateTypeCode(FD3D::ObjectNode);

#endif // FD3D_TRANSFORM_H
