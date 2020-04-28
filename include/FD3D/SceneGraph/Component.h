#ifndef COMPONENT_H
#define COMPONENT_H

#include <FDCore/Identifiable.h>
#include <FDCore/TypeInformation.h>

#include <string>

#include <FDCore/Macros.h>

namespace FD3D
{
    class FD_EXPORT Component : public FDCore::Identifiable<>
    {
        protected:
            std::string m_name;

        public:
            Component();
            virtual ~Component();

            const std::string &getName() const;
            void setName(const std::string &name);

            template<typename T>
            bool is() const
            {
                return matchTypeCodeHash(FDCore::TypeCodeHelper<T>::hash());
            }

            template<typename T>
            T *as()
            {
                if(!is<T>())
                    return nullptr;

                return static_cast<T*>(this);
            }

            template<typename T>
            const T *as() const
            {
                if(!is<T>())
                    return nullptr;

                return static_cast<T*>(this);
            }

            virtual const char *getTypeCode() const;
            virtual size_t getTypeCodeHash() const;
            virtual bool matchTypeCodeHash(size_t hash) const;
    };
}

#endif // COMPONENT_H
