#ifndef FD3D_TRANSFORM_JSON_H
#define FD3D_TRANSFORM_JSON_H

#include <rapidjson/document.h>

#include <FDJson/Json_fwd.h>
#include <FD3D/Serialization/Json/Glm_json_fwd.h>
#include <FDJson/JsonSerializer.h>

#include <FD3D/Utils/Transform.h>

namespace FDJson
{
    FD_INLINE bool unserialize(const rapidjson::Value &val, FD3D::Transform &v, FDJson::Serializer &serializer, std::string *err)
    {
        if(!serializer.unserialize(val, static_cast<FD3D::Component&>(v), err))
            return false;

        if(!val.HasMember("position"))
        {
            if(err)
                *err = "vertex has no attribute 'position'";

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
                *err = "vertex has no attribute 'scale'";

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
                *err = "vertex has no attribute 'rotation'";

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

    FD_INLINE rapidjson::Value serialize(const FD3D::Transform &t, FDJson::Serializer &serializer)
    {
        rapidjson::Value result = serializer.serialize(static_cast<const FD3D::Component &>(t));
        result.AddMember(rapidjson::Value("position", 8u, serializer.getAllocator()), serializer.serialize(t.getPosition()),
                         serializer.getAllocator());
        result.AddMember(rapidjson::Value("scale", 5u, serializer.getAllocator()), serializer.serialize(t.getScale()),
                         serializer.getAllocator());
        result.AddMember(rapidjson::Value("rotation", 8u, serializer.getAllocator()), serializer.serialize(t.getRotation()),
                         serializer.getAllocator());

        return result;
    }

}

#endif // FD3D_TRANSFORM_JSON_H
