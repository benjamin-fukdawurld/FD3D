#ifndef COMPONENT_JSON_H
#define COMPONENT_JSON_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/SceneGraph/Component.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::Component &comp, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::Component &comp, Serializer &serializer, std::string *err = nullptr);
}

#endif // COMPONENT_JSON_H
