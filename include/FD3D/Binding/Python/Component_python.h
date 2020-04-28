#ifndef COMPONENT_PYTHON_H
#define COMPONENT_PYTHON_H

#include <FD3D/SceneGraph/Component.h>

#include <pybind11/embed.h>

namespace FD3D
{
    namespace Python
    {
        template<typename ComponentBase = FD3D::Component>
        class PYBIND11_EXPORT PyComponent : public ComponentBase
        {
            public:
                /* Inherit the constructors */
                using ComponentBase::ComponentBase;

                /*  Trampoline (need one for each virtual function) */
                const char *getTypeCode() const override {
                    PYBIND11_OVERLOAD(
                        const char *, /* Return type */
                        ComponentBase,      /* Parent class */
                        getTypeCode,         /* Name of function in C++ (must match Python name) */
                    );
                }

                size_t getTypeCodeHash() const override {
                    PYBIND11_OVERLOAD(
                        size_t, /* Return type */
                        ComponentBase,      /* Parent class */
                        getTypeCodeHash,          /* Name of function in C++ (must match Python name) */
                    );
                }

                bool matchTypeCodeHash(size_t hash) const override {
                    PYBIND11_OVERLOAD(
                        bool, /* Return type */
                        ComponentBase,      /* Parent class */
                        matchTypeCodeHash,          /* Name of function in C++ (must match Python name) */
                        hash      /* Argument(s) */
                    );
                }
        };

        PYBIND11_EXPORT void bind_component(pybind11::module &m);
    }
}

#endif // COMPONENT_PYTHON_H
