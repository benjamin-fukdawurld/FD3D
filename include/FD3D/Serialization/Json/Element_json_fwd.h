#ifndef FD3D_ELEMENT_JSON_FWD_H
#define FD3D_ELEMENT_JSON_FWD_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/SceneGraph/Element.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::Element &comp, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::Element &comp, Serializer &serializer, std::string *err = nullptr);
}

#endif // FD3D_ELEMENT_JSON_FWD_H
