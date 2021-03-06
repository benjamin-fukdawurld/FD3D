#ifndef FD3D_PROJECTION_H
#define FD3D_PROJECTION_H

#include <cstdint>
#include <glm/mat4x4.hpp>

#include <FD3D/Camera/ProjectionType.h>

#include <FDCore/Macros.h>

namespace FD3D
{
    class FD_EXPORT Projection
    {
        protected:
            mutable glm::mat4 m_mat;
            float m_left;
            float m_right;
            float m_bottom;
            float m_top;
            float m_fov;
            float m_near;
            float m_far;
            ProjectionType m_type;
            mutable bool m_isUpToDate;

        public:
            Projection();

            const float *getMatrixPtr() const;

            operator const glm::mat4x4 &() const { return getMatrix(); }

            const glm::mat4x4 &getMatrix() const;

            float getLeft() const;
            void setLeft(float left);
            float getRight() const;
            void setRight(float right);
            float getWidth() const;
            void setWidth(float w);

            float getBottom() const;
            void setBottom(float bottom);
            float getTop() const;
            void setTop(float top);
            float getHeight() const;
            void setHeight(float h);

            float getAspectRatio() const { return getWidth() / getHeight(); }

            float getNear() const;
            void setNear(float near);
            float getFar() const;
            void setFar(float far);
            float getFov() const;
            void setFov(float fov);

            ProjectionType getType() const;
            void setType(const ProjectionType &type);

            void invalidate() const;
            bool isUptoDate() const;
            virtual void update() const;

        protected:
            void generateMatrix() const;
    };
}

#endif // FD3D_PROJECTION_H
