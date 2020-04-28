#ifndef SCENENODE_PYTHON_H
#define SCENENODE_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/SceneGraph/SceneNode.h>

namespace FD3D
{
    namespace Python
    {
        template<typename SceneNodeBase = FD3D::SceneNode>
        class PYBIND11_EXPORT PySceneNode : public SceneNodeBase
        {
            public:
                /* Inherit the constructors */
                using SceneNodeBase::SceneNodeBase;
            
                /* Trampoline (need one for each virtual function) */
                const char *getTypeCode() const override {
                    PYBIND11_OVERLOAD(
                        const char *, /* Return type */
                        SceneNodeBase,      /* Parent class */
                        getTypeCode         /* Name of function in C++ (must match Python name) */
                    );
                }
                
                size_t getTypeCodeHash() const override {
                    PYBIND11_OVERLOAD(
                        size_t, /* Return type */
                        FD3D::SceneNode,      /* Parent class */
                        getTypeCodeHash          /* Name of function in C++ (must match Python name) */
                    );
                }
                
                bool matchTypeCodeHash(size_t hash) const override {
                    PYBIND11_OVERLOAD(
                        bool, /* Return type */
                        SceneNodeBase,      /* Parent class */
                        matchTypeCodeHash,          /* Name of function in C++ (must match Python name) */
                        hash      /* Argument(s) */
                    );
                }
        };
        
        PYBIND11_EXPORT void bind_node(pybind11::module &m);
        PYBIND11_EXPORT void bind_scenenode(pybind11::module &m);
        PYBIND11_EXPORT void bind_scenenodeproxy(pybind11::module &m);
    }
}

#endif // SCENENODE_PYTHON_H
