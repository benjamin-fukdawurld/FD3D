#ifndef LIGHT_JSON_H
#define LIGHT_JSON_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/Light/Light.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::LightType &type, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::LightType &type, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::LightCone &cone, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::LightCone &cone, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::LightAttenuation &attenuation, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::LightAttenuation &attenuation, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::LightColor &color, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::LightColor &color, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::Light &light, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::Light &light, Serializer &serializer, std::string *err = nullptr);
}

#endif // LIGHT_JSON_H
