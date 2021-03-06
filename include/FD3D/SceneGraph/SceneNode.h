#ifndef FD3D_SCENENODE_H
#define FD3D_SCENENODE_H

#include <cstdint>
#include <string>
#include <vector>

#include <FD3D/SceneGraph/Element.h>
#include <FDCore/TypeInformation.h>

namespace FD3D
{
    class FD_EXPORT SceneNode : public FD3D::Element
    {
        public:
            typedef typename FDCore::Identifiable<uintptr_t>::id_type id_type;
            typedef typename std::vector<id_type>::iterator child_iterator;
            typedef typename std::vector<id_type>::const_iterator const_child_iterator;
            typedef typename std::vector<id_type>::reverse_iterator reverse_child_iterator;
            typedef typename std::vector<id_type>::const_reverse_iterator const_reverse_child_iterator;

        protected:
            std::string m_name;
            std::vector<id_type> m_children;
            id_type m_parent;
            bool m_isEnabled;

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

                return static_cast<const T*>(this);
            }

            const std::string &getName() const;
            void setName(const std::string &name);

            const std::vector<id_type> &getChildIds() const;
            void setChildIds(std::vector<id_type> &&children);
            void setChildIds(const std::vector<id_type> &children);

            id_type getChildId(size_t index) const;

            void addChildId(id_type id);
            void removeChildId(id_type id);
            void removeChildIdAt(size_t pos);

            bool hasChildren() const;
            size_t getChildIdCount() const;
            void reserveChildIds(size_t size);

            bool isEnabled() const;
            void enable();
            void disable();

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
            virtual bool matchTypeCodeHash(size_t hash) const;
    };

    class FD_EXPORT RootNode : public SceneNode
    {
        friend class Scene;

        private:
            using SceneNode::SceneNode;
            using SceneNode::setParentId;

            RootNode() = default;

            RootNode(const RootNode &node) = delete;

            RootNode &operator=(const RootNode &node) = delete;

        public:
            const char *getTypeCode() const override;
            size_t getTypeCodeHash() const override;
            bool matchTypeCodeHash(size_t hash) const override;
    };

    template<typename T>
    class EntityNode: public SceneNode
    {
        public:
            typedef T EntityType;

        protected:
            EntityType *m_entity;

        public:
            EntityNode(id_type parent) :
                EntityNode(nullptr, parent)
            {}

            EntityNode(EntityType *entity = nullptr, id_type parent = 0) :
                SceneNode(parent),
                m_entity(entity)
            {}


            EntityNode(EntityNode &&node)
            {
                m_entity = node.m_entity;
                SceneNode::operator=(std::move(node));
            }

            EntityNode(const EntityNode &node) = delete;

            EntityNode &operator=(EntityNode &&node)
            {
                if(&node == this)
                    return *this;

                m_entity = std::move(node.m_entity);
                SceneNode::operator=(std::move(node));
                return *this;
            }

            EntityNode &operator=(const EntityNode &node) = delete;

            bool hasEntity() { return m_entity != nullptr; }
            EntityType *getEntity() { return m_entity; }
            const EntityType *getEntity() const { return m_entity; }

            void setEntity(EntityType *entity) { m_entity = entity; }

            const char *getTypeCode() const override;
            size_t getTypeCodeHash() const override;
            bool matchTypeCodeHash(size_t hash) const override
            {
                return hash == EntityNode<T>::getTypeCodeHash() || SceneNode::matchTypeCodeHash(hash);
            }
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

generateTypeCode(FD3D::SceneNode);
generateTypeCode(FD3D::RootNode);


#endif // FD3D_SCENENODE_H
