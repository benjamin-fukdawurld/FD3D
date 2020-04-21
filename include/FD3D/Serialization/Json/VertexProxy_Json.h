#ifndef VERTEXPROXY_JSON_H
#define VERTEXPROXY_JSON_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/Utils/VertexProxy.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::VertexComponentType &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::VertexComponentType &v, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::VertexComponentFlag &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::VertexComponentFlag &v, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::ConstVertexProxy &v, Serializer &serializer);

    rapidjson::Value serialize(const FD3D::VertexProxy &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::VertexProxy &v, Serializer &serializer, std::string *err = nullptr);
}

#endif // VERTEXPROXY_JSON_H
