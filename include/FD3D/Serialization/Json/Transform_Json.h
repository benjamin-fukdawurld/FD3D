#ifndef TRANSFORM_JSON_H
#define TRANSFORM_JSON_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/Utils/Transform.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::Transform &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::Transform &v, Serializer &serializer, std::string *err = nullptr);
}

#endif // TRANSFORM_JSON_H
