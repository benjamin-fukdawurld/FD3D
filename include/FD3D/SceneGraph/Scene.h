#ifndef SCENE_H
#define SCENE_H

#include <FD3D/SceneNode.h>

namespace FD3D
{
    class SceneNodeProxy;
    class ConstSceneNodeProxy;

    class Scene
    {
        public:
            typedef SceneNode::id_type id_type;

        protected:
            std::vector<SceneNode> m_nodes;
            id_type m_rootId;

        public:
            Scene();

            id_type getRootId() const;

            SceneNodeProxy getNode(id_type id);
            ConstSceneNodeProxy getNode(id_type id) const;

            void addNode(SceneNode &&node);
            void addNode(const SceneNode &node);
            void removeNode(id_type id);
            void removeNodeAt(size_t pos);

            bool hasNodes() const;
            void clearNodes();
            size_t getNodeCount() const;

            template<typename T, typename ...Args>
            void emplaceNode(Args... args)
            {
                addNode(std::move(T{args...}));
            }

            std::vector<SceneNodeProxy> findByName(const std::string &name,
                                                   id_type from = 0);
            std::vector<ConstSceneNodeProxy> findByName(const std::string &name,
                                                        id_type from = 0) const;

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
