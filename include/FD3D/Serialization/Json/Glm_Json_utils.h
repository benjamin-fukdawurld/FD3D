#ifndef GLM_JSON_UTILS_H
#define GLM_JSON_UTILS_H

#include <FD3D/Serialization/Json/Glm_Json_fwd.h>

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
                *err += "value is not an object";

            return false;
        }

        if(val.HasMember("x"))
        {
            if(err)
                *err += "value has no member 'x'";

            return false;
        }

        if(val.HasMember("y"))
        {
            if(err)
                *err += "value has no member 'y'";

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
                *err += "value is not an object";

            return false;
        }

        if(val.HasMember("x"))
        {
            if(err)
                *err += "value has no member 'x'";

            return false;
        }

        if(val.HasMember("y"))
        {
            if(err)
                *err += "value has no member 'y'";

            return false;
        }

        if(val.HasMember("z"))
        {
            if(err)
                *err += "value has no member 'z'";

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
                *err += "value is not an object";

            return false;
        }

        if(val.HasMember("w"))
        {
            if(err)
                *err += "value has no member 'w'";

            return false;
        }

        if(val.HasMember("x"))
        {
            if(err)
                *err += "value has no member 'x'";

            return false;
        }

        if(val.HasMember("y"))
        {
            if(err)
                *err += "value has no member 'y'";

            return false;
        }

        if(val.HasMember("z"))
        {
            if(err)
                *err += "value has no member 'z'";

            return false;
        }

        return serializer.unserialize(val["w"], v.w, err)
                && serializer.unserialize(val["x"], v.x, err)
                && serializer.unserialize(val["y"], v.y, err)
                && serializer.unserialize(val["z"], v.z, err);
    }
}

#endif // GLM_JSON_UTILS_H
