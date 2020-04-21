#ifndef SCENENODE_JSON_FWD_H
#define SCENENODE_JSON_FWD_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/SceneGraph/SceneNode.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::SceneNode &node, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::SceneNode &node, Serializer &serializer, std::string *err = nullptr);

    template<typename T>
    rapidjson::Value serialize(const FD3D::EntityNode<T> &node, Serializer &serializer);

    template<typename T>
    bool unserialize(const rapidjson::Value &val, FD3D::EntityNode<T> &node, Serializer &serializer, std::string *err = nullptr);
}

#endif // SCENENODE_JSON_FWD_H
