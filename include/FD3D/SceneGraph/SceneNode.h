#ifndef SCENENODE_H
#define SCENENODE_H

#include <cstdint>
#include <string>
#include <vector>

#include <FDCore/Identifiable.h>
#include <FDCore/TypeInformation.h>

namespace FD3D
{
    class SceneNode : public FDCore::Identifiable<>
    {
        public:
            typedef typename FDCore::Identifiable<>::id_type id_type;
            typedef typename std::vector<id_type>::iterator child_iterator;
            typedef typename std::vector<id_type>::const_iterator const_child_iterator;
            typedef typename std::vector<id_type>::reverse_iterator reverse_child_iterator;
            typedef typename std::vector<id_type>::const_reverse_iterator const_reverse_child_iterator;

        protected:
            std::string m_name;
            std::vector<id_type> m_children;
            id_type m_parent;

        public:
            SceneNode(id_type parent = 0);

            SceneNode(SceneNode &&node);
            SceneNode(const SceneNode &node);

            SceneNode &operator=(SceneNode &&node);
            SceneNode &operator=(const SceneNode &node);

            virtual ~SceneNode();

            template<typename T>
            bool is() const
            {
                return FDCore::TypeCodeHelper<T>::hash == getTypeCodeHash();
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

            const std::string &getName() const;
            void setName(const std::string &name);

            const std::vector<id_type> &getChildIds() const;
            void setChildIds(std::vector<id_type> &&children);
            void setChildIds(const std::vector<id_type> &children);

            id_type &getChildId(size_t index);
            const id_type &getChildId(size_t index) const;

            void addChildId(id_type id);
            void removeChildId(id_type id);
            void removeChildIdAt(size_t pos);

            bool hasChildren() const;
            size_t getChildIdCount() const;
            void reserveChildIds(size_t size);

            void clearChildIds();

            child_iterator childIdsBegin();
            const_child_iterator childIdsBegin() const;
            const_child_iterator childIdsConstBegin() const;

            child_iterator childIdsEnd();
            const_child_iterator childIdsEnd() const;
            const_child_iterator childIdsConstEnd() const;

            reverse_child_iterator childIdsReverseBegin();
            const_reverse_child_iterator childIdsReverseBegin() const;
            const_reverse_child_iterator childIdsConstReverseBegin() const;

            reverse_child_iterator childIdsReverseEnd();
            const_reverse_child_iterator childIdsReverseEnd() const;
            const_reverse_child_iterator childIdsConstReverseEnd() const;

            bool hasParent() const;
            id_type getParentId() const;
            void setParentId(id_type parent);

            virtual const char *getTypeCode() const;
            virtual size_t getTypeCodeHash() const;
    };

    class RootNode : public SceneNode
    {
        friend class Scene;

        private:
            using SceneNode::SceneNode;
            using SceneNode::setParentId;

            RootNode(const RootNode &node) = delete;

            RootNode &operator=(const RootNode &node) = delete;

    };

    template<typename T>
    class EntityNode: public SceneNode
    {
        public:
            typedef T EntityType;

        protected:
            EntityType m_entity;

        public:
            EntityNode(id_type parent = 0) :
                SceneNode(parent)
            {}

            EntityNode(EntityNode &&node) :
                SceneNode(std::move(node)),
                m_entity(std::move(node.m_entity))
            {
            }

            EntityNode(const EntityNode &node) :
                SceneNode(node),
                m_entity(node.m_entity)
            {}

            EntityNode &operator=(EntityNode &&node)
            {
                m_entity = std::move(node.m_entity);
                SceneNode::operator=(std::move(node));
                return *this;
            }

            EntityNode &operator=(const EntityNode &node)
            {
                m_entity = node.m_entity;
                SceneNode::operator=(node);
                return *this;
            }

            EntityType &getEntity() { return m_entity; }
            const EntityType &getEntity() const { return m_entity; }

            void setEntity(EntityType &&entity) { m_entity = std::move(entity); }
            void setEntity(const EntityType &entity) { m_entity = entity; }

            const char *getTypeCode() const override;
            size_t getTypeCodeHash() const override;
    };

    template<typename T>
    const char *EntityNode<T>::getTypeCode() const
    {
        return FDCore::TypeCodeHelper<EntityNode<T>>::code;
    }


    template<typename T>
    size_t FD3D::EntityNode<T>::getTypeCodeHash() const
    {
        return FDCore::TypeCodeHelper<EntityNode<T>>::hash();
    }
}


#endif // SCENENODE_H
