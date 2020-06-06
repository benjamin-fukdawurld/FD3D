#ifndef FD3D_PROJECTION_JSON_FWD_H
#define FD3D_PROJECTION_JSON_FWD_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/Camera/Projection.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::ProjectionType &type, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::ProjectionType &type, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::Projection &proj, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::Projection &proj, Serializer &serializer, std::string *err = nullptr);
}

#endif // FD3D_PROJECTION_JSON_FWD_H
