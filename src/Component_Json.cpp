#include <FD3D/Serialization/Json/Component_Json.h>

#include <FD3D/Serialization/Json/Glm_Json_utils.h>
#include <FDJson/Json_primitive.h>
#include <FDJson/JsonSerializer.h>

rapidjson::Value FDJson::serialize(const FD3D::Component &comp, FDJson::Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kObjectType);

    result.AddMember(serializer.serialize("id"), serializer.serialize(comp.getId()), serializer.getAllocator());
    result.AddMember(serializer.serialize("name"), serializer.serialize(comp.getName()), serializer.getAllocator());
    result.AddMember(serializer.serialize("type"), serializer.serialize(comp.getTypeCode()), serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::Component &comp, FDJson::Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    if(!val.HasMember("name"))
    {
        if(err)
            *err += "value has no member 'name'";

        return false;
    }

    std::string str;
    if(!serializer.unserialize(val["name"], str, err))
    {
        if(err)
            *err += "Error parsing name: " + *err;

        return false;
    }

    comp.setName(str);

    return true;
}
