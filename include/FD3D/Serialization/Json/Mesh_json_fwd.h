#ifndef FD3D_MESH_JSON_FWD_H
#define FD3D_MESH_JSON_FWD_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/Mesh/MeshComponent.h>
#include <FD3D/Mesh/Mesh.h>

namespace FDJson
{
    template<typename T>
    std::enable_if_t<std::is_same_v<T, FD3D::AbstractMesh> || std::is_same_v<T, FD3D::Mesh>,
    rapidjson::Value> serialize(const T &mesh, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same_v<T, FD3D::AbstractMesh> || std::is_same_v<T, FD3D::Mesh>,
    bool> unserialize(const rapidjson::Value &val, T &mesh, Serializer &serializer, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same_v<T, FD3D::AbstractMeshComponent> || std::is_same_v<T, FD3D::MeshComponent>,
    rapidjson::Value> serialize(const T &mesh, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same_v<T, FD3D::AbstractMeshComponent> || std::is_same_v<T, FD3D::MeshComponent>,
    bool> unserialize(const rapidjson::Value &val, T &mesh, Serializer &serializer, std::string *err = nullptr);
}

#endif // FD3D_MESH_JSON_FWD_H
