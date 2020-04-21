#include <FD3D/Serialization/Json/Mesh_Json.h>

#include <FD3D/Serialization/Json/VertexProxy_Json.h>
#include <FD3D/Serialization/Json/Component_Json.h>
#include <FD3D/Serialization/Json/Glm_Json_utils.h>
#include <FDJson/Json_primitive.h>
#include <FDJson/JsonSerializer.h>
#include <FDJson/Json_utils.h>


rapidjson::Value FDJson::serialize(const FD3D::AbstractMesh &mesh, FDJson::Serializer &serializer)
{
    rapidjson::Value result(serializer.serialize(static_cast<const FD3D::Component&>(mesh)));
    result.AddMember(serializer.serialize("flags"), serializer.serialize(mesh.getComponentFlags()), serializer.getAllocator());
    result.AddMember(serializer.serialize("material"), serializer.serialize(mesh.getMaterialId()), serializer.getAllocator());
    result.AddMember(serializer.serialize("shader"), serializer.serialize(mesh.getShaderId()), serializer.getAllocator());
    result.AddMember(serializer.serialize("numberOfColorChannels"),
                     serializer.serialize(static_cast<uint16_t>(mesh.getNumberOfColorChannel())), serializer.getAllocator());
    result.AddMember(serializer.serialize("numberOfTextureChannels"),
                     serializer.serialize(static_cast<uint16_t>(mesh.getNumberOfUvChannel())), serializer.getAllocator());
    result.AddMember(serializer.serialize("isInterlaced"), serializer.serialize(mesh.isInterlaced()), serializer.getAllocator());
    result.AddMember(serializer.serialize("indices"), serializer.serialize(mesh.getIndices(), mesh.getNumberOfIndices()),
                     serializer.getAllocator());

    rapidjson::Value vert(rapidjson::kArrayType);
    for(size_t i = 0, imax = mesh.getNumberOfVertices(); i < imax; ++i)
        vert.PushBack(serializer.serialize(mesh.getVertex(i)), serializer.getAllocator());

    result.AddMember(serializer.serialize("vertices"), vert, serializer.getAllocator());

    return result;
}

bool FDJson::unserialize(const rapidjson::Value &val, FD3D::AbstractMesh &mesh, FDJson::Serializer &serializer, std::string *err)
{
    if(!serializer.unserialize(val, static_cast<FD3D::Component&>(mesh), err))
        return false;

    {
        if(!val.HasMember("flags"))
        {
            if(err)
                *err += "value has no attribute flags";

            return false;
        }

        FD3D::VertexComponentFlag flags;
        if(serializer.unserialize(val["flags"], flags, err))
        {
            if(err)
                *err += "Error parsing vertex component flags: " + *err;

            return false;
        }
        mesh.setComponentsFlags(flags);
    }

    {
        if(!val.HasMember("material"))
        {
            if(err)
                *err += "value has no attribute material";

            return false;
        }

        FD3D::Component::id_type id;
        if(serializer.unserialize(val["material"], id, err))
        {
            if(err)
                *err += "Error parsing material id: " + *err;

            return false;
        }
        mesh.setMaterialId(id);
    }

    {
        if(!val.HasMember("shader"))
        {
            if(err)
                *err += "value has no attribute shader";

            return false;
        }

        FD3D::Component::id_type id;
        if(serializer.unserialize(val["shader"], id, err))
        {
            if(err)
                *err += "Error parsing shader id: " + *err;

            return false;
        }
        mesh.setShaderId(id);
    }

    {
        if(!val.HasMember("numberOfColorChannels"))
        {
            if(err)
                *err += "value has no attribute numberOfColorChannels";

            return false;
        }

        uint16_t nb;
        if(serializer.unserialize(val["numberOfColorChannels"], nb, err))
        {
            if(err)
                *err += "Error parsing numberOfColorChannels: " + *err;

            return false;
        }
        mesh.setNumberOfColorChannel(static_cast<uint8_t>(nb));
    }

    {
        if(!val.HasMember("numberOfTextureChannels"))
        {
            if(err)
                *err += "value has no attribute numberOfTextureChannels";

            return false;
        }

        uint16_t nb;
        if(serializer.unserialize(val["numberOfTextureChannels"], nb, err))
        {
            if(err)
                *err += "Error parsing numberOfTextureChannels: " + *err;

            return false;
        }
        mesh.setNumberOfUvChannel(static_cast<uint8_t>(nb));
    }

    {
        if(!val.HasMember("isInterlaced"))
        {
            if(err)
                *err += "value has no attribute isInterlaced";

            return false;
        }

        bool b;
        if(serializer.unserialize(val["isInterlaced"], b, err))
        {
            if(err)
                *err += "Error parsing isInterlaced: " + *err;

            return false;
        }

        mesh.setInterlaced(b);
    }

    {
        if(!val.HasMember("indices"))
        {
            if(err)
                *err += "value has no attribute indices";

            return false;
        }

        const rapidjson::Value &ind = val["indices"];
        if(!ind.IsArray())
        {
            if(err)
                *err += "indices attribute is not an array";

            return false;
        }

        mesh.setNumberOfIndices(ind.Size());
        if(serializer.unserialize(ind, mesh.getIndices(), mesh.getNumberOfIndices(), err))
        {
            if(err)
                *err += "Error parsing indices: " + *err;

            return false;
        }
    }

    {
        if(!val.HasMember("vertices"))
        {
            if(err)
                *err += "value has no attribute vertices";

            return false;
        }

        const rapidjson::Value &vert = val["vertices"];
        if(!vert.IsArray())
        {
            if(err)
                *err += "vertices attribute is not an array";

            return false;
        }

        mesh.setNumberOfVertices(vert.Size());
        for(size_t i = 0, imax = mesh.getNumberOfVertices(); i < imax; ++i)
        {
            FD3D::VertexProxy v = mesh.getVertex(i);
            if(serializer.unserialize(vert[static_cast<rapidjson::SizeType>(i)], v, err))
            {
                if(err)
                    *err += "Error parsing vertices: " + *err;

                return false;
            }
        }
    }

    return true;
}

