#ifndef FD3D_MATERIAL_JSON_FWD_H
#define FD3D_MATERIAL_JSON_FWD_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/Material/MaterialComponent.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::Material &material, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::Material &material, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::MaterialComponent &material, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::MaterialComponent &material, Serializer &serializer, std::string *err = nullptr);
}

#endif // FD3D_MATERIAL_JSON_FWD_H
