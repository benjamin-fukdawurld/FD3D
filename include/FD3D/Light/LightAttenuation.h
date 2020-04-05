#ifndef LIGHTATTENUATION_H
#define LIGHTATTENUATION_H

namespace FD3D
{
    class LightAttenuation
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

#endif // LIGHTATTENUATION_H
