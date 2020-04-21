#include <FD3D/Serialization/Json/Material_Json.h>

#include <FD3D/Serialization/Json/Glm_Json_utils.h>
#include <FDJson/Json_primitive.h>
#include <FDJson/JsonSerializer.h>

rapidjson::Value FDJson::serialize(const FD3D::Material &material, FDJson::Serializer &serializer)
{
    rapidjson::Value result;
    result.AddMember(serializer.serialize("ambient"),
                     serializer.serialize(FD3D::color_helper<const glm::vec3>(material.getAmbientColor())),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("diffuse"),
                     serializer.serialize(FD3D::color_helper<const glm::vec3>(material.getDiffuseColor())),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("specular"),
                     serializer.serialize(FD3D::color_helper<const glm::vec3>(material.getSpecularColor())),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("shininess"),
                     serializer.serialize(material.getShininess()),
                     serializer.getAllocator());
    result.AddMember(serializer.serialize("opacity"),
                     serializer.serialize(material.getOpacity()),
                     serializer.getAllocator());


    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::Material &material, FDJson::Serializer &serializer, std::string *err)
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

        FD3D::color_helper<glm::vec3> col(material.getAmbientColor());
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

        FD3D::color_helper<glm::vec3> col(material.getDiffuseColor());
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

        FD3D::color_helper<glm::vec3> col(material.getSpecularColor());
        const rapidjson::Value &specular = val["specular"];
        if(!serializer.unserialize(specular, col, err))
        {
            if(err)
                *err += "Error parsing specular color: " + *err;

            return false;
        }
    }

    float f;
    {
        if(!val.HasMember("shininess"))
        {
            if(err)
                *err += "value has no shininess";

            return false;
        }

        const rapidjson::Value &shininess = val["shininess"];
        if(!serializer.unserialize(shininess, f, err))
        {
            if(err)
                *err += "Error parsing shininess: " + *err;

            return false;
        }
        material.setShininess(f);
    }

    {
        if(!val.HasMember("opacity"))
        {
            if(err)
                *err += "value has no opacity";

            return false;
        }

        const rapidjson::Value &opacity = val["opacity"];
        if(!serializer.unserialize(opacity, f, err))
        {
            if(err)
                *err += "Error parsing opacity: " + *err;

            return false;
        }
        material.setOpacity(f);
    }

    return true;
}
