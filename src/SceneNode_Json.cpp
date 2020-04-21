#include <FD3D/Serialization/Json/SceneNode_Json.h>

#include <FD3D/Serialization/Json/Glm_Json_utils.h>
#include <FDJson/Json_primitive.h>
#include <FDJson/JsonSerializer.h>

rapidjson::Value FDJson::serialize(const FD3D::SceneNode &node, FDJson::Serializer &serializer)
{
    rapidjson::Value result;
    result.AddMember(serializer.serialize("name"), serializer.serialize(node.getName()), serializer.getAllocator());
    result.AddMember(serializer.serialize("type"), serializer.serialize(node.getTypeCode()), serializer.getAllocator());
    result.AddMember(serializer.serialize("isEnabled"), serializer.serialize(node.isEnabled()), serializer.getAllocator());
    result.AddMember(serializer.serialize("parent"), serializer.serialize((node.getParentId())),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("children"), serializer.serialize(node.getChildIds()), serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::SceneNode &node, Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    {
        if(!val.HasMember("type"))
        {
            if(err)
                *err += "value has no attribute 'type'";

            return false;
        }

        const rapidjson::Value &type = val["type"];
        if(!type.IsString())
        {
            if(err)
                *err += "value has no attribute 'type'";

            return false;
        }

        std::string str(val["type"].GetString());

    }

    {
        if(!val.HasMember("name"))
        {
            if(err)
                *err += "value has no attribute 'name'";

            return false;
        }

        std::string str;
        if(!serializer.unserialize(val, str, err))
        {
            if(err)
                *err += "Error parsing attribute name: " + *err;

            return false;
        }

        node.setName(str);
    }

    {
        if(!val.HasMember("isEnabled"))
        {
            if(err)
                *err += "value has no attribute 'isEnabled'";

            return false;
        }

        bool b;
        if(!serializer.unserialize(val, b, err))
        {
            if(err)
                *err += "Error parsing attribute isEnabled: " + *err;

            return false;
        }

        if(b)
            node.enable();
        else
            node.disable();
    }

    return true;
}
