#include <FD3D/Serialization/Json/Glm_Json_fwd.h>

#include <FDJson/Json_primitive_fwd.h>
#include <FDJson/JsonSerializer.h>

using namespace FDJson;

rapidjson::Value FDJson::serialize(const FD3D::color_helper<const glm::vec3> &c, Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("r", 1u, serializer.getAllocator()), rapidjson::Value(c.v.r), serializer.getAllocator());
    result.AddMember(rapidjson::Value("g", 1u, serializer.getAllocator()), rapidjson::Value(c.v.g), serializer.getAllocator());
    result.AddMember(rapidjson::Value("b", 1u, serializer.getAllocator()), rapidjson::Value(c.v.b), serializer.getAllocator());
    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::color_helper<glm::vec3> &c, Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    if(val.HasMember("r"))
    {
        if(err)
            *err += "value has no member 'r'";

        return false;
    }

    if(val.HasMember("g"))
    {
        if(err)
            *err += "value has no member 'g'";

        return false;
    }

    if(val.HasMember("b"))
    {
        if(err)
            *err += "value has no member 'b'";

        return false;
    }

    return serializer.unserialize(val["r"], c.v.r, err)
            && serializer.unserialize(val["g"], c.v.g, err)
            && serializer.unserialize(val["b"], c.v.b, err);
}

rapidjson::Value FDJson::serialize(const FD3D::color_helper<const glm::vec4> &c, Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("r", 1u, serializer.getAllocator()), rapidjson::Value(c.v.r), serializer.getAllocator());
    result.AddMember(rapidjson::Value("g", 1u, serializer.getAllocator()), rapidjson::Value(c.v.g), serializer.getAllocator());
    result.AddMember(rapidjson::Value("b", 1u, serializer.getAllocator()), rapidjson::Value(c.v.b), serializer.getAllocator());
    result.AddMember(rapidjson::Value("a", 1u, serializer.getAllocator()), rapidjson::Value(c.v.a), serializer.getAllocator());
    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::color_helper<glm::vec4> &c, Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    if(val.HasMember("r"))
    {
        if(err)
            *err += "value has no member 'r'";

        return false;
    }

    if(val.HasMember("g"))
    {
        if(err)
            *err += "value has no member 'g'";

        return false;
    }

    if(val.HasMember("b"))
    {
        if(err)
            *err += "value has no member 'b'";

        return false;
    }

    if(val.HasMember("a"))
    {
        if(err)
            *err += "value has no member 'a'";

        return false;
    }

    return serializer.unserialize(val["r"], c.v.r, err)
            && serializer.unserialize(val["g"], c.v.g, err)
            && serializer.unserialize(val["b"], c.v.b, err)
            && serializer.unserialize(val["a"], c.v.a, err);
}

rapidjson::Value FDJson::serialize(const FD3D::texture_helper<const glm::vec2> &c, Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("s", 1u, serializer.getAllocator()), rapidjson::Value(c.v.s), serializer.getAllocator());
    result.AddMember(rapidjson::Value("t", 1u, serializer.getAllocator()), rapidjson::Value(c.v.t), serializer.getAllocator());
    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::texture_helper<glm::vec2> &c, Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    if(val.HasMember("s"))
    {
        if(err)
            *err += "value has no member 's'";

        return false;
    }

    if(val.HasMember("t"))
    {
        if(err)
            *err += "value has no member 't'";

        return false;
    }

    return serializer.unserialize(val["s"], c.v.s, err)
            && serializer.unserialize(val["t"], c.v.t, err);
}

rapidjson::Value FDJson::serialize(const FD3D::texture_helper<const glm::vec3> &c, Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("s", 1u, serializer.getAllocator()), rapidjson::Value(c.v.s), serializer.getAllocator());
    result.AddMember(rapidjson::Value("t", 1u, serializer.getAllocator()), rapidjson::Value(c.v.t), serializer.getAllocator());
    result.AddMember(rapidjson::Value("p", 1u, serializer.getAllocator()), rapidjson::Value(c.v.p), serializer.getAllocator());
    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::texture_helper<glm::vec3> &c, Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    if(val.HasMember("s"))
    {
        if(err)
            *err += "value has no member 's'";

        return false;
    }

    if(val.HasMember("t"))
    {
        if(err)
            *err += "value has no member 't'";

        return false;
    }

    if(val.HasMember("p"))
    {
        if(err)
            *err += "value has no member 'p'";

        return false;
    }

    return serializer.unserialize(val["s"], c.v.s, err)
            && serializer.unserialize(val["t"], c.v.t, err)
            && serializer.unserialize(val["p"], c.v.p, err);
}

rapidjson::Value FDJson::serialize(const FD3D::texture_helper<const glm::vec4> &c, Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("s", 1u, serializer.getAllocator()), rapidjson::Value(c.v.s), serializer.getAllocator());
    result.AddMember(rapidjson::Value("t", 1u, serializer.getAllocator()), rapidjson::Value(c.v.t), serializer.getAllocator());
    result.AddMember(rapidjson::Value("p", 1u, serializer.getAllocator()), rapidjson::Value(c.v.p), serializer.getAllocator());
    result.AddMember(rapidjson::Value("q", 1u, serializer.getAllocator()), rapidjson::Value(c.v.q), serializer.getAllocator());
    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::texture_helper<glm::vec4> &c, Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err += "value is not an object";

        return false;
    }

    if(val.HasMember("s"))
    {
        if(err)
            *err += "value has no member 's'";

        return false;
    }

    if(val.HasMember("t"))
    {
        if(err)
            *err += "value has no member 't'";

        return false;
    }

    if(val.HasMember("p"))
    {
        if(err)
            *err += "value has no member 'p'";

        return false;
    }

    if(val.HasMember("q"))
    {
        if(err)
            *err += "value has no member 'q'";

        return false;
    }

    return serializer.unserialize(val["s"], c.v.s, err)
            && serializer.unserialize(val["t"], c.v.t, err)
            && serializer.unserialize(val["p"], c.v.p, err)
            && serializer.unserialize(val["q"], c.v.q, err);
}
