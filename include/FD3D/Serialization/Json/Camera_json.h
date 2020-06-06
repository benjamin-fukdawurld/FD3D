#ifndef FD3D_CAMERA_JSON_H
#define FD3D_CAMERA_JSON_H

#include <FD3D/Serialization/Json/Camera_json_fwd.h>
#include <FD3D/Serialization/Json/Transform_json_fwd.h>
#include <FD3D/Serialization/Json/Projection_json_fwd.h>

#include <FDJson/JsonSerializer.h>

FD_INLINE rapidjson::Value FDJson::serialize(const FD3D::Camera &cam, FDJson::Serializer &serializer)
{
    rapidjson::Value result = serializer.serialize(static_cast<const FD3D::Transform&>(cam));

    result.AddMember(rapidjson::Value("projection", 10u, serializer.getAllocator()),
                     serializer.serialize(cam.projection), serializer.getAllocator());

    return result;
}

FD_INLINE bool FDJson::unserialize(const rapidjson::Value &val, FD3D::Camera &cam, FDJson::Serializer &serializer, std::string *err)
{
    if(!val.HasMember("projection"))
    {
        if(err)
            *err = "value has no member projection";

        return false;
    }

    return serializer.unserialize(val, static_cast<FD3D::Transform&>(cam), err)
            && serializer.unserialize(val["projection"], cam.projection, err);
}

#endif // FD3D_CAMERA_JSON_H
