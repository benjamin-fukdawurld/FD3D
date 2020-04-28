#ifndef TRASFORMSTACK_H
#define TRASFORMSTACK_H

#include <stack>

#include <FD3D/Utils/Transform.h>

#include <FDCore/Macros.h>

namespace FD3D
{
    class FD_EXPORT TransformStack
    {
        public:
            struct TransformData
            {
                glm::vec3 position;
                glm::vec3 scale;
                glm::quat rotation;

                TransformData();

                TransformData(const FD3D::Transform &transform);

                FD3D::Transform toTransform();
            };

        protected:
            std::stack<std::pair<TransformData, glm::mat4>> m_stack;

        public:
            TransformStack() = default;

            TransformData &getCurrentTransformData();

            const TransformData &getCurrentTransformData() const;

            glm::mat4 &getCurrentMatrix();

            const glm::mat4 &getCurrentMatrix() const;

            TransformStack &operator<<(const Transform &trans);

            TransformStack &operator>>(Transform &trans);

            const std::pair<TransformData, glm::mat4> &top() const;

            std::pair<TransformData, glm::mat4> &top();

            void pop();

            void push(const Transform &trans);

            bool empty() const;

            size_t size() const;
    };
}

#endif // TRASFORMSTACK_H
