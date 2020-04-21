#ifndef GLM_JSON_FWD_H
#define GLM_JSON_FWD_H


#include <type_traits>
#include <rapidjson/fwd.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

#include <FD3D/Serialization/Glm_Serialize_utils.h>

#include <FDJson/FDJson.h>

namespace FDJson
{
    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec2> || std::is_same_v<T, glm::ivec2>,
    rapidjson::Value> serialize(const T &v, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec2> || std::is_same_v<T, glm::ivec2>,
    bool> unserialize(const rapidjson::Value &val, T &v, Serializer &serializer, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec3> || std::is_same_v<T, glm::ivec3>,
    rapidjson::Value> serialize(const T &v, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec3> || std::is_same_v<T, glm::ivec3>,
    bool> unserialize(const rapidjson::Value &val, T &v, Serializer &serializer, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec4> || std::is_same_v<T, glm::quat> || std::is_same_v<T, glm::quat>,
    rapidjson::Value> serialize(const T &v, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same_v<T, glm::vec4> || std::is_same_v<T, glm::ivec4> || std::is_same_v<T, glm::quat>,
    bool> unserialize(const rapidjson::Value &val, T &v, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::color_helper<const glm::vec3> &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::color_helper<glm::vec3> &v, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::color_helper<const glm::vec4> &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::color_helper<glm::vec4> &v, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::texture_helper<const glm::vec2> &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::texture_helper<glm::vec2> &v, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::texture_helper<const glm::vec3> &v, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::texture_helper<glm::vec3> &v, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const FD3D::texture_helper<const glm::vec4> &c, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::texture_helper<glm::vec4> &c, Serializer &serializer, std::string *err = nullptr);
}

#endif // GLM_JSON_FWD_H
