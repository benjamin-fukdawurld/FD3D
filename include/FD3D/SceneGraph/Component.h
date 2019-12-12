#ifndef COMPONENT_H
#define COMPONENT_H

#include <FDCore/Identifiable.h>

namespace FD3D
{
    class Component : FDCore::Identifiable<>
    {
        public:
            Component();
            virtual ~Component();
    };
}

#endif // COMPONENT_H
