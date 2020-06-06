#ifndef FD3D_ELEMENT_JSON_H
#define FD3D_ELEMENT_JSON_H

#include <FD3D/Serialization/Json/Element_json_fwd.h>
#include <FDCore/Serialization/Json/Object_json_fwd.h>

#include <FD3D/SceneGraph/SceneManager.h>

#include <rapidjson/document.h>

#include <FDJson/JsonSerializer.h>

namespace FDJson
{
    FD_INLINE rapidjson::Value serialize(const FD3D::Element &elm, FDJson::Serializer &serializer)
    {
        rapidjson::Value result(serializer.serialize(static_cast<const FDCore::Object&>(elm)));

        FD3D::SceneManager *mgr = serializer.getUserDataAs<FD3D::SceneManager>();
        if(mgr)
        {
            int id = mgr->getIdIndex(elm.getId());
            assert(id > FD3D::SceneManager::NoIndex);
            result.AddMember(serializer.serialize("id"), serializer.serialize(id), serializer.getAllocator());
        }
        else
            result.AddMember(serializer.serialize("id"), serializer.serialize(elm.getId()), serializer.getAllocator());

        return result;
    }

    FD_INLINE bool unserialize(const rapidjson::Value &val, FD3D::Element &elm, FDJson::Serializer &serializer, std::string *err)
    {
        if(!serializer.unserialize(val, static_cast<FDCore::Object&>(elm), err))
            return false;

        if(!val.HasMember("id"))
        {
            if(err)
                *err = "value has no id";

            return false;
        }

        int id;
        if(!serializer.unserialize(val["id"], id, err))
        {
            if(err)
                *err = "unable to userialize id: " + *err;

            return false;
        }

        FD3D::SceneManager *mgr = serializer.getUserDataAs<FD3D::SceneManager>();
        mgr->setIdIndex(elm.getId(), id);

        return true;
    }
}

#endif // FD3D_ELEMENT_JSON_H
