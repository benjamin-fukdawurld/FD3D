#ifndef LIGHTCONE_H
#define LIGHTCONE_H

namespace FD3D
{
    class LightCone
    {
        protected:
            float m_innerAngle;
            float m_outerAngle;

        public:
            LightCone();
            LightCone(float innerAngle, float outerAngle);

            float getInnerAngle() const;
            void setInnerAngle(float val);

            float getOuterAngle() const;
            void setOuterAngle(float val);
    };
}

#endif // LIGHTCONE_H
