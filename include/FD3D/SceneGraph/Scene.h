#ifndef FD3D_SCENE_H
#define FD3D_SCENE_H

#include <FD3D/SceneGraph/SceneNode.h>
#include <FD3D/SceneGraph/Component.h>

#include <FDCore/AssociativeContainer.h>

#include <memory>

#include <FDCore/Macros.h>

namespace FD3D
{
    class SceneNodeProxy;
    class ConstSceneNodeProxy;

    class FD_EXPORT Scene
    {
        public:
            typedef SceneNode::id_type node_id_type;
            typedef Component::id_type component_id_type;
            typedef std::unique_ptr<SceneNode> NodePtr;
            typedef std::unique_ptr<Component> ComponentPtr;
            typedef FDCore::AssociativeContainer<component_id_type, ComponentPtr> ComponentMap;
            typedef FDCore::AssociativeContainer<node_id_type, NodePtr> NodeMap;
            typedef FDCore::AssociativeContainer<node_id_type, component_id_type> BindingMap;


        protected:
            ComponentMap m_components;
            NodeMap m_nodes;
            BindingMap m_componentBindings;
            node_id_type m_rootId;

        public:
            Scene();
            Scene(const Scene&) = delete;

            Scene &operator=(const Scene&) = delete;

            node_id_type getRootId() const;
            const ComponentMap &getComponents() const;
            const NodeMap &getNodes() const;
            const BindingMap &getBindings() const;

            void clear();

            SceneNodeProxy getRootNode();
            ConstSceneNodeProxy getRootNode() const;
            SceneNodeProxy getNode(node_id_type id);
            ConstSceneNodeProxy getNode(node_id_type id) const;

            void addNode(SceneNode *node);
            void removeNode(node_id_type id);
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
                                                   node_id_type from = 0);
            std::vector<ConstSceneNodeProxy> findByName(const std::string &name,
                                                        node_id_type from = 0) const;

            Component *getComponent(Component::id_type id);
            const Component *getComponent(Component::id_type id) const;

            template<typename T>
            std::vector<T*> getNodesAs()
            {
                typedef NodeMap::cell_type cell_type;

                typedef std::vector<NodeMap::iterator> node_vector;

                node_vector nodes = m_nodes.find_all_if([](const cell_type &c){
                    return c.value->as<T>();
                });

                std::vector<T*> result;
                result.reserve(nodes.size());
                for(size_t i = 0, imax = nodes.size(); i < imax; ++i)
                    result.push_back(nodes[i]->value->as<T>());

                return result;
            }

            template<typename T>
            std::vector<const T*> getNodesAs() const
            {
                typedef NodeMap::cell_type cell_type;

                typedef std::vector<NodeMap::const_iterator> node_vector;

                node_vector nodes = m_nodes.find_all_if([](const cell_type &c){
                    return c.value->as<T>();
                });

                std::vector<const T*> result;
                result.reserve(nodes.size());
                for(size_t i = 0, imax = nodes.size(); i < imax; ++i)
                    result.push_back(nodes[i]->value->as<T>());

                return result;
            }

            template<typename T>
            std::vector<T*> getComponentsAs()
            {
                typedef ComponentMap::cell_type cell_type;

                typedef std::vector<ComponentMap::iterator> component_vector;

                component_vector components = m_components.find_all_if([](const cell_type &c){
                    return c.value->as<T>();
                });

                std::vector<T*> result;
                result.reserve(components.size());
                for(size_t i = 0, imax = components.size(); i < imax; ++i)
                    result.push_back(components[i]->value->as<T>());

                return result;
            }

            template<typename T>
            std::vector<const T*> getComponentsAs() const
            {
                typedef ComponentMap::cell_type cell_type;

                typedef std::vector<ComponentMap::const_iterator> component_vector;

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

            void bindComponent(node_id_type node, Component::id_type comp);
            void unbindComponent(node_id_type node, Component::id_type comp);

            std::vector<Component::id_type> getNodeComponentIds(node_id_type node) const;

            std::vector<Component::id_type>
                getNodeComponentIds(node_id_type node, std::function<bool(const Component*)> pred) const;

            std::vector<Component*> getNodeComponents(node_id_type node);
            std::vector<const Component*> getNodeComponents(node_id_type node) const;

            std::vector<Component *> getNodeComponents(node_id_type node,
                                                      std::function<bool(const Component*)> pred);
            std::vector<const Component*>
                getNodeComponents(node_id_type node, std::function<bool(const Component*)> pred) const;

            template<typename T>
            std::vector<T*> getNodeComponentsAs(node_id_type node)
            {
                std::vector<T*> result;
                for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
                {
                    T *c = getComponent(it->value)->as<T>();
                    if(c != nullptr)
                        result.push_back(c);
                }

                return result;
            }

            template<typename T>
            std::vector<const T*> getNodeComponentsAs(node_id_type node) const
            {
                std::vector<const T*> result;
                for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
                {
                    const T *c = getComponent(it->value)->as<T>();
                    if(c != nullptr)
                        result.push_back(c);
                }

                return result;
            }

            std::vector<SceneNodeProxy> getBoundNodes(component_id_type comp);
            std::vector<ConstSceneNodeProxy> getBoundNodes(component_id_type comp) const;

        private:
            void init();

            void removeNodeComponents(SceneNode::id_type id);
            void removeHierarchy(node_id_type id);
    };
}

#include <FD3D/SceneGraph/SceneNodeProxy.h>

#endif // FD3D_SCENE_H
