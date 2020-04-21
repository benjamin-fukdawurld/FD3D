#include <FD3D/Serialization/Json/Light_Json.h>

#include <FD3D/Serialization/Json/Glm_Json_utils.h>
#include <FDJson/Json_primitive.h>
#include <FDJson/JsonSerializer.h>


rapidjson::Value FDJson::serialize(const FD3D::LightType &type, FDJson::Serializer &serializer)
{
    return serializer.serialize(FD3D::lightTypeToString(type).data());
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::LightType &type, FDJson::Serializer &, std::string *err)
{
    if(!val.IsString())
    {
        if(err)
            *err += "value is not a string";

        return false;
    }

    type = FD3D::lightTypeFromString(val.GetString());
    if(type == FD3D::LightType::Invalid)
    {
        if(err)
            *err += "value is not a valid type";

        return false;
    }

    return true;
}

rapidjson::Value FDJson::serialize(const FD3D::LightCone &cone, FDJson::Serializer &serializer)
{
    rapidjson::Value result;
    result.AddMember(rapidjson::Value("innerAngle", 10u, serializer.getAllocator()),
                     serializer.serialize(cone.getInnerAngle()), serializer.getAllocator());
    result.AddMember(rapidjson::Value("outerAngle", 10u, serializer.getAllocator()),
                     serializer.serialize(cone.getOuterAngle()), serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::LightCone &cone, FDJson::Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    if(!val.HasMember("innerAngle"))
    {
        if(err)
            *err += "value has no inner angle";

        return false;
    }

    const rapidjson::Value &inner = val["innerAngle"];
    if(!inner.IsFloat())
    {
        if(err)
            *err += "inner angle is not a float";

        return false;
    }

    float f;
    if(!serializer.unserialize(inner, f, err))
    {
        if(err)
            *err += "Error parsing innerAngle: " + *err;

        return false;
    }
    cone.setInnerAngle(f);

    if(!val.HasMember("outerAngle"))
    {
        if(err)
            *err += "value has no outer angle";

        return false;
    }

    const rapidjson::Value &outer = val["outerAngle"];
    if(!outer.IsFloat())
    {
        if(err)
            *err += "outer angle is not a float";

        return false;
    }

    if(!serializer.unserialize(outer, f, err))
    {
        if(err)
            *err += "Error parsing outerAngle: " + *err;

        return false;
    }
    cone.setOuterAngle(f);

    return true;
}

rapidjson::Value FDJson::serialize(const FD3D::LightAttenuation &attenuation, FDJson::Serializer &serializer)
{
    rapidjson::Value result;
    result.AddMember(rapidjson::Value("constant", 8u, serializer.getAllocator()),
                     serializer.serialize(attenuation.getConstantAttenuation()),
                     serializer.getAllocator());

    result.AddMember(rapidjson::Value("linear", 6u, serializer.getAllocator()),
                     serializer.serialize(attenuation.getLinearAttenuation()),
                     serializer.getAllocator());

    result.AddMember(rapidjson::Value("quadratic", 9u, serializer.getAllocator()),
                     serializer.serialize(attenuation.getQuadraticAttenuation()),
                     serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::LightAttenuation &attenuation, FDJson::Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    float f;
    if(!val.HasMember("constant"))
    {
        if(err)
            *err += "value has no constant attenuation";

        return false;
    }

    const rapidjson::Value &constant = val["constant"];
    if(!constant.IsFloat())
    {
        if(err)
            *err += "constant attenuation is not a float";

        return false;
    }

    if(!serializer.unserialize(constant, f, err))
    {
        if(err)
            *err += "Error parsing constant attenuation: " + *err;

        return false;
    }
    attenuation.setConstantAttenuation(f);

    if(!val.HasMember("linear"))
    {
        if(err)
            *err += "value has no linear attenuation";

        return false;
    }

    const rapidjson::Value &linear = val["linear"];
    if(!linear.IsFloat())
    {
        if(err)
            *err += "linear attenuation is not a float";

        return false;
    }

    if(!serializer.unserialize(linear, f, err))
    {
        if(err)
            *err += "Error parsing linear attenuation: " + *err;

        return false;
    }
    attenuation.setLinearAttenuation(f);

    if(!val.HasMember("linear"))
    {
        if(err)
            *err += "value has no linear attenuation";

        return false;
    }

    const rapidjson::Value &quadratic = val["quadratic"];
    if(!quadratic.IsFloat())
    {
        if(err)
            *err += "quadratic attenuation is not a float";

        return false;
    }

    if(!serializer.unserialize(quadratic, f, err))
    {
        if(err)
            *err += "Error parsing quadratic attenuation: " + *err;

        return false;
    }
    attenuation.setQuadraticAttenuation(f);

    return true;
}

rapidjson::Value FDJson::serialize(const FD3D::LightColor &color, FDJson::Serializer &serializer)
{
    rapidjson::Value result;
    result.AddMember(serializer.serialize("ambient"),
                     serializer.serialize(FD3D::color_helper<const glm::vec4>(color.ambient)),
                     serializer.getAllocator());

    result.AddMember(serializer.serialize("diffuse"),
                     serializer.serialize(FD3D::color_helper<const glm::vec4>(color.diffuse)),
                     serializer.getAllocator());

    result.AddMember(serializer.serialize("specular"),
                     serializer.serialize(FD3D::color_helper<const glm::vec4>(color.specular)),
                     serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::LightColor &color, FDJson::Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }


    {
        if(!val.HasMember("ambient"))
        {
            if(err)
                *err += "value has no ambient color";

            return false;
        }

        FD3D::color_helper<glm::vec4> col(color.ambient);
        const rapidjson::Value &ambient = val["ambient"];
        if(!serializer.unserialize(ambient, col, err))
        {
            if(err)
                *err += "Error parsing ambient color: " + *err;

            return false;
        }
    }

    {
        if(!val.HasMember("diffuse"))
        {
            if(err)
                *err += "value has no diffuse color";

            return false;
        }

        FD3D::color_helper<glm::vec4> col(color.diffuse);
        const rapidjson::Value &diffuse = val["diffuse"];
        if(!serializer.unserialize(diffuse, col, err))
        {
            if(err)
                *err += "Error parsing diffuse color: " + *err;

            return false;
        }
    }

    {
        if(!val.HasMember("specular"))
        {
            if(err)
                *err += "value has no specular color";

            return false;
        }

        FD3D::color_helper<glm::vec4> col(color.specular);
        const rapidjson::Value &specular = val["specular"];
        if(!serializer.unserialize(specular, col, err))
        {
            if(err)
                *err += "Error parsing specular color: " + *err;

            return false;
        }
    }

    return true;
}

rapidjson::Value FDJson::serialize(const FD3D::Light &light, FDJson::Serializer &serializer)
{
    rapidjson::Value result;
    result.AddMember(serializer.serialize("color"),
                     serializer.serialize(light.color),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("cone"),
                     serializer.serialize(light.cone),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("attenuation"),
                     serializer.serialize(light.attenuation),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("type"),
                     serializer.serialize(light.getType()),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("position"),
                     serializer.serialize(light.getPosition()),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("direction"),
                     serializer.serialize(light.getDirection()),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("up"),
                     serializer.serialize(light.getDirection()),
                     serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::Light &light, FDJson::Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    {
        if(!val.HasMember("color"))
        {
            if(err)
                *err += "value has no color";

            return false;
        }

        const rapidjson::Value &color = val["color"];
        if(!serializer.unserialize(color, light.color, err))
        {
            if(err)
                *err += "Error parsing color: " + *err;

            return false;
        }
    }

    {
        if(!val.HasMember("cone"))
        {
            if(err)
                *err += "value has no cone";

            return false;
        }

        const rapidjson::Value &cone = val["cone"];
        if(!serializer.unserialize(cone, light.cone, err))
        {
            if(err)
                *err += "Error parsing cone: " + *err;

            return false;
        }
    }

    {
        if(!val.HasMember("attenuation"))
        {
            if(err)
                *err += "value has no attenuation";

            return false;
        }

        const rapidjson::Value &cone = val["attenuation"];
        if(!serializer.unserialize(cone, light.attenuation, err))
        {
            if(err)
                *err += "Error parsing attenuation: " + *err;

            return false;
        }
    }

    {
        if(!val.HasMember("type"))
        {
            if(err)
                *err += "value has no type";

            return false;
        }

        FD3D::LightType t;
        const rapidjson::Value &type = val["type"];
        if(!serializer.unserialize(type, t, err))
        {
            if(err)
                *err += "Error parsing type: " + *err;

            return false;
        }
    }

    {
        if(!val.HasMember("position"))
        {
            if(err)
                *err += "value has no position";

            return false;
        }

        glm::vec3 pos;
        const rapidjson::Value &position = val["position"];
        if(!serializer.unserialize(position, pos, err))
        {
            if(err)
                *err += "Error parsing position: " + *err;

            return false;
        }
        light.setPosition(pos);
    }

    {
        if(!val.HasMember("direction"))
        {
            if(err)
                *err += "value has no direction";

            return false;
        }

        glm::vec3 dir;
        const rapidjson::Value &direction = val["direction"];
        if(!serializer.unserialize(direction, dir, err))
        {
            if(err)
                *err += "Error parsing direction: " + *err;

            return false;
        }
        light.setDirection(dir);
    }

    {
        if(!val.HasMember("up"))
        {
            if(err)
                *err += "value has no up";

            return false;
        }

        glm::vec3 up;
        const rapidjson::Value &v = val["up"];
        if(!serializer.unserialize(v, up, err))
        {
            if(err)
                *err += "Error parsing up: " + *err;

            return false;
        }
        light.setUp(up);
    }

    return true;
}
