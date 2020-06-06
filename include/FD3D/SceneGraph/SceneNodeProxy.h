#ifndef FD3D_SCENENODEPROXY_H
#define FD3D_SCENENODEPROXY_H

#include <FD3D/SceneGraph/Scene.h>

namespace FD3D
{
    class SceneNodeProxy;
    class ConstSceneNodeProxy;

    namespace internal
    {
        template<typename Derived, typename ConstProxyType = Derived>
        class ConstSceneNodeProxyTrait
        {
            public:
                typedef SceneNode::id_type id_type;

            public:
                const Scene &getScene() const
                {
                    auto &d = asDerived();
                    return d.m_scene;
                }

                const SceneNode &getNode() const
                {
                    auto &d = asDerived();
                    return d.m_node;
                }

                operator bool() const { return asDerived().m_node != nullptr; }

                bool isRoot() const
                {
                    if(!asDerived().m_node)
                        return false;

                    return asDerived().m_scene->getRootId() == asDerived().m_node->getId();
                }

                const SceneNode &operator*() const { return *(asDerived().m_node); }

                const SceneNode *operator->() const { return asDerived().m_node; }


                ConstProxyType getChildAt(id_type index) const
                {
                    auto &d = asDerived();
                    return d.m_scene->getNode(d.m_node->getChildId(index));
                }


                ConstProxyType getParent() const
                {
                    auto &d = asDerived();
                    return d.m_scene->getNode(d.m_node->getParentId());
                }

                std::vector<ConstProxyType> findByName(const std::string &name) const
                {
                    auto &d = asDerived();
                    return d.m_scene->findByName(name, d.m_node->getId());
                }

                std::vector<const Component*> getComponents() const
                {
                    auto &d = asDerived();
                    return d.m_scene->getNodeComponents(d.m_node->getId());
                }

                std::vector<const Component*>
                    getNodeComponents(std::function<bool(const Component*)> pred) const
                {
                    auto &d = asDerived();
                    return d.m_scene->getNodeComponents(d.m_node->getId(), pred);
                }

                template<typename T>
                std::vector<const T*> getComponentsAs() const
                {
                    auto &d = asDerived();
                    return const_cast<const Scene*>(d.m_scene)->getNodeComponentsAs<T>(d.m_node->getId());
                }

            private:
                const Derived &asDerived() const { return *static_cast<const Derived*>(this); }
        };
    }

    class FD_EXPORT SceneNodeProxy : public internal::ConstSceneNodeProxyTrait<ConstSceneNodeProxy>
    {
        friend class internal::ConstSceneNodeProxyTrait<ConstSceneNodeProxy>;

        public:
            typedef SceneNode::id_type id_type;

        protected:
            Scene *m_scene;
            SceneNode *m_node;

        public:
            SceneNodeProxy(Scene &scene, SceneNode *node = nullptr) :
                m_scene(&scene),
                m_node(node)
            {}

            SceneNode &getNode()
            {
                return *m_node;
            }

            template<typename T>
            T *getNodeAs()
            {
                return m_node->as<T>();
            }

            SceneNode &operator*() { return *m_node; }
            SceneNode *operator->() { return m_node; }
            SceneNodeProxy getChildAt(id_type index)
            {
                return m_scene->getNode(m_node->getChildId(index));
            }

            SceneNodeProxy getParent()
            {
                return m_scene->getNode(m_node->getParentId());
            }
            std::vector<SceneNodeProxy> findByName(const std::string &name)
            {
                return m_scene->findByName(name, m_node->getId());
            }

            std::vector<Component*> getNodeComponents()
            {
                return m_scene->getNodeComponents(m_node->getId());
            }

            std::vector<Component *> getNodeComponents(std::function<bool(const Component*)> pred)
            {
                return m_scene->getNodeComponents(m_node->getId(), pred);
            }

            template<typename T>
            std::vector<T*> getComponentsAs()
            {
                return m_scene->getNodeComponentsAs<T>(m_node->getId());
            }
    };

    class FD_EXPORT ConstSceneNodeProxy : public internal::ConstSceneNodeProxyTrait<ConstSceneNodeProxy>
    {
        friend class internal::ConstSceneNodeProxyTrait<ConstSceneNodeProxy>;

        public:
            typedef SceneNode::id_type id_type;

        protected:
            const Scene *m_scene;
            const SceneNode *m_node;

        public:
            ConstSceneNodeProxy(const Scene &scene, const SceneNode *node = nullptr) :
                m_scene(&scene),
                m_node(node)
            {}

            template<typename T>
            const T *getNodeAs()
            {
                return m_node->as<T>();
            }

            ConstSceneNodeProxy(ConstSceneNodeProxy &&other) = default;
            ConstSceneNodeProxy(const ConstSceneNodeProxy &other) = default;
    };
}

#endif // FD3D_SCENENODEPROXY_H
