#ifndef FD3D_MESH_JSON_H
#define FD3D_MESH_JSON_H

#include <FD3D/Serialization/Json/Component_json_fwd.h>
#include <FD3D/Serialization/Json/VertexProxy_json_fwd.h>
#include <FD3D/Serialization/Json/Scene_json_fwd.h>

#include <FD3D/Serialization/Json/Material_json_fwd.h>

#include <FDJson/JsonSerializer.h>

#include <FD3D/Mesh/MeshComponent.h>
#include <FD3D/Mesh/Mesh.h>
#include <FD3D/SceneGraph/SceneManager.h>

namespace FDJson
{
    template<typename T>
    std::enable_if_t<std::is_same_v<T, FD3D::AbstractMesh> || std::is_same_v<T, FD3D::Mesh>,
    rapidjson::Value> serialize(const T &mesh, FDJson::Serializer &serializer)
    {
        rapidjson::Value result(serializer.serialize(static_cast<const FDCore::AbstractResource&>(mesh)));
        result.AddMember(serializer.serialize("flags"), serializer.serialize(mesh.getComponentFlags()), serializer.getAllocator());

        const FD3D::Material *mat = mesh.getMaterial();
        if(mat)
            result.AddMember(serializer.serialize("material"), serializer.serialize(mat->getResourcePath()), serializer.getAllocator());
        else
            result.AddMember(serializer.serialize("material"), serializer.serialize(nullptr), serializer.getAllocator());

        const FDCore::AbstractResource *shad = mesh.getShader();
        if(shad)
            result.AddMember(serializer.serialize("shader"), serializer.serialize(shad->getResourcePath()), serializer.getAllocator());
        else
            result.AddMember(serializer.serialize("shader"), serializer.serialize(nullptr), serializer.getAllocator());

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

    template<typename T>
    std::enable_if_t<std::is_same_v<T, FD3D::AbstractMesh> || std::is_same_v<T, FD3D::Mesh>,
    bool> unserialize(const rapidjson::Value &val, T &mesh, FDJson::Serializer &serializer, std::string *err)
    {
        if(!serializer.unserialize(val, static_cast<FDCore::BaseResource&>(mesh), err))
            return false;

        FD3D::SceneManager *mgr = serializer.getUserDataAs<FD3D::SceneManager>();
        if(mgr)
        {
            {
                if(!val.HasMember("material"))
                {
                    if(err)
                        *err = "value has no attribute material";

                    return false;
                }

                if(val["material"].IsNull())
                    mesh->setMaterial(nullptr);
                else
                {
                    int index;
                    if(!serializer.unserialize(val["material"], index, err))
                    {
                        if(err)
                            *err = "Error parsing material id: " + *err;

                        return false;
                    }

                    FD3D::Element::id_type id = mgr->getIndexId(index);
                    if(id == 0)
                    {
                        if(err)
                            *err = "Error parsing material id: id does not exist";

                        return false;
                    }

                    mesh.setMaterialId(id);
                }
            }
            /*
            {
                if(!val.HasMember("shader"))
                {
                    if(err)
                        *err = "value has no attribute shader";

                    return false;
                }

                if(!val["shader"].IsNull())
                {
                    int index;
                    if(!serializer.unserialize(val["shader"], index, err))
                    {
                        if(err)
                            *err = "Error parsing shader id: " + *err;

                        return false;
                    }

                    FD3D::Element::id_type id = mgr->getIndexId(index);
                    if(id == 0)
                    {
                        if(err)
                            *err = "Error parsing shader id: id does not exist";

                        return false;
                    }
                    mesh.setShaderId(id);
                }
            }*/
        }

        {
            if(!val.HasMember("flags"))
            {
                if(err)
                    *err = "value has no attribute flags";

                return false;
            }

            FD3D::VertexComponentFlag flags;
            if(!serializer.unserialize(val["flags"], flags, err))
            {
                if(err)
                    *err = "Error parsing vertex component flags: " + *err;

                return false;
            }
            mesh.setComponentsFlags(flags);
        }

        {
            if(!val.HasMember("numberOfColorChannels"))
            {
                if(err)
                    *err = "value has no attribute numberOfColorChannels";

                return false;
            }

            uint16_t nb;
            if(!serializer.unserialize(val["numberOfColorChannels"], nb, err))
            {
                if(err)
                    *err = "Error parsing numberOfColorChannels: " + *err;

                return false;
            }
            mesh.setNumberOfColorChannel(static_cast<uint8_t>(nb));
        }

        {
            if(!val.HasMember("numberOfTextureChannels"))
            {
                if(err)
                    *err = "value has no attribute numberOfTextureChannels";

                return false;
            }

            uint16_t nb;
            if(!serializer.unserialize(val["numberOfTextureChannels"], nb, err))
            {
                if(err)
                    *err = "Error parsing numberOfTextureChannels: " + *err;

                return false;
            }
            mesh.setNumberOfUvChannel(static_cast<uint8_t>(nb));
        }

        {
            if(!val.HasMember("isInterlaced"))
            {
                if(err)
                    *err = "value has no attribute isInterlaced";

                return false;
            }

            bool b;
            if(!serializer.unserialize(val["isInterlaced"], b, err))
            {
                if(err)
                    *err = "Error parsing isInterlaced: " + *err;

                return false;
            }

            mesh.setInterlaced(b);
        }

        {
            if(!val.HasMember("indices"))
            {
                if(err)
                    *err = "value has no attribute indices";

                return false;
            }

            const rapidjson::Value &ind = val["indices"];
            if(!ind.IsArray())
            {
                if(err)
                    *err = "indices attribute is not an array";

                return false;
            }

            mesh.setNumberOfIndices(ind.Size());
            if(!serializer.unserialize(ind, mesh.getIndices(), mesh.getNumberOfIndices(), err))
            {
                if(err)
                    *err = "Error parsing indices: " + *err;

                return false;
            }
        }

        {
            if(!val.HasMember("vertices"))
            {
                if(err)
                    *err = "value has no attribute vertices";

                return false;
            }

            const rapidjson::Value &vert = val["vertices"];
            if(!vert.IsArray())
            {
                if(err)
                    *err = "vertices attribute is not an array";

                return false;
            }

            mesh.setNumberOfVertices(vert.Size());
            for(size_t i = 0, imax = mesh.getNumberOfVertices(); i < imax; ++i)
            {
                FD3D::VertexProxy2 v = mesh.getVertex(i);
                if(!serializer.unserialize(vert[static_cast<rapidjson::SizeType>(i)], v, err))
                {
                    if(err)
                        *err = "Error parsing vertices: " + *err;

                    return false;
                }
            }
        }

        return true;
    }

    template<typename T>
    std::enable_if_t<std::is_same_v<T, FD3D::AbstractMeshComponent> || std::is_same_v<T, FD3D::MeshComponent>,
    rapidjson::Value> serialize(const T &mesh, FDJson::Serializer &serializer)
    {
        rapidjson::Value result(serializer.serialize(static_cast<const FD3D::Component&>(mesh)));
        result.AddMember(serializer.serialize("flags"), serializer.serialize(mesh.getComponentFlags()), serializer.getAllocator());

        FD3D::SceneManager *mgr = serializer.getUserDataAs<FD3D::SceneManager>();
        if(mgr)
        {
            int materialId = mgr->getIdIndex(mesh.getMaterialId());
            assert(materialId != FD3D::SceneManager::IndexError);
            int shaderId = mgr->getIdIndex(mesh.getShaderId());
            assert(shaderId != FD3D::SceneManager::IndexError);

            if(materialId == FD3D::SceneManager::NoIndex)
            result.AddMember(serializer.serialize("material"), serializer.serialize(nullptr), serializer.getAllocator());
            else
            result.AddMember(serializer.serialize("material"), serializer.serialize(materialId), serializer.getAllocator());

            if(shaderId == FD3D::SceneManager::NoIndex)
            result.AddMember(serializer.serialize("shader"), serializer.serialize(nullptr), serializer.getAllocator());
            else
            result.AddMember(serializer.serialize("shader"), serializer.serialize(shaderId), serializer.getAllocator());
        }
        else
        {
            result.AddMember(serializer.serialize("material"), serializer.serialize(mesh.getMaterialId()),
                             serializer.getAllocator());
            result.AddMember(serializer.serialize("shader"), serializer.serialize(mesh.getShaderId()),
                             serializer.getAllocator());
        }
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

    template<typename T>
    std::enable_if_t<std::is_same_v<T, FD3D::AbstractMeshComponent> || std::is_same_v<T, FD3D::MeshComponent>,
    bool> unserialize(const rapidjson::Value &val, T &mesh, FDJson::Serializer &serializer, std::string *err)
    {
        if(!serializer.unserialize(val, static_cast<FD3D::Component&>(mesh), err))
            return false;

        //FD3D::SceneManager *mgr = serializer.getUserDataAs<FD3D::SceneManager>();
        {
            if(!val.HasMember("flags"))
            {
                if(err)
                    *err = "value has no attribute flags";

                return false;
            }

            FD3D::VertexComponentFlag flags;
            if(!serializer.unserialize(val["flags"], flags, err))
            {
                if(err)
                    *err = "Error parsing vertex component flags: " + *err;

                return false;
            }
            mesh.setComponentsFlags(flags);
        }

        /*{
            if(!val.HasMember("material"))
            {
                if(err)
                    *err = "value has no attribute material";

                return false;
            }

            if(!val["material"].IsNull())
            {
                int index;
                if(!serializer.unserialize(val["material"], index, err))
                {
                    if(err)
                        *err = "Error parsing material id: " + *err;

                    return false;
                }

                FD3D::Element::id_type id = mgr->getIndexId(index);
                if(id == 0)
                {
                    if(err)
                        *err = "Error parsing material id: id does not exist";

                    return false;
                }

                mesh.setMaterialId(id);
            }
        }

        {
            if(!val.HasMember("shader"))
            {
                if(err)
                    *err = "value has no attribute shader";

                return false;
            }

            if(!val["shader"].IsNull())
            {
                int index;
                if(!serializer.unserialize(val["shader"], index, err))
                {
                    if(err)
                        *err = "Error parsing shader id: " + *err;

                    return false;
                }

                FD3D::Element::id_type id = mgr->getIndexId(index);
                if(id == 0)
                {
                    if(err)
                        *err = "Error parsing shader id: id does not exist";

                    return false;
                }
                mesh.setShaderId(id);
            }
        }*/

        {
            if(!val.HasMember("numberOfColorChannels"))
            {
                if(err)
                    *err = "value has no attribute numberOfColorChannels";

                return false;
            }

            uint16_t nb;
            if(!serializer.unserialize(val["numberOfColorChannels"], nb, err))
            {
                if(err)
                    *err = "Error parsing numberOfColorChannels: " + *err;

                return false;
            }
            mesh.setNumberOfColorChannel(static_cast<uint8_t>(nb));
        }

        {
            if(!val.HasMember("numberOfTextureChannels"))
            {
                if(err)
                    *err = "value has no attribute numberOfTextureChannels";

                return false;
            }

            uint16_t nb;
            if(!serializer.unserialize(val["numberOfTextureChannels"], nb, err))
            {
                if(err)
                    *err = "Error parsing numberOfTextureChannels: " + *err;

                return false;
            }
            mesh.setNumberOfUvChannel(static_cast<uint8_t>(nb));
        }

        {
            if(!val.HasMember("isInterlaced"))
            {
                if(err)
                    *err = "value has no attribute isInterlaced";

                return false;
            }

            bool b;
            if(!serializer.unserialize(val["isInterlaced"], b, err))
            {
                if(err)
                    *err = "Error parsing isInterlaced: " + *err;

                return false;
            }

            mesh.setInterlaced(b);
        }

        {
            if(!val.HasMember("indices"))
            {
                if(err)
                    *err = "value has no attribute indices";

                return false;
            }

            const rapidjson::Value &ind = val["indices"];
            if(!ind.IsArray())
            {
                if(err)
                    *err = "indices attribute is not an array";

                return false;
            }

            mesh.setNumberOfIndices(ind.Size());
            if(!serializer.unserialize(ind, mesh.getIndices(), mesh.getNumberOfIndices(), err))
            {
                if(err)
                    *err = "Error parsing indices: " + *err;

                return false;
            }
        }

        {
            if(!val.HasMember("vertices"))
            {
                if(err)
                    *err = "value has no attribute vertices";

                return false;
            }

            const rapidjson::Value &vert = val["vertices"];
            if(!vert.IsArray())
            {
                if(err)
                    *err = "vertices attribute is not an array";

                return false;
            }

            mesh.setNumberOfVertices(vert.Size());
            for(size_t i = 0, imax = mesh.getNumberOfVertices(); i < imax; ++i)
            {
                FD3D::VertexProxy2 v = mesh.getVertex(i);
                if(!serializer.unserialize(vert[static_cast<rapidjson::SizeType>(i)], v, err))
                {
                    if(err)
                        *err = "Error parsing vertices: " + *err;

                    return false;
                }
            }
        }

        return true;
    }
}

#endif // FD3D_MESH_JSON_H
