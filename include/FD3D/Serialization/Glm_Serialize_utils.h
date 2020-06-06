#ifndef FD3D_GLM_SERIALIZE_UTILS_H
#define FD3D_GLM_SERIALIZE_UTILS_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace FD3D
{
    template<typename T>
    struct color_helper;

    template<typename T>
    struct texture_helper;

    template<>
    struct color_helper<glm::vec3>
    {
        glm::vec3 &v;
        color_helper(glm::vec3 &v):
            v(v)
        {}
    };

    template<>
    struct color_helper<const glm::vec3>
    {
        const glm::vec3 &v;
        color_helper(const glm::vec3 &v):
            v(v)
        {}
    };

    template<>
    struct color_helper<glm::vec4>
    {
        glm::vec4 &v;
        color_helper(glm::vec4 &v):
            v(v)
        {}
    };

    template<>
    struct color_helper<const glm::vec4>
    {
        const glm::vec4 &v;
        color_helper(const glm::vec4 &v):
            v(v)
        {}
    };

    template<>
    struct texture_helper<glm::vec2>
    {
        glm::vec2 &v;
        texture_helper(glm::vec2 &v):
            v(v)
        {}
    };

    template<>
    struct texture_helper<const glm::vec2>
    {
        const glm::vec2 &v;
        texture_helper(const glm::vec2 &v):
            v(v)
        {}
    };

    template<>
    struct texture_helper<glm::vec3>
    {
        glm::vec3 &v;
        texture_helper(glm::vec3 &v):
            v(v)
        {}
    };

    template<>
    struct texture_helper<const glm::vec3>
    {
        const glm::vec3 &v;
        texture_helper(const glm::vec3 &v):
            v(v)
        {}
    };

    template<>
    struct texture_helper<glm::vec4>
    {
        glm::vec4 &v;
        texture_helper(glm::vec4 &v):
            v(v)
        {}
    };

    template<>
    struct texture_helper<const glm::vec4>
    {
        const glm::vec4 &v;
        texture_helper(const glm::vec4 &v):
            v(v)
        {}
    };
}

#endif // FD3D_GLM_SERIALIZE_UTILS_H
