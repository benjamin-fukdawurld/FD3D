#ifndef FD3D_MODEL_H
#define FD3D_MODEL_H

#include <vector>
#include <string>

#include <glm/mat4x4.hpp>

#include <FD3D/Mesh/Mesh.h>
#include <FD3D/Mesh/Transform.h>
#include <FD3D/SceneGraph/SceneNode.h>

namespace FD3D
{
    template<typename T = Mesh<Vertex>>
    class Model
    {
        public:
            typedef T MeshType;
            typedef typename T::VertexType VertexType;
            typedef Model<MeshType> ModelType;

            typedef typename std::vector<T>::iterator child_iterator;
            typedef typename std::vector<T>::const_iterator const_child_iterator;
            typedef typename std::vector<T>::reverse_iterator reverse_child_iterator;
            typedef typename std::vector<T>::const_reverse_iterator const_reverse_child_iterator;

            typedef typename std::vector<T>::iterator mesh_iterator;
            typedef typename std::vector<T>::const_iterator const_mesh_iterator;
            typedef typename std::vector<T>::reverse_iterator reverse_mesh_iterator;
            typedef typename std::vector<T>::const_reverse_iterator const_reverse_mesh_iterator;

        protected:
            std::string m_name;
            std::string m_directory;
            ModelType *m_parent;
            std::vector<ModelType> m_children;
            std::vector<T> m_meshes;
            Transform m_transform;

        public:
            Model(const std::string &name = "") :
                m_name(name),
                m_parent(nullptr)
            {}

            Model(const std::string &name,
                  const std::vector<T> &meshes,
                  const std::string &directory,
                  ModelType *parent = nullptr) :
                m_name(name),
                m_meshes(meshes),
                m_directory(directory),
                m_parent(parent)
            {}

            const std::string &getName() const;
            void setName(const std::string &name);

            Transform &getTransform();
            const Transform &getTransform() const;
            void setTransform(Transform &&transform);
            void setTransform(const Transform &transform);

            ModelType *getParent();
            const ModelType *getParent() const;
            void setParent(ModelType *parent);

            const std::vector<ModelType> &getChildren() const;
            void setChildren(std::vector<ModelType> &&children);
            void setChildren(const std::vector<ModelType> &children);

            ModelType &getChild(size_t index);
            const ModelType &getChild(size_t index) const;

            template<typename ...Args>
            void emplaceChild(Args ...args);

            void addChild(ModelType &&model);
            void addChild(const ModelType &model);
            void removeChild(const size_t pos);

            bool hasChildren() const;
            size_t getChildCount() const;
            void reserveChildren(size_t size);

            void clearChildren();

            child_iterator childrenBegin();
            const_child_iterator childrenBegin() const;
            const_child_iterator childrenConstBegin() const;

            child_iterator childrenEnd();
            const_child_iterator childrenEnd() const;
            const_child_iterator childrenConstEnd() const;

            child_iterator childrenReverseBegin();
            const_child_iterator childrenReverseBegin() const;
            const_child_iterator childrenConstReverseBegin() const;

            child_iterator childrenReverseEnd();
            const_child_iterator childrenReverseEnd() const;
            const_child_iterator childrenConstReverseEnd() const;

            template<typename ...Args>
            void emplaceMesh(Args ...args);

            void addMesh(T &&mesh);
            void addMesh(const T &mesh);
            void removeMesh(const size_t pos);

            bool hasMesh() const;
            size_t getMeshCount() const;
            void reserveMeshes(size_t size);

            void clearMeshes();

            const T &getMesh(size_t pos) const;
            T &getMesh(size_t pos);

            const T &operator[](size_t pos) const;
            T &operator[](size_t pos);

            mesh_iterator meshesBegin();
            const_mesh_iterator meshesBegin() const;
            const_mesh_iterator meshesConstBegin() const;

            mesh_iterator meshesEnd();
            const_mesh_iterator meshesEnd() const;
            const_mesh_iterator meshesConstEnd() const;

            mesh_iterator meshesReverseBegin();
            const_mesh_iterator meshesReverseBegin() const;
            const_mesh_iterator meshesConstReverseBegin() const;

            mesh_iterator meshesReverseEnd();
            const_mesh_iterator meshesReverseEnd() const;
            const_mesh_iterator meshesConstReverseEnd() const;

            const std::vector<T> &getMeshes() const;
            void setMeshes(const std::vector<T> &meshes);
            std::string getDirectory() const;
            void setDirectory(const std::string &directory);
    };

    template<typename MeshType>
    using ModelNode = EntityNode<Model<MeshType>>;


    template<typename T>
    template<typename ...Args>
    void Model<T>::emplaceChild(Args ...args)
    {
        m_children.emplace_back(args...);
    }

    template<typename T>
    const std::string &Model<T>::getName() const
    {
        return m_name;
    }

    template<typename T>
    void Model<T>::setName(const std::string &name)
    {
        m_name = name;
    }

    template<typename T>
    Transform &Model<T>::getTransform()
    {
        return m_transform;
    }

    template<typename T>
    const Transform &Model<T>::getTransform() const
    {
        return m_transform;
    }

    template<typename T>
    void Model<T>::setTransform(Transform &&transform)
    {
        m_transform = std::move(transform);
    }

    template<typename T>
    void Model<T>::setTransform(const Transform &transform)
    {
        m_transform = transform;
    }

    template<typename T>
    Model<T> *Model<T>::getParent()
    {
        return m_parent;
    }

    template<typename T>
    const Model<T> *Model<T>::getParent() const
    {
        return m_parent;
    }

    template<typename T>
    const std::vector<Model<T>> &Model<T>::getChildren() const
    {
        return m_children;
    }

    template<typename T>
    void Model<T>::setChildren(std::vector<Model<T>> &&children)
    {
        m_children = std::move(children);
    }

    template<typename T>
    void Model<T>::setChildren(const std::vector<Model<T>> &children)
    {
        m_children = children;
    }

    template<typename T>
    Model<T> &Model<T>::getChild(size_t index)
    {
        return m_children[index];
    }

    template<typename T>
    const Model<T> &Model<T>::getChild(size_t index) const
    {
        return m_children[index];
    }

    template<typename T>
    void Model<T>::addChild(Model<T> &&model)
    {
        m_children.push_back(std::move(model));
    }

    template<typename T>
    void Model<T>::addChild(const Model<T> &model)
    {
        m_children.push_back(model);
    }

    template<typename T>
    void Model<T>::setParent(Model<T> *parent)
    {
        m_parent = parent;
    }

    template<typename T>
    void Model<T>::removeChild(const size_t pos)
    {
        auto it = m_children.begin();
        std::advance(it, pos);
        m_children.erase(it);
    }

    template<typename T>
    bool Model<T>::hasChildren() const
    {
        return !m_children.empty();
    }

    template<typename T>
    size_t Model<T>::getChildCount() const
    {
        return m_children.size();
    }

    template<typename T>
    void Model<T>::reserveChildren(size_t size)
    {
        m_children.reserve(size);
    }

    template<typename T>
    void Model<T>::clearChildren()
    {
        m_children.clear();
    }

    template<typename T>
    typename Model<T>::child_iterator Model<T>::childrenBegin()
    {
        return m_children.begin();
    }

    template<typename T>
    typename Model<T>::const_child_iterator Model<T>::childrenBegin() const
    {
        return m_children.begin();
    }

    template<typename T>
    typename Model<T>::const_child_iterator Model<T>::childrenConstBegin() const
    {
        return m_children.cbegin();
    }

    template<typename T>
    typename Model<T>::child_iterator Model<T>::childrenEnd()
    {
        return m_children.end();
    }

    template<typename T>
    typename Model<T>::const_child_iterator Model<T>::childrenEnd() const
    {
        return m_children.end();
    }

    template<typename T>
    typename Model<T>::const_child_iterator Model<T>::childrenConstEnd() const
    {
        return m_children.cend();
    }

    template<typename T>
    typename Model<T>::child_iterator Model<T>::childrenReverseBegin()
    {
        return m_children.rbegin();
    }

    template<typename T>
    typename Model<T>::const_child_iterator Model<T>::childrenReverseBegin() const
    {
        return m_children.begin();
    }

    template<typename T>
    typename Model<T>::const_child_iterator Model<T>::childrenConstReverseBegin() const
    {
        return m_children.crbegin();
    }

    template<typename T>
    typename Model<T>::child_iterator Model<T>::childrenReverseEnd()
    {
        return m_children.rend();
    }

    template<typename T>
    typename Model<T>::const_child_iterator Model<T>::childrenReverseEnd() const
    {
        return m_children.rend();
    }

    template<typename T>
    typename Model<T>::const_child_iterator Model<T>::childrenConstReverseEnd() const
    {
        return m_children.crend();
    }

    template<typename T>
    template<typename ...Args>
    void Model<T>::emplaceMesh(Args ...args)
    {
        m_meshes.emplace_back(args...);
    }

    template<typename T>
    void Model<T>::addMesh(T &&mesh)
    {
        m_meshes.push_back(std::move(mesh));
    }

    template<typename T>
    void Model<T>::addMesh(const T &mesh)
    {
        m_meshes.push_back(mesh);
    }

    template<typename T>
    void Model<T>::removeMesh(const size_t pos)
    {
        auto it = m_meshes.begin();
        std::advance(it, pos);
        m_meshes.erase(it);
    }

    template<typename T>
    typename Model<T>::mesh_iterator Model<T>::meshesBegin()
    {
        return m_meshes.begin();
    }

    template<typename T>
    typename Model<T>::const_mesh_iterator Model<T>::meshesBegin() const
    {
        return m_meshes.begin();
    }

    template<typename T>
    typename Model<T>::const_mesh_iterator Model<T>::meshesConstBegin() const
    {
        return m_meshes.cbegin();
    }

    template<typename T>
    typename Model<T>::mesh_iterator Model<T>::meshesEnd()
    {
        return m_meshes.end();
    }

    template<typename T>
    typename Model<T>::const_mesh_iterator Model<T>::meshesEnd() const
    {
        return m_meshes.end();
    }

    template<typename T>
    typename Model<T>::const_mesh_iterator Model<T>::meshesConstEnd() const
    {
        return m_meshes.cend();
    }

    template<typename T>
    typename Model<T>::mesh_iterator Model<T>::meshesReverseBegin()
    {
        return m_meshes.rbegin();
    }

    template<typename T>
    typename Model<T>::const_mesh_iterator Model<T>::meshesReverseBegin() const
    {
        return m_meshes.begin();
    }

    template<typename T>
    typename Model<T>::const_mesh_iterator Model<T>::meshesConstReverseBegin() const
    {
        return m_meshes.crbegin();
    }

    template<typename T>
    typename Model<T>::mesh_iterator Model<T>::meshesReverseEnd()
    {
        return m_meshes.rend();
    }

    template<typename T>
    typename Model<T>::const_mesh_iterator Model<T>::meshesReverseEnd() const
    {
        return m_meshes.rend();
    }

    template<typename T>
    typename Model<T>::const_mesh_iterator Model<T>::meshesConstReverseEnd() const
    {
        return m_meshes.crend();
    }

    template<typename T>
    bool Model<T>::hasMesh() const
    {
        return !m_meshes.empty();
    }

    template<typename T>
    size_t Model<T>::getMeshCount() const
    {
        return m_meshes.size();
    }

    template<typename T>
    void Model<T>::reserveMeshes(size_t size)
    {
        m_meshes.reserve(size);
    }

    template<typename T>
    void Model<T>::clearMeshes()
    {
        m_meshes.clear();
        m_directory.clear();
    }

    template<typename T>
    const T &Model<T>::getMesh(size_t pos) const
    {
        return m_meshes.at(pos);
    }

    template<typename T>
    T &Model<T>::getMesh(size_t pos)
    {
        return m_meshes.at(pos);
    }

    template<typename T>
    const T &Model<T>::operator[](size_t pos) const
    {
        return m_meshes.at(pos);
    }

    template<typename T>
    T &Model<T>::operator[](size_t pos)
    {
        return m_meshes.at(pos);
    }

    template<typename  T>
    std::string Model<T>::getDirectory() const
    {
        return m_directory;
    }

    template<typename  T>
    void Model<T>::setDirectory(const std::string &directory)
    {
        m_directory = directory;
    }

    template<typename  T>
    const std::vector<T> &Model<T>::getMeshes() const
    {
        return m_meshes;
    }

    template<typename  T>
    void Model<T>::setMeshes(const std::vector<T> &meshes)
    {
        m_meshes = meshes;
    }

}

generateTemplateTypeCode(FD3D::Model, MeshType);
generateTemplateTypeCode(FD3D::ModelNode, MeshType);

#endif // FD3D_MODEL_H
