#ifndef MESH_JSON_H
#define MESH_JSON_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/Mesh/AbstractMesh.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::AbstractMesh &mesh, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::AbstractMesh &mesh, Serializer &serializer, std::string *err = nullptr);
}

#endif // MESH_JSON_H
