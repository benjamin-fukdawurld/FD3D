#ifndef FD3D_VERTEXPROXY_JSON_FWD_H
#define FD3D_VERTEXPROXY_JSON_FWD_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/Utils/VertexProxy.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::VertexComponentType &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::VertexComponentType &v, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::VertexComponentFlag &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::VertexComponentFlag &v, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::ConstVertexProxy2 &v, Serializer &serializer);

    rapidjson::Value serialize(const FD3D::VertexProxy2 &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::VertexProxy2 &v, Serializer &serializer, std::string *err = nullptr);
}

#endif // FD3D_VERTEXPROXY_JSON_FWD_H
