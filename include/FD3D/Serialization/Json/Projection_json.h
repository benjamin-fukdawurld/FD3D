#ifndef FD3D_JSONPROJECTION_JSON_H
#define FD3D_JSONPROJECTION_JSON_H

#include <FD3D/Serialization/Json/Projection_json_fwd.h>

#include <rapidjson/document.h>

#include <FDJson/Json_primitive_fwd.h>
#include <FDJson/JsonSerializer.h>

rapidjson::Value FDJson::serialize(const FD3D::ProjectionType &type, FDJson::Serializer &serializer)
{
    return serializer.serialize(FD3D::projectionTypeToString(type).data());
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::ProjectionType &type, FDJson::Serializer &, std::string *err)
{
    if(!val.IsString())
    {
        if(!err)
            *err = "value must be a string";

        return false;
    }

    type = FD3D::projectionTypeFromString(val.GetString());
    if(type == FD3D::ProjectionType::Invalid)
    {
        if(err)
            *err = "ProjectionType is invalide";

        return false;
    }

    return true;
}

rapidjson::Value FDJson::serialize(const FD3D::Projection &proj, FDJson::Serializer &serializer)
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("left", 4u, serializer.getAllocator()),
                     serializer.serialize(proj.getLeft()), serializer.getAllocator());
    result.AddMember(rapidjson::Value("right", 5u, serializer.getAllocator()),
                     serializer.serialize(proj.getRight()), serializer.getAllocator());
    result.AddMember(rapidjson::Value("top", 3u, serializer.getAllocator()),
                     serializer.serialize(proj.getTop()), serializer.getAllocator());
    result.AddMember(rapidjson::Value("bottom", 6u, serializer.getAllocator()),
                     serializer.serialize(proj.getBottom()), serializer.getAllocator());
    result.AddMember(rapidjson::Value("near", 4u, serializer.getAllocator()),
                     serializer.serialize(proj.getNear()), serializer.getAllocator());
    result.AddMember(rapidjson::Value("far", 3u, serializer.getAllocator()),
                     serializer.serialize(proj.getFar()), serializer.getAllocator());
    result.AddMember(rapidjson::Value("fov", 3u, serializer.getAllocator()),
                     serializer.serialize(proj.getFov()), serializer.getAllocator());
    result.AddMember(rapidjson::Value("projectionType", 14u, serializer.getAllocator()),
                     serializer.serialize(proj.getType()), serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::Projection &proj, FDJson::Serializer &serializer, std::string *err)
{
    if(!val.IsObject())
    {
        if(err)
            *err = "value is not an object";

        return false;
    }

    if(!val.HasMember("left"))
    {
        if(err)
            *err = "vertex has no attribute 'left'";

        return false;
    }

    float f;
    if(!serializer.unserialize(val["left"], f, err))
    {
        if(err)
            *err = "error parsing left" + *err;

        return false;
    }
    proj.setLeft(f);

    if(!val.HasMember("right"))
    {
        if(err)
            *err = "vertex has no attribute 'right'";

        return false;
    }

    if(!serializer.unserialize(val["right"], f, err))
    {
        if(err)
            *err = "error parsing right" + *err;

        return false;
    }
    proj.setRight(f);

    if(!val.HasMember("top"))
    {
        if(err)
            *err = "vertex has no attribute 'top'";

        return false;
    }

    if(!serializer.unserialize(val["top"], f, err))
    {
        if(err)
            *err = "error parsing top" + *err;

        return false;
    }
    proj.setTop(f);


    if(!val.HasMember("bottom"))
    {
        if(err)
            *err = "vertex has no attribute 'bottom'";

        return false;
    }

    if(!serializer.unserialize(val["bottom"], f, err))
    {
        if(err)
            *err = "error parsing bottom" + *err;

        return false;
    }
    proj.setBottom(f);


    if(!val.HasMember("near"))
    {
        if(err)
            *err = "vertex has no attribute 'near'";

        return false;
    }

    if(!serializer.unserialize(val["near"], f, err))
    {
        if(err)
            *err = "error parsing near" + *err;

        return false;
    }
    proj.setNear(f);


    if(!val.HasMember("far"))
    {
        if(err)
            *err = "vertex has no attribute 'far'";

        return false;
    }

    if(!serializer.unserialize(val["far"], f, err))
    {
        if(err)
            *err = "error parsing far" + *err;

        return false;
    }
    proj.setFar(f);


    if(!val.HasMember("fov"))
    {
        if(err)
            *err = "vertex has no attribute 'fov'";

        return false;
    }

    if(!serializer.unserialize(val["fov"], f, err))
    {
        if(err)
            *err = "error parsing fov" + *err;

        return false;
    }
    proj.setFov(f);


    if(!val.HasMember("projectionType"))
    {
        if(err)
            *err = "vertex has no attribute 'type'";

        return false;
    }

    FD3D::ProjectionType type;
    if(!serializer.unserialize(val["projectionType"], type, err))
    {
        if(err)
            *err = "error parsing type" + *err;

        return false;
    }
    proj.setType(type);

    return true;
}


#endif // FD3D_JSONPROJECTION_JSON_H
