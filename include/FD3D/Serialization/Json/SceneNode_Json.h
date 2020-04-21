#ifndef SCENENODE_JSON_H
#define SCENENODE_JSON_H

#include <FD3D/Serialization/Json/SceneNode_Json_fwd.h>

#include <FDJson/JsonSerializer.h>

namespace FDJson
{
    template<typename T>
    rapidjson::Value serialize(const FD3D::EntityNode<T> &node, Serializer &serializer)
    {
        rapidjson::Value result = serializer.serialize(static_cast<const FD3D::SceneNode&>(node));
        result.AddMember(serializer.serialize("entity"),
                         serializer.serialize(node.getEntity()));

        return result;
    }

    template<typename T>
    bool unserialize(const rapidjson::Value &val, FD3D::EntityNode<T> &node, Serializer &serializer, std::string *err)
    {
        if(!serializer.unserialize(val, static_cast<FD3D::SceneNode&>(node), err))
            return false;

        if(!val.HasMember("entity"))
        {
            if(err)
                *err += "value has no member 'entity'";

            return false;
        }

        if(!serializer.unserialize(val["entity"], node.getEntity(), err))
        {
            if(err)
                *err += "Error parsing entity: " + *err;

            return false;
        }

        return true;
    }
}

#endif // SCENENODE_JSON_H
