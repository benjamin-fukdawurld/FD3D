#ifndef MATERIAL_JSON_H
#define MATERIAL_JSON_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/Material/Material.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::Material &material, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::Material &material, Serializer &serializer, std::string *err = nullptr);
}

#endif // MATERIAL_JSON_H
