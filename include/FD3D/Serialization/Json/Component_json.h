#ifndef FD3D_COMPONENT_JSON_H
#define FD3D_COMPONENT_JSON_H

#include <FD3D/Serialization/Json/Component_json_fwd.h>
#include <FD3D/Serialization/Json/Element_json.h>

#include <FD3D/SceneGraph/SceneManager.h>

#include <rapidjson/document.h>

#include <FDJson/JsonSerializer.h>

namespace FDJson
{
    FD_INLINE rapidjson::Value serialize(const FD3D::Component &comp, FDJson::Serializer &serializer)
    {
        rapidjson::Value result(serializer.serialize(static_cast<const FD3D::Element&>(comp)));
        result.AddMember(serializer.serialize("name"), serializer.serialize(comp.getName()), serializer.getAllocator());

        return result;
    }

    FD_INLINE bool unserialize(const rapidjson::Value &val, FD3D::Component &comp, FDJson::Serializer &serializer, std::string *err)
    {
        if(!serializer.unserialize(val, static_cast<FD3D::Element&>(comp), err))
            return false;

        if(!val.HasMember("name"))
        {
            if(err)
                *err = "value has no member 'name'";

            return false;
        }

        std::string str;
        if(!serializer.unserialize(val["name"], str, err))
        {
            if(err)
                *err = "Error parsing name: " + *err;

            return false;
        }

        comp.setName(str);

        return true;
    }
}

#endif // COMPONENT_JSON_H
