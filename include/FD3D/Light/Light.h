#ifndef FD3D_LIGHT_H
#define FD3D_LIGHT_H

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

#include <FD3D/SceneGraph/SceneNode.h>
#include <FD3D/SceneGraph/Component.h>

#include <FD3D/Light/LightColor.h>
#include <FD3D/Light/LightAttenuation.h>
#include <FD3D/Light/LightCone.h>
#include <FD3D/Light/LightType.h>

#include <FDCore/TypeInformation.h>
#include <FDCore/Macros.h>

#include <assimp/light.h>

namespace FD3D
{
    class FD_EXPORT Light : public FD3D::Component
    {
        public:
            LightColor color;
            LightCone cone;
            LightAttenuation attenuation;

        protected:
            glm::vec3 m_position;
            glm::vec3 m_direction;
            glm::vec3 m_up;
            LightType m_type;

        public:
            Light();

            glm::vec3 &getPosition();
            const glm::vec3 &getPosition() const;
            void setPosition(const glm::vec3 &position);

            glm::vec3 &getDirection();
            const glm::vec3 &getDirection() const;
            void setDirection(const glm::vec3 &direction);

            glm::vec3 &getUp();
            const glm::vec3 &getUp() const;
            void setUp(const glm::vec3 &up);

            void translate(const glm::vec3 &v);
            void rotate(const glm::vec3 &angles);
            void rotate(const glm::quat &quaternion);

            LightType getType() const;
            void setType(const LightType &type);

            const char *getTypeCode() const override;
            size_t getTypeCodeHash() const override;
            bool matchTypeCodeHash(size_t hash) const override;

            bool fromLight(const aiLight *in);
    };

    typedef EntityNode<Light> LightNode;
}

generateTypeCode(FD3D::Light);
generateTypeCode(FD3D::LightNode);

#endif // FD3D_LIGHT_H
