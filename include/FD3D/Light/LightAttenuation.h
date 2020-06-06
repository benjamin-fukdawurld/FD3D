#ifndef FD3D_LIGHTATTENUATION_H
#define FD3D_LIGHTATTENUATION_H

#include <FDCore/Macros.h>

namespace FD3D
{
    class FD_EXPORT LightAttenuation
    {
        protected:
            float m_constantAttenuation;
            float m_linearAttenuation;
            float m_quadraticAttenuation;

        public:
            LightAttenuation();

            LightAttenuation(float constant, float linear, float quadratic);

            float getConstantAttenuation() const;
            void setConstantAttenuation(float val);

            float getLinearAttenuation() const;
            void setLinearAttenuation(float val);

            float getQuadraticAttenuation() const;
            void setQuadraticAttenuation(float val);

            float getAttenuation(float distance) const;
    };
}

#endif // FD3D_LIGHTATTENUATION_H
