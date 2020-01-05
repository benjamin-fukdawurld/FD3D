#ifndef FD3D_MODEL_H
#define FD3D_MODEL_H

#include <vector>
#include <string>

#include <glm/mat4x4.hpp>

#include <FD3D/Mesh/Mesh.h>
#include <FD3D/Utils/Transform.h>
#include <FD3D/SceneGraph/SceneNode.h>

namespace FD3D
{
    class Model
    {
        protected:
            std::vector<Component::id_type> m_meshIds;

        public:
            Transform transform;

        public:
            Model() {}

            Model(std::vector<Component::id_type> &&meshIds) : m_meshIds(std::move(meshIds)) {}

            Model(const std::vector<Component::id_type> &meshIds) : m_meshIds(meshIds) {}

            Component::id_type &getMesh(size_t pos) { return m_meshIds.at(pos); }
            Component::id_type getMesh(size_t pos) const { return m_meshIds.at(pos); }

            Component::id_type &operator[](size_t pos) { return m_meshIds[pos]; }
            Component::id_type operator[](size_t pos) const { return m_meshIds[pos]; }

            bool hasMesh() const { return !m_meshIds.empty(); }

            size_t getNumberOfMesh() const { return m_meshIds.size(); }

            void addMeshId(Component::id_type id)
            {
                assert(id != 0);
                m_meshIds.push_back(id);
            }

            void removeMeshId(Component::id_type id)
            {
                auto it = std::find(m_meshIds.begin(), m_meshIds.end(), id);
                if(it != m_meshIds.end())
                    m_meshIds.erase(it);
            }
    };

}

generateTypeCode(FD3D::Model);

#endif // FD3D_MODEL_H
