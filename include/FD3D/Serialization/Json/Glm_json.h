#ifndef FD3D_GLM_JSON_H
#define FD3D_GLM_JSON_H

#include <FD3D/Serialization/Json/Glm_json_fwd.h>

#include <FDJson/Json_fwd.h>
#include <FDJson/JsonSerializer.h>

namespace FDJson
{
    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec2> || std::is_same_v<T, glm::ivec2>,
    rapidjson::Value> serialize(const T &v, Serializer &serializer)
    {
        rapidjson::Value result(rapidjson::kObjectType);
        result.AddMember(rapidjson::Value("x", 1u, serializer.getAllocator()), rapidjson::Value(v.x), serializer.getAllocator());
        result.AddMember(rapidjson::Value("y", 1u, serializer.getAllocator()), rapidjson::Value(v.y), serializer.getAllocator());
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec2> || std::is_same_v<T, glm::ivec2>,
    bool> unserialize(const rapidjson::Value &val, T &v, Serializer &serializer, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "value is not an object";

            return false;
        }

        if(val.HasMember("x"))
        {
            if(err)
                *err = "value has no member 'x'";

            return false;
        }

        if(val.HasMember("y"))
        {
            if(err)
                *err = "value has no member 'y'";

            return false;
        }

        return serializer.unserialize(val["x"], v.x, err) && serializer.unserialize(val["y"], v.y, err);
    }


    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec3> || std::is_same_v<T, glm::ivec3>,
    rapidjson::Value> serialize(const T &v, Serializer &serializer)
    {
        rapidjson::Value result(rapidjson::kObjectType);
        result.AddMember(rapidjson::Value("x", 1u, serializer.getAllocator()), rapidjson::Value(v.x), serializer.getAllocator());
        result.AddMember(rapidjson::Value("y", 1u, serializer.getAllocator()), rapidjson::Value(v.y), serializer.getAllocator());
        result.AddMember(rapidjson::Value("z", 1u, serializer.getAllocator()), rapidjson::Value(v.z), serializer.getAllocator());
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec3> || std::is_same_v<T, glm::ivec3>,
    bool> unserialize(const rapidjson::Value &val, T &v, Serializer &serializer, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "value is not an object";

            return false;
        }

        if(!val.HasMember("x"))
        {
            if(err)
                *err = "value has no member 'x'";

            return false;
        }

        if(!val.HasMember("y"))
        {
            if(err)
                *err = "value has no member 'y'";

            return false;
        }

        if(!val.HasMember("z"))
        {
            if(err)
                *err = "value has no member 'z'";

            return false;
        }

        return serializer.unserialize(val["x"], v.x, err)
                && serializer.unserialize(val["y"], v.y, err)
                && serializer.unserialize(val["z"], v.z, err);
    }


    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec4> || std::is_same_v<T, glm::ivec4> || std::is_same_v<T, glm::quat>,
    rapidjson::Value> serialize(const T &v, Serializer &serializer)
    {
        rapidjson::Value result(rapidjson::kObjectType);
        result.AddMember(rapidjson::Value("w", 1u, serializer.getAllocator()), rapidjson::Value(v.w), serializer.getAllocator());
        result.AddMember(rapidjson::Value("x", 1u, serializer.getAllocator()), rapidjson::Value(v.x), serializer.getAllocator());
        result.AddMember(rapidjson::Value("y", 1u, serializer.getAllocator()), rapidjson::Value(v.y), serializer.getAllocator());
        result.AddMember(rapidjson::Value("z", 1u, serializer.getAllocator()), rapidjson::Value(v.z), serializer.getAllocator());
        return result;
    }

    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec4> || std::is_same_v<T, glm::ivec4> || std::is_same_v<T, glm::quat>,
    bool> unserialize(const rapidjson::Value &val, T &v, Serializer &serializer, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "value is not an object";

            return false;
        }

        if(!val.HasMember("w"))
        {
            if(err)
                *err = "value has no member 'w'";

            return false;
        }

        if(!val.HasMember("x"))
        {
            if(err)
                *err = "value has no member 'x'";

            return false;
        }

        if(!val.HasMember("y"))
        {
            if(err)
                *err = "value has no member 'y'";

            return false;
        }

        if(!val.HasMember("z"))
        {
            if(err)
                *err = "value has no member 'z'";

            return false;
        }

        return serializer.unserialize(val["w"], v.w, err)
                && serializer.unserialize(val["x"], v.x, err)
                && serializer.unserialize(val["y"], v.y, err)
                && serializer.unserialize(val["z"], v.z, err);
    }

    FD_INLINE rapidjson::Value serialize(const FD3D::color_helper<const glm::vec3> &c, Serializer &serializer)
    {
        rapidjson::Value result(rapidjson::kObjectType);
        result.AddMember(rapidjson::Value("r", 1u, serializer.getAllocator()), rapidjson::Value(c.v.r), serializer.getAllocator());
        result.AddMember(rapidjson::Value("g", 1u, serializer.getAllocator()), rapidjson::Value(c.v.g), serializer.getAllocator());
        result.AddMember(rapidjson::Value("b", 1u, serializer.getAllocator()), rapidjson::Value(c.v.b), serializer.getAllocator());
        return result;
    }

    FD_INLINE bool unserialize(const rapidjson::Value &val, FD3D::color_helper<glm::vec3> &c, Serializer &serializer, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "value is not an object";

            return false;
        }

        if(!val.HasMember("r"))
        {
            if(err)
                *err = "value has no member 'r'";

            return false;
        }

        if(!val.HasMember("g"))
        {
            if(err)
                *err = "value has no member 'g'";

            return false;
        }

        if(!val.HasMember("b"))
        {
            if(err)
                *err = "value has no member 'b'";

            return false;
        }

        return serializer.unserialize(val["r"], c.v.r, err)
                && serializer.unserialize(val["g"], c.v.g, err)
                && serializer.unserialize(val["b"], c.v.b, err);
    }

    FD_INLINE rapidjson::Value serialize(const FD3D::color_helper<const glm::vec4> &c, Serializer &serializer)
    {
        rapidjson::Value result(rapidjson::kObjectType);
        result.AddMember(rapidjson::Value("r", 1u, serializer.getAllocator()), rapidjson::Value(c.v.r), serializer.getAllocator());
        result.AddMember(rapidjson::Value("g", 1u, serializer.getAllocator()), rapidjson::Value(c.v.g), serializer.getAllocator());
        result.AddMember(rapidjson::Value("b", 1u, serializer.getAllocator()), rapidjson::Value(c.v.b), serializer.getAllocator());
        result.AddMember(rapidjson::Value("a", 1u, serializer.getAllocator()), rapidjson::Value(c.v.a), serializer.getAllocator());
        return result;
    }

    FD_INLINE bool unserialize(const rapidjson::Value &val, FD3D::color_helper<glm::vec4> &c, Serializer &serializer, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "value is not an object";

            return false;
        }

        if(!val.HasMember("r"))
        {
            if(err)
                *err = "value has no member 'r'";

            return false;
        }

        if(!val.HasMember("g"))
        {
            if(err)
                *err = "value has no member 'g'";

            return false;
        }

        if(!val.HasMember("b"))
        {
            if(err)
                *err = "value has no member 'b'";

            return false;
        }

        if(!val.HasMember("a"))
        {
            if(err)
                *err = "value has no member 'a'";

            return false;
        }

        return serializer.unserialize(val["r"], c.v.r, err)
                && serializer.unserialize(val["g"], c.v.g, err)
                && serializer.unserialize(val["b"], c.v.b, err)
                && serializer.unserialize(val["a"], c.v.a, err);
    }

    FD_INLINE rapidjson::Value serialize(const FD3D::texture_helper<const glm::vec2> &c, Serializer &serializer)
    {
        rapidjson::Value result(rapidjson::kObjectType);
        result.AddMember(rapidjson::Value("s", 1u, serializer.getAllocator()), rapidjson::Value(c.v.s), serializer.getAllocator());
        result.AddMember(rapidjson::Value("t", 1u, serializer.getAllocator()), rapidjson::Value(c.v.t), serializer.getAllocator());
        return result;
    }

    FD_INLINE bool unserialize(const rapidjson::Value &val, FD3D::texture_helper<glm::vec2> &c, Serializer &serializer, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "value is not an object";

            return false;
        }

        if(!val.HasMember("s"))
        {
            if(err)
                *err = "value has no member 's'";

            return false;
        }

        if(!val.HasMember("t"))
        {
            if(err)
                *err = "value has no member 't'";

            return false;
        }

        return serializer.unserialize(val["s"], c.v.s, err)
                && serializer.unserialize(val["t"], c.v.t, err);
    }

    FD_INLINE rapidjson::Value serialize(const FD3D::texture_helper<const glm::vec3> &c, Serializer &serializer)
    {
        rapidjson::Value result(rapidjson::kObjectType);
        result.AddMember(rapidjson::Value("s", 1u, serializer.getAllocator()), rapidjson::Value(c.v.s), serializer.getAllocator());
        result.AddMember(rapidjson::Value("t", 1u, serializer.getAllocator()), rapidjson::Value(c.v.t), serializer.getAllocator());
        result.AddMember(rapidjson::Value("p", 1u, serializer.getAllocator()), rapidjson::Value(c.v.p), serializer.getAllocator());
        return result;
    }

    FD_INLINE bool unserialize(const rapidjson::Value &val, FD3D::texture_helper<glm::vec3> &c, Serializer &serializer, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "value is not an object";

            return false;
        }

        if(!val.HasMember("s"))
        {
            if(err)
                *err = "value has no member 's'";

            return false;
        }

        if(!val.HasMember("t"))
        {
            if(err)
                *err = "value has no member 't'";

            return false;
        }

        if(!val.HasMember("p"))
        {
            if(err)
                *err = "value has no member 'p'";

            return false;
        }

        return serializer.unserialize(val["s"], c.v.s, err)
                && serializer.unserialize(val["t"], c.v.t, err)
                && serializer.unserialize(val["p"], c.v.p, err);
    }

    FD_INLINE rapidjson::Value serialize(const FD3D::texture_helper<const glm::vec4> &c, Serializer &serializer)
    {
        rapidjson::Value result(rapidjson::kObjectType);
        result.AddMember(rapidjson::Value("s", 1u, serializer.getAllocator()), rapidjson::Value(c.v.s), serializer.getAllocator());
        result.AddMember(rapidjson::Value("t", 1u, serializer.getAllocator()), rapidjson::Value(c.v.t), serializer.getAllocator());
        result.AddMember(rapidjson::Value("p", 1u, serializer.getAllocator()), rapidjson::Value(c.v.p), serializer.getAllocator());
        result.AddMember(rapidjson::Value("q", 1u, serializer.getAllocator()), rapidjson::Value(c.v.q), serializer.getAllocator());
        return result;
    }

    FD_INLINE bool unserialize(const rapidjson::Value &val, FD3D::texture_helper<glm::vec4> &c, Serializer &serializer, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "value is not an object";

            return false;
        }

        if(!val.HasMember("s"))
        {
            if(err)
                *err = "value has no member 's'";

            return false;
        }

        if(!val.HasMember("t"))
        {
            if(err)
                *err = "value has no member 't'";

            return false;
        }

        if(val.HasMember("p"))
        {
            if(err)
                *err = "value has no member 'p'";

            return false;
        }

        if(val.HasMember("q"))
        {
            if(err)
                *err = "value has no member 'q'";

            return false;
        }

        return serializer.unserialize(val["s"], c.v.s, err)
                && serializer.unserialize(val["t"], c.v.t, err)
                && serializer.unserialize(val["p"], c.v.p, err)
                && serializer.unserialize(val["q"], c.v.q, err);
    }
}

#endif // FD3D_GLM_JSON_H
