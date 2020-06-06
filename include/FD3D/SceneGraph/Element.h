#ifndef ELEMENT_H
#define ELEMENT_H

#include <FDCore/Identifiable.h>
#include <FDCore/Object.h>

namespace FD3D
{
    class FD_EXPORT Element : public FDCore::Identifiable<uintptr_t>, public FDCore::Object
    {
        public:
            Element();
            ~Element() = default;

            const char *getTypeCode() const;
            size_t getTypeCodeHash() const;
            bool matchTypeCodeHash(size_t hash) const;
    };
}

generateTypeCode(FD3D::Element);


#endif // ELEMENT_H
