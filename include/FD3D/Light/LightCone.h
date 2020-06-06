#ifndef FD3D_LIGHTCONE_H
#define FD3D_LIGHTCONE_H

#include <FDCore/Macros.h>

namespace FD3D
{
    class FD_EXPORT LightCone
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

#endif // FD3D_LIGHTCONE_H
