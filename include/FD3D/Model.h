#ifndef FD3D_MODEL_H
#define FD3D_MODEL_H

#include <vector>
#include <string>

#include <FD3D/Mesh.h>

namespace FD3D
{
    template<typename T = Mesh<Vertex>>
    class Model
    {
        public:
            typedef T MeshType;
            typedef typename std::vector<T>::iterrator iterrator;
            typedef typename std::vector<T>::const_iterrator const_iterrator;
            typedef typename std::vector<T>::reverse_iterrator reverse_iterrator;
            typedef typename std::vector<T>::const_reverse_iterrator const_reverse_iterrator;

        protected:
            std::vector<T> m_meshes;
            std::string m_directory;

        public:
            Model() {}

            Model(const std::vector<T> &meshes, const std::string &directory) :
                m_meshes(meshes),
                m_directory(directory)
            {}

            template<typename ...Args>
            void emplaceMesh(Args ...args);

            void addMesh(const T &mesh);
            void removeMesh(const size_t pos);

            bool empty() const;
            size_t size() const;
            void reserve(size_t s);

            void clear();

            const T &getMesh(size_t pos) const;
            T &getMesh(size_t pos);

            const T &operator[](size_t pos) const;
            T &operator[](size_t pos);

            iterrator begin();
            const_iterrator begin() const;
            const_iterrator cbegin() const;

            iterrator end();
            const_iterrator end() const;
            const_iterrator cend() const;

            iterrator rbegin();
            const_iterrator rbegin() const;
            const_iterrator crbegin() const;

            iterrator rend();
            const_iterrator rend() const;
            const_iterrator crend() const;

            const std::vector<T> &getMeshes() const;
            void setMeshes(const std::vector<T> &meshes);
            std::string getDirectory() const;
            void setDirectory(const std::string &directory);
    };

    template<typename T>
    template<typename ...Args>
    void Model<T>::emplaceMesh(Args ...args)
    {
        m_meshes.emplace_back(args...);
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
    typename Model<T>::iterrator Model<T>::begin()
    {
        return m_meshes.begin();
    }

    template<typename T>
    typename Model<T>::const_iterrator Model<T>::begin() const
    {
        return m_meshes.begin();
    }

    template<typename T>
    typename Model<T>::const_iterrator Model<T>::cbegin() const
    {
        return m_meshes.cbegin();
    }

    template<typename T>
    typename Model<T>::iterrator Model<T>::end()
    {
        return m_meshes.end();
    }

    template<typename T>
    typename Model<T>::const_iterrator Model<T>::end() const
    {
        return m_meshes.end();
    }

    template<typename T>
    typename Model<T>::const_iterrator Model<T>::cend() const
    {
        return m_meshes.cend();
    }

    template<typename T>
    typename Model<T>::iterrator Model<T>::rbegin()
    {
        return m_meshes.rbegin();
    }

    template<typename T>
    typename Model<T>::const_iterrator Model<T>::rbegin() const
    {
        return m_meshes.begin();
    }

    template<typename T>
    typename Model<T>::const_iterrator Model<T>::crbegin() const
    {
        return m_meshes.crbegin();
    }

    template<typename T>
    typename Model<T>::iterrator Model<T>::rend()
    {
        return m_meshes.rend();
    }

    template<typename T>
    typename Model<T>::const_iterrator Model<T>::rend() const
    {
        return m_meshes.rend();
    }

    template<typename T>
    typename Model<T>::const_iterrator Model<T>::crend() const
    {
        return m_meshes.crend();
    }

    template<typename T>
    bool Model<T>::empty() const
    {
        return m_meshes.empty();
    }

    template<typename T>
    size_t Model<T>::size() const
    {
        return m_meshes.size();
    }

    template<typename T>
    void Model<T>::reserve(size_t s)
    {
        m_meshes.reserve(s);
    }

    template<typename T>
    void Model<T>::clear()
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

#endif // FD3D_MODEL_H
