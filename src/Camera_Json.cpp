#include <FD3D/Serialization/Json/Camera_Json.h>

#include <FD3D/Serialization/Json/Transform_Json.h>
#include <FD3D/Serialization/Json/Projection_Json.h>
#include <FDJson/Json_primitive.h>
#include <FDJson/JsonSerializer.h>

rapidjson::Value FDJson::serialize(const FD3D::Camera &cam, FDJson::Serializer &serializer)
{
    rapidjson::Value result = serializer.serialize(static_cast<const FD3D::Transform&>(cam));

    result.AddMember(rapidjson::Value("projection", 10u, serializer.getAllocator()),
                     serializer.serialize(cam.projection), serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::Camera &cam, FDJson::Serializer &serializer, std::string *err)
{
    return serializer.unserialize(val, static_cast<FD3D::Transform&>(cam), err)
            && serializer.unserialize(val, cam.projection, err);
}
