#ifndef FD3D_BEHAVIOR_PYTHON_H
#define FD3D_BEHAVIOR_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/Behavior/BehaviorComponent.h>
#include <FD3D/Behavior/StrategyBehaviorComponent.h>

#include <FD3D/Binding/Python/Component_python.h>

namespace FD3D
{
    namespace Python
    {
        template<typename BehaviorBase = FD3D::BehaviorComponent>
        class PYBIND11_EXPORT PyBehavior : public PyComponent<BehaviorBase>
        {
            public:
                /* Inherit the constructors */
                using PyComponent<BehaviorBase>::PyComponent;

                FD3D::Scene *getScene() override
                {
                    PYBIND11_OVERLOAD(
                        FD3D::Scene*, /* Return type */
                        BehaviorBase,      /* Parent class */
                        getScene,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void setScene(FD3D::Scene *scene) override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        BehaviorBase,      /* Parent class */
                        setScene,         /* Name of function in C++ (must match Python name) */
                        scene
                    );
                }

                FD3D::SceneNode::id_type getNodeId() const override
                {
                    PYBIND11_OVERLOAD(
                        FD3D::SceneNode::id_type, /* Return type */
                        BehaviorBase,      /* Parent class */
                        getNodeId,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void setNodeId(FD3D::SceneNode::id_type id) override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        BehaviorBase,      /* Parent class */
                        setNodeId,         /* Name of function in C++ (must match Python name) */
                        id
                    );
                }

                void init() override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        BehaviorBase,      /* Parent class */
                        init,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void quit() override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        BehaviorBase,      /* Parent class */
                        quit,         /* Name of function in C++ (must match Python name) */
                    );
                }

                /*  Trampoline (need one for each virtual function) */
                void update() override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        BehaviorBase,      /* Parent class */
                        update,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void onDisable() override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        BehaviorBase,      /* Parent class */
                        onDisable,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void onEnable() override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        BehaviorBase,      /* Parent class */
                        onEnable,         /* Name of function in C++ (must match Python name) */
                    );
                }
        };

        PYBIND11_EXPORT void bind_behavior(pybind11::module &m);
    }

    class PYBIND11_EXPORT PythonBehaviorWrapper : public FD3D::AbstractBehaviorComponent
    {
        protected:
            pybind11::object m_self;

        public:
            PythonBehaviorWrapper() = default;
            PythonBehaviorWrapper(pybind11::object self);

            ~PythonBehaviorWrapper() override = default;

            void setSelf(pybind11::object self);
            pybind11::object getSelf();

            FD3D::Scene *getScene() override;

            const FD3D::Scene *getScene() const override;

            void setScene(FD3D::Scene *scene) override;

            FD3D::SceneNode::id_type getNodeId() const override;

            void setNodeId(FD3D::SceneNode::id_type id) override;

            void init() override;
            void quit() override;
            void update() override;

            void onDisable() override;
            void onEnable() override;

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FD3D::PythonBehaviorWrapper);

#endif // FD3D_BEHAVIOR_PYTHON_H
