#include <FD3D/Serialization/Json/Transform_Json.h>

#include <rapidjson/document.h>

#include <FD3D/Serialization/Json/Glm_Json_fwd.h>
#include <FD3D/Serialization/Json/Glm_Json_utils.h>
#include <FD3D/Mesh/AbstractMesh.h>

#include <FDJson/JsonSerializer.h>

rapidjson::Value FDJson::serialize(const FD3D::Transform &t, FDJson::Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("position", 8u, serializer.getAllocator()), serializer.serialize(t.getPosition()),
                     serializer.getAllocator());
    result.AddMember(rapidjson::Value("scale", 5u, serializer.getAllocator()), serializer.serialize(t.getScale()),
                     serializer.getAllocator());
    result.AddMember(rapidjson::Value("rotation", 8u, serializer.getAllocator()), serializer.serialize(t.getRotation()),
                     serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::Transform &v, FDJson::Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    if(!val.HasMember("position"))
    {
        if(err)
            *err += "vertex has no attribute 'position'";

        return false;
    }

    glm::vec3 &pos = v.getPosition();
    if(!serializer.unserialize(val["position"], pos, err))
    {
        if(err)
            *err = std::string("Error parsing position: ") + *err;

        return false;
    }

    if(!val.HasMember("scale"))
    {
        if(err)
            *err += "vertex has no attribute 'scale'";

        return false;
    }

    glm::vec3 &scale = v.getScale();
    if(!serializer.unserialize(val["scale"], scale, err))
    {
        if(err)
            *err = std::string("Error parsing scale: ") + *err;

        return false;
    }

    if(!val.HasMember("rotation"))
    {
        if(err)
            *err += "vertex has no attribute 'rotation'";

        return false;
    }

    glm::quat &rotation = v.getRotation();
    if(!serializer.unserialize(val["rotation"], rotation, err))
    {
        if(err)
            *err = std::string("Error parsing rotation: ") + *err;

        return false;
    }

    return true;
}
