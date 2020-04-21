#include <FD3D/Serialization/Json/VertexProxy_Json.h>

#include <rapidjson/document.h>

#include <FD3D/Serialization/Json/Glm_Json_fwd.h>
#include <FD3D/Serialization/Json/Glm_Json_utils.h>
#include <FD3D/Mesh/AbstractMesh.h>

#include <FDJson/JsonSerializer.h>

rapidjson::Value FDJson::serialize(const FD3D::VertexProxy &v, FDJson::Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("position", 8u, serializer.getAllocator()), serializer.serialize(v.getPosition()),
                     serializer.getAllocator());

    const glm::vec3 *ptr = v.getNormal();
    if(ptr)
    {
        result.AddMember(rapidjson::Value("normal", 6u, serializer.getAllocator()), serializer.serialize(*ptr),
                         serializer.getAllocator());
    }

    ptr = v.getTangent();
    if(ptr)
    {
        result.AddMember(rapidjson::Value("tangent", 7u, serializer.getAllocator()), serializer.serialize(*ptr),
                         serializer.getAllocator());
        result.AddMember(rapidjson::Value("bitangent", 9u, serializer.getAllocator()), serializer.serialize(*v.getBitangent()),
                         serializer.getAllocator());
    }

    if(v.getMesh()->hasVertexComponent(FD3D::VertexComponentType::Texture))
    {
        rapidjson::Value texVal(rapidjson::kArrayType);
        for(size_t i = 0, imax = v.getMesh()->getNumberOfUvChannel(); i <imax; ++i)
        {
            const glm::vec2 *tex = v.getUv(i);
            if(tex)
                result.PushBack(serializer.serialize(FD3D::texture_helper<const glm::vec2>{*tex}), serializer.getAllocator());
        }
        result.AddMember(rapidjson::Value("texture", 7u, serializer.getAllocator()), texVal, serializer.getAllocator());
    }

    if(v.getMesh()->hasVertexComponent(FD3D::VertexComponentType::Color))
    {
        rapidjson::Value colVal(rapidjson::kArrayType);
        for(size_t i = 0, imax = v.getMesh()->getNumberOfColorChannel(); i <imax; ++i)
        {
            const glm::vec4 *col = v.getColor(i);
            if(ptr)
                result.PushBack(serializer.serialize(FD3D::color_helper<const glm::vec4>{*col}), serializer.getAllocator());
        }
        result.AddMember(rapidjson::Value("color", 5u, serializer.getAllocator()), colVal, serializer.getAllocator());
    }

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::VertexProxy &v, FDJson::Serializer &serializer, std::string *err)
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

    glm::vec3 *ptr = v.getPosition();
    if(!serializer.unserialize(val["position"], *ptr, err))
    {
        if(err)
            *err = std::string("Error parsing position: ") + *err;

        return false;
    }

    if(v.getMesh()->hasVertexComponent(FD3D::VertexComponentType::Normal))
    {
        ptr = v.getNormal();
        if(!val.HasMember("normal"))
        {
            if(err)
                *err += "vertex has no attribute 'normal'";

            return false;
        }

        if(!serializer.unserialize(val["normal"], *ptr, err))
        {
            if(err)
                *err = std::string("Error parsing normal: ") + *err;

            return false;
        }
    }

    if(v.getMesh()->hasVertexComponent(FD3D::VertexComponentType::Tangent))
    {
        ptr = v.getTangent();
        if(!val.HasMember("tangent"))
        {
            if(err)
                *err += "vertex has no attribute 'tangent'";

            return false;
        }

        if(!serializer.unserialize(val["tangent"], *ptr, err))
        {
            if(err)
                *err = std::string("Error parsing normal: ") + *err;

            return false;
        }

        ptr = v.getTangent();
        if(!val.HasMember("bitangent"))
        {
            if(err)
                *err += "vertex has no attribute 'bitangent'";

            return false;
        }

        if(!serializer.unserialize(val["bitangent"], *ptr, err))
        {
            if(err)
                *err = std::string("Error parsing normal: ") + *err;

            return false;
        }
    }

    if(v.getMesh()->hasVertexComponent(FD3D::VertexComponentType::Texture))
    {
        if(!val.HasMember("texture"))
        {
            if(err)
                *err += "vertex has no attribute 'texture'";

            return false;
        }

        const rapidjson::Value &tex = val["texture"];
        rapidjson::SizeType nbUvs = static_cast<rapidjson::SizeType>(v.getMesh()->getNumberOfUvChannel());
        if(tex.Size() != nbUvs)
        {
            if(err)
            {
                *err += "vertex texture count does not match expected value (expected ";
                *err += std::to_string(nbUvs) + ", received " + std::to_string(val.Size()) + ")";
            }

            return false;
        }

        for(rapidjson::SizeType i = 0; i < nbUvs; ++i)
        {
            FD3D::texture_helper<glm::vec2> t(*v.getUv(i));

            if(!serializer.unserialize(tex[i], t, err))
            {
                if(err)
                    *err = std::string("Error parsing texture: ") + *err;

                return false;
            }
        }
    }

    if(v.getMesh()->hasVertexComponent(FD3D::VertexComponentType::Color))
    {
        if(!val.HasMember("color"))
        {
            if(err)
                *err += "vertex has no attribute 'color'";

            return false;
        }

        const rapidjson::Value &color = val["color"];
        rapidjson::SizeType nbColors = static_cast<rapidjson::SizeType>(v.getMesh()->getNumberOfColorChannel());
        if(color.Size() != nbColors)
        {
            if(err)
            {
                *err += "vertex color count does not match expected value (expected ";
                *err += std::to_string(nbColors) + ", received " + std::to_string(val.Size()) + ")";
            }

            return false;
        }

        for(rapidjson::SizeType i = 0; i < nbColors; ++i)
        {
            FD3D::color_helper<glm::vec4> t(*v.getColor(i));

            if(!serializer.unserialize(color[i], t, err))
            {
                if(err)
                    *err = std::string("Error parsing color: ") + *err;

                return false;
            }
        }
    }

    return true;
}

rapidjson::Value FDJson::serialize(const FD3D::VertexComponentType &v, FDJson::Serializer &serializer)
{
    return serializer.serialize(FD3D::vertexComponentTypeToString(v).data());
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::VertexComponentType &v, FDJson::Serializer &serializer, std::string *err)
{
    std::string str;
    if(!serializer.unserialize(val, str, err))
    {
        if(!err)
            *err += "Error parsing vertex component type: " + *err;

        return false;
    }

    v = FD3D::vertexComponentTypeFromString(str);
    if(!serializer.unserialize(val, str, err))
    {
        if(!err)
            *err += "Error parsing vertex component type: " + *err;

        return false;
    }

    return true;
}

rapidjson::Value FDJson::serialize(const FD3D::VertexComponentFlag &v, FDJson::Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kArrayType);
    if(v[FD3D::VertexComponentType::Position])
        result.PushBack(serializer.serialize(FD3D::VertexComponentType::Position), serializer.getAllocator());
    if(v[FD3D::VertexComponentType::Normal])
        result.PushBack(serializer.serialize(FD3D::VertexComponentType::Position), serializer.getAllocator());
    if(v[FD3D::VertexComponentType::Tangent])
        result.PushBack(serializer.serialize(FD3D::VertexComponentType::Position), serializer.getAllocator());
    if(v[FD3D::VertexComponentType::Texture])
        result.PushBack(serializer.serialize(FD3D::VertexComponentType::Position), serializer.getAllocator());
    if(v[FD3D::VertexComponentType::Color])
        result.PushBack(serializer.serialize(FD3D::VertexComponentType::Position), serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::VertexComponentFlag &v, FDJson::Serializer &serializer, std::string *err)
{
    if(!val.IsArray())
    {
        if(!err)
            *err += "value is not an arry";

        return false;
    }

    for(auto it = val.Begin(), end = val.End(); it != end; ++it)
    {
        FD3D::VertexComponentType t;
        if(!serializer.unserialize(val, t, err))
        {
            if(err)
                *err += "Error parsing component: " + *err;

            return false;
        }

        v |= t;
    }

    return true;
}

rapidjson::Value FDJson::serialize(const FD3D::ConstVertexProxy &v, FDJson::Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("position", 8u, serializer.getAllocator()), serializer.serialize(v.getPosition()),
                     serializer.getAllocator());

    const glm::vec3 *ptr = v.getNormal();
    if(ptr)
    {
        result.AddMember(rapidjson::Value("normal", 6u, serializer.getAllocator()), serializer.serialize(*ptr),
                         serializer.getAllocator());
    }

    ptr = v.getTangent();
    if(ptr)
    {
        result.AddMember(rapidjson::Value("tangent", 7u, serializer.getAllocator()), serializer.serialize(*ptr),
                         serializer.getAllocator());
        result.AddMember(rapidjson::Value("bitangent", 9u, serializer.getAllocator()), serializer.serialize(*v.getBitangent()),
                         serializer.getAllocator());
    }

    if(v.getMesh()->hasVertexComponent(FD3D::VertexComponentType::Texture))
    {
        rapidjson::Value texVal(rapidjson::kArrayType);
        for(size_t i = 0, imax = v.getMesh()->getNumberOfUvChannel(); i <imax; ++i)
        {
            const glm::vec2 *tex = v.getUv(i);
            if(tex)
                result.PushBack(serializer.serialize(FD3D::texture_helper<const glm::vec2>{*tex}), serializer.getAllocator());
        }
        result.AddMember(rapidjson::Value("texture", 7u, serializer.getAllocator()), texVal, serializer.getAllocator());
    }

    if(v.getMesh()->hasVertexComponent(FD3D::VertexComponentType::Color))
    {
        rapidjson::Value colVal(rapidjson::kArrayType);
        for(size_t i = 0, imax = v.getMesh()->getNumberOfColorChannel(); i <imax; ++i)
        {
            const glm::vec4 *col = v.getColor(i);
            if(ptr)
                result.PushBack(serializer.serialize(FD3D::color_helper<const glm::vec4>{*col}), serializer.getAllocator());
        }
        result.AddMember(rapidjson::Value("color", 5u, serializer.getAllocator()), colVal, serializer.getAllocator());
    }

    return result;
}
