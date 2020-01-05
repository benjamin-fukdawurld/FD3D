#ifndef SCENE_H
#define SCENE_H

#include <FD3D/SceneGraph/SceneNode.h>
#include <FD3D/SceneGraph/Component.h>

#include <FDCore/AssociativeContainer.h>

#include <memory>

namespace FD3D
{
    class SceneNodeProxy;
    class ConstSceneNodeProxy;

    class Scene
    {
        public:
            typedef SceneNode::id_type id_type;

        protected:
            FDCore::AssociativeContainer<Component::id_type, std::unique_ptr<Component>> m_components;
            FDCore::AssociativeContainer<Component::id_type, std::unique_ptr<SceneNode>> m_nodes;
            FDCore::AssociativeContainer<id_type, Component::id_type> m_componentBindings;
            id_type m_rootId;

        public:
            Scene();

            id_type getRootId() const;

            SceneNodeProxy getNode(id_type id);
            ConstSceneNodeProxy getNode(id_type id) const;

            void addNode(SceneNode *node);
            void removeNode(id_type id);
            void removeNodeAt(size_t pos);

            bool hasNodes() const;
            void clearNodes();
            size_t getNodeCount() const;

            template<typename T, typename ...Args>
            void emplaceNode(Args... args)
            {
                addNode(std::make_unique<T>(args...));
            }

            std::vector<SceneNodeProxy> findByName(const std::string &name,
                                                   id_type from = 0);
            std::vector<ConstSceneNodeProxy> findByName(const std::string &name,
                                                        id_type from = 0) const;

            Component *getComponent(Component::id_type id);
            const Component *getComponent(Component::id_type id) const;

            template<typename T>
            std::vector<T*> getComponentsAs()
            {
                typedef FDCore::AssociativeContainer<
                            Component::id_type,
                            std::unique_ptr<Component>
                        >::cell_type cell_type;

                typedef std::vector<FDCore::AssociativeContainer<
                            Component::id_type,
                            std::unique_ptr<Component>
                        >::iterator> component_vector;

                component_vector components = m_components.find_all_if([](const cell_type &c){
                    return c.value->as<T>();
                });

                std::vector<T*> result;
                result.reserve(components.size());
                for(size_t i = 0, imax = components.size(); i < imax; ++i)
                    result.push_back(components[i]->value->as<T>());

                return result;
            }

            void addComponent(Component *node);
            void removeComponent(Component::id_type id);
            void removeComponentAt(size_t pos);

            bool hasComponents() const;
            void clearComponents();
            size_t getComponentCount() const;

            template<typename T, typename ...Args>
            void emplaceComponent(Args... args)
            {
                auto p = std::make_unique<T>(args...);
                m_components.insert(p->getId(), std::move(p));
            }

            std::vector<Component*> findComponentsByName(const std::string &name);
            std::vector<const Component*> findComponentsByName(const std::string &name) const;

            void bindComponent(id_type node, Component::id_type comp);
            void unbindComponent(id_type node, Component::id_type comp);

            std::vector<Component::id_type> getNodeComponentIds(id_type node) const;

            std::vector<Component::id_type>
                getNodeComponentIds(id_type node, std::function<bool(const Component*)> pred) const;

            std::vector<Component*> getNodeComponents(id_type node);
            std::vector<const Component*> getNodeComponents(id_type node) const;

            std::vector<Component *> getNodeComponents(id_type node,
                                                      std::function<bool(const Component*)> pred);
            std::vector<const Component*>
                getNodeComponents(id_type node, std::function<bool(const Component*)> pred) const;

            template<typename T>
            std::vector<T*> getNodeComponentsAs(id_type node)
            {
                std::vector<T*> result;
                for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
                {
                    T *c = getComponent(it->value)->as<T>();
                    result.push_back();
                }

                return result;
            }

            template<typename T>
            std::vector<const T*> getNodeComponentsAs(id_type node) const
            {
                std::vector<const T*> result;
                for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
                {
                    const T *c = getComponent(it->value)->as<T>();
                    result.push_back();
                }

                return result;
            }

        private:
            void removeHierarchy(id_type id);
    };

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

                ConstProxyType &getNode() const
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

            private:
                const Derived &asDerived() const { return *static_cast<const Derived*>(this); }
        };
    }

    class SceneNodeProxy : public internal::ConstSceneNodeProxyTrait<ConstSceneNodeProxy>
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
    };

    class ConstSceneNodeProxy : public internal::ConstSceneNodeProxyTrait<ConstSceneNodeProxy>
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

            ConstSceneNodeProxy(ConstSceneNodeProxy &&other) = default;
            ConstSceneNodeProxy(const ConstSceneNodeProxy &other) = default;
    };
}

#endif // SCENE_H
