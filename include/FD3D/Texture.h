#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>
#include <string>

namespace FD3D
{
    class Texture
    {
        protected:
            uint32_t m_id;
            std::string m_type;

        public:
            Texture() : m_id(0), m_type() {}
            Texture(uint32_t id, const std::string &type) : m_id(id), m_type(type) {}

            uint32_t getId() const
            {
                return m_id;
            }

            void setId(uint32_t id)
            {
                m_id = id;
            }

            const std::string &getType() const
            {
                return m_type;
            }

            void setType(const std::string &type)
            {
                m_type = type;
            }
    };
}

#endif // TEXTURE_H
