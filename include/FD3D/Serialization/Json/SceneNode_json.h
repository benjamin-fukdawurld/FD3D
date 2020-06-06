#ifndef FD3D_SCENENODE_JSON_H
#define FD3D_SCENENODE_JSON_H

#include <FD3D/Serialization/Json/SceneNode_json_fwd.h>
#include <FD3D/Serialization/Json/Scene_json_fwd.h>

#include <FDJson/Json_fwd.h>
#include <FDJson/JsonSerializer.h>

#include <FD3D/SceneGraph/SceneManager.h>

namespace FDJson
{
    FD_INLINE rapidjson::Value serialize(const FD3D::SceneNode &node, FDJson::Serializer &serializer)
    {
        rapidjson::Value result(serializer.serialize(static_cast<const FD3D::Element&>(node)));

        FD3D::SceneManager *mgr = serializer.getUserDataAs<FD3D::SceneManager>();
        if(mgr)
        {
            int parentId = mgr->getIdIndex(node.getParentId());
            assert(parentId != FD3D::SceneManager::IndexError);
            if(parentId != FD3D::SceneManager::NoIndex)
                result.AddMember(serializer.serialize("parent"), serializer.serialize(parentId), serializer.getAllocator());
            else
                result.AddMember(serializer.serialize("parent"), serializer.serialize(nullptr), serializer.getAllocator());


            rapidjson::Value children(rapidjson::kArrayType);
            for(auto id: node.getChildIds())
            {
                int childId = mgr->getIdIndex(id);
                assert(childId > FD3D::SceneManager::NoIndex);
                children.PushBack(childId, serializer.getAllocator());
            }
            result.AddMember(serializer.serialize("children"), children, serializer.getAllocator());

            rapidjson::Value components(rapidjson::kArrayType);
            for(auto comp: mgr->getScene()->getNodeComponents(node.getId()))
            {
                int compId = mgr->getIdIndex(comp->getId());
                assert(compId > FD3D::SceneManager::NoIndex);
                components.PushBack(compId, serializer.getAllocator());
            }
            result.AddMember(serializer.serialize("components"), components, serializer.getAllocator());
        }
        else
        {
            result.AddMember(serializer.serialize("id"), serializer.serialize(node.getId()),
                                 serializer.getAllocator());
            result.AddMember(serializer.serialize("parent"), serializer.serialize(node.getParentId()),
                             serializer.getAllocator());
            result.AddMember(serializer.serialize("children"), serializer.serialize(node.getChildIds()), serializer.getAllocator());
        }

        result.AddMember(serializer.serialize("name"), serializer.serialize(node.getName()), serializer.getAllocator());
        result.AddMember(serializer.serialize("isEnabled"), serializer.serialize(node.isEnabled()), serializer.getAllocator());

        return result;
    }

    FD_INLINE bool unserialize(const rapidjson::Value &val, FD3D::SceneNode &node, Serializer &serializer, std::string *err)
    {
        if(!serializer.unserialize(val, static_cast<FD3D::Element&>(node), err))
            return false;

        FD3D::SceneManager *mgr = serializer.getUserDataAs<FD3D::SceneManager>();
        {
            if(!val.HasMember("name"))
            {
                if(err)
                    *err = "value has no attribute 'name'";

                return false;
            }

            std::string str;
            if(!serializer.unserialize(val["name"], str, err))
            {
                if(err)
                    *err = "Error parsing attribute name: " + *err;

                return false;
            }

            node.setName(str);
        }

        {
            if(!val.HasMember("isEnabled"))
            {
                if(err)
                    *err = "value has no attribute 'isEnabled'";

                return false;
            }

            bool b;
            if(!serializer.unserialize(val["isEnabled"], b, err))
            {
                if(err)
                    *err = "Error parsing attribute isEnabled: " + *err;

                return false;
            }

            if(b)
                node.enable();
            else
                node.disable();
        }

        {
            if(!val.HasMember("parent"))
            {
                if(err)
                    *err = "value has no attribute 'parent'";

                return false;
            }

            const rapidjson::Value &parent = val["parent"];
            if(!parent.IsNull())
            {
                int index;
                if(!serializer.unserialize(parent, index, err))
                {
                    if(err)
                        *err = "Error parsing attribute isEnabled: " + *err;

                    return false;
                }

                FD3D::SceneNode::id_type id = mgr->getIndexId(index);
                assert(id > 0 && "Parent id is invalid");
                node.setParentId(id);
            }
        }

        return true;
    }


    template<typename T>
    rapidjson::Value serialize(const FD3D::EntityNode<T> &node, Serializer &serializer)
    {
        rapidjson::Value result = serializer.serialize(static_cast<const FD3D::SceneNode&>(node));

        FD3D::SceneManager *mgr = serializer.getUserDataAs<FD3D::SceneManager>();
        if(mgr)
        {
            int id = mgr->getIdIndex(node.getEntity()->getId());
            assert(id != FD3D::SceneManager::IndexError);
            if(id >= FD3D::SceneManager::NoIndex)
                result.AddMember(serializer.serialize("entity"), serializer.serialize(id), serializer.getAllocator());
            else
                result.AddMember(serializer.serialize("entity"), serializer.serialize(nullptr), serializer.getAllocator());

        }
        else
            result.AddMember(serializer.serialize("entity"),
                             serializer.serialize(node.getEntity()->getId()), serializer.getAllocator());

        return result;
    }

    template<typename T>
    bool unserialize(const rapidjson::Value &val, FD3D::EntityNode<T> &node, Serializer &serializer, std::string *err)
    {
        if(!serializer.unserialize(val, static_cast<FD3D::SceneNode&>(node), err))
            return false;

        FD3D::SceneManager *mgr = serializer.getUserDataAs<FD3D::SceneManager>();
        if(!val.HasMember("entity"))
        {
            if(err)
                *err = "value has no member 'entity'";

            return false;
        }

        int index;
        if(!serializer.unserialize(val["entity"], index, err))
        {
            if(err)
                *err = "Error parsing entity: " + *err;

            return false;
        }

        FD3D::Element::id_type id = mgr->getIndexId(index);
        if(id == 0)
        {
            if(err)
                *err = "Error parsing entity: id '" + std::to_string(index) + "' does not exist";

            return false;
        }

        node.setEntity(static_cast<T*>(mgr->getScene()->getComponent(id)));
        return true;
    }
}

#endif // FD3D_SCENENODE_JSON_H
