#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

namespace FD3D
{
    class Transform
    {
        protected:
            mutable glm::mat4 m_mat;
            glm::vec3 m_position;
            glm::vec3 m_scale;
            glm::quat m_rotation;
            mutable bool m_isUpToDate;

        public:
            Transform();

            const float *getPtr() const;

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

        protected:
            void generateMatrix() const;
    };
}

#endif // TRANSFORM_H
