#include <FD3D/SceneGraph/SceneLoader.h>

#include <limits>
#include <iostream>
#include <queue>

#include <assimp/scene.h>

static aiTextureType toAssimpType(FD3D::TextureType type)
{
    switch (type)
    {
        case FD3D::TextureType::None:
            return aiTextureType_NONE;

        case FD3D::TextureType::Height:
            return aiTextureType_HEIGHT;

        case FD3D::TextureType::Ambient:
            return aiTextureType_AMBIENT;

        case FD3D::TextureType::Diffuse:
            return aiTextureType_DIFFUSE;

        case FD3D::TextureType::Normals:
            return aiTextureType_NORMALS;

        case FD3D::TextureType::Opacity:
            return aiTextureType_OPACITY;

        case FD3D::TextureType::Emissive:
            return aiTextureType_EMISSIVE;

        case FD3D::TextureType::LightMap:
            return aiTextureType_LIGHTMAP;

        case FD3D::TextureType::Specular:
            return aiTextureType_SPECULAR;

        case FD3D::TextureType::Shininess:
            return aiTextureType_SHININESS;

        case FD3D::TextureType::Reflection:
            return aiTextureType_REFLECTION;

        case FD3D::TextureType::Displacement:
            return aiTextureType_DISPLACEMENT;

        case FD3D::TextureType::Invalid:
            return aiTextureType_UNKNOWN;
    }

    return aiTextureType_UNKNOWN;
}


FD3D::AbstractSceneLoader::AbstractSceneLoader()
{
    aiString str;
    m_importer.GetExtensionList(str);
    std::clog << str.C_Str() << std::endl;
}

FD3D::AbstractSceneLoader::~AbstractSceneLoader() {}

bool FD3D::AbstractSceneLoader::loadScene(Scene &result, const std::string &path, unsigned int flags)
{
    m_scene = internal2::importScene(m_importer, path, flags);
    if(!m_scene)
        return false;

    m_lights.clear();
    m_meshes.clear();
    m_cameras.clear();
    m_materials.clear();

    if(path.find('/') != std::string::npos)
        m_directory = path.substr(0, path.find_last_of('/') + 1);

    if(!loadMaterials(result) || !loadMeshes(result) || !loadLights(result) || !loadCameras(result))
        return false;

    return loadNodes(result);
}

bool FD3D::AbstractSceneLoader::loadMaterials(Scene &out)
{
    for(size_t i = 0, imax = m_scene->mNumMaterials; i < imax; ++i)
    {
        if(!loadMaterial(m_scene->mMaterials[i], out))
            return false;
    }

    return true;
}

bool FD3D::AbstractSceneLoader::loadLights(Scene &out)
{
    for(size_t i = 0, imax = m_scene->mNumLights; i < imax; ++i)
    {
        if(!loadLight(m_scene->mLights[i], out))
            return false;
    }

    return true;
}

bool FD3D::AbstractSceneLoader::loadMeshes(Scene &out)
{
    for(size_t i = 0, imax = m_scene->mNumMeshes; i < imax; ++i)
    {
        if(!loadMesh(m_scene->mMeshes[i], out))
            return false;
    }

    return true;
}

bool FD3D::AbstractSceneLoader::loadCameras(Scene &out)
{
    for(size_t i = 0, imax = m_scene->mNumCameras; i < imax; ++i)
    {
        if(!loadCamera(m_scene->mCameras[i], out))
            return false;
    }

    return true;
}

bool FD3D::AbstractSceneLoader::loadNodes(FD3D::Scene &out)
{
    std::queue<std::pair<Scene::node_id_type, const aiNode *>> todo;
    todo.push(std::make_pair(out.getRootId(), m_scene->mRootNode));
    while(!todo.empty())
    {
        Scene::node_id_type parent = 0;
        const aiNode *node = nullptr;
        {
            std::pair<Scene::node_id_type, const aiNode *> current = todo.front();
            parent = current.first;
            node = current.second;
            todo.pop();
        }

        Scene::node_id_type id = loadNode(node, out, parent);
        for(size_t i = 0; i < node->mNumChildren; ++i)
            todo.push(std::make_pair(id, node->mChildren[i]));
    }

    return true;
}

bool FD3D::AbstractSceneLoader::loadMaterial(const aiMaterial *in, Scene &out)
{
    std::unique_ptr<MaterialComponent> result(new MaterialComponent());
    auto textureLoop = [in, &result, this](TextureType type)
    {
        aiTextureType t = toAssimpType(type);
        for(size_t i = 0, imax = in->GetTextureCount(t); i < imax; ++i)
        {
            aiString path;

            in->GetTexture(t, static_cast<unsigned int>(i), &path);
            std::string texpath = this->getDirectory() + path.C_Str();

            uint32_t tex = 0;
            auto it = m_textures.find(texpath);
            if(it != m_textures.end())
                tex = it->value;
            else
            {
                if(path.C_Str()[0] != '*')
                {
                    tex = this->loadTexture(texpath);
                    if(tex == 0)
                    {
                        std::cerr << "Unable to load texture '" << texpath << "'" << std::endl;
                        continue;
                    }
                }
                else
                {
                    size_t index = std::stoul(path.C_Str() + 1);
                    tex = this->loadEmbeddedTexture(m_scene->mTextures[index]);
                    if(tex == 0)
                    {
                        std::cerr << "Unable to load embedded texture '" << index << "'" << std::endl;
                        continue;
                    }
                }

                m_textures.insert(texpath, tex);
            }

            result->getTextures(type).push_back(tex);
        }

        return true;
    };

    if(
       !(
           textureLoop(FD3D::TextureType::None)
        && textureLoop(FD3D::TextureType::Height)
        && textureLoop(FD3D::TextureType::Ambient)
        && textureLoop(FD3D::TextureType::Diffuse)
        && textureLoop(FD3D::TextureType::Invalid)
        && textureLoop(FD3D::TextureType::Normals)
        && textureLoop(FD3D::TextureType::Opacity)
        && textureLoop(FD3D::TextureType::Emissive)
        && textureLoop(FD3D::TextureType::LightMap)
        && textureLoop(FD3D::TextureType::Specular)
        && textureLoop(FD3D::TextureType::Shininess)
        && textureLoop(FD3D::TextureType::Reflection)
        && textureLoop(FD3D::TextureType::Displacement)
        )
       )
       return false;

    aiColor3D color;
    aiString name;
    float shininess;

    if(in->Get(AI_MATKEY_NAME, name) == AI_SUCCESS)
        result->setName(name.C_Str());

    if(in->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
        result->setShininess(shininess);

    if(in->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
        result->setDiffuseColor({color.r, color.g, color.b});

    if(in->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
        result->setAmbientColor({color.r, color.g, color.b});

    if(in->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
        result->setSpecularColor({color.r, color.g, color.b});


    m_materials.push_back(result->getId());
    out.addComponent(result.release());
    return true;
}

bool FD3D::AbstractSceneLoader::loadLight(const aiLight *in, Scene &out)
{
    std::unique_ptr<LightNode> node(new LightNode());
    std::unique_ptr<Light> light(new Light());
    switch (in->mType)
    {
        case aiLightSource_AREA:
            light->setType(LightType::AreaLight);
        break;

        case aiLightSource_SPOT:
            light->setType(LightType::SpotLight);
        break;

        case aiLightSource_POINT:
            light->setType(LightType::PointLight);
        break;

        case aiLightSource_AMBIENT:
            light->setType(LightType::AmbientLight);
        break;

        case aiLightSource_DIRECTIONAL:
            light->setType(LightType::DirectionalLight);
        break;

        case aiLightSource_UNDEFINED:
        default:
            light->setType(LightType::Invalid);
        break;
    }

    node->setName(in->mName.C_Str());
    light->setPosition(
        {
            in->mPosition.x,
            in->mPosition.y,
            in->mPosition.z
        }
    );

    light->setDirection(
        {
            in->mDirection.x,
            in->mDirection.y,
            in->mDirection.z
        }
    );

    light->setUp(
        {
            in->mUp.x,
            in->mUp.y,
            in->mUp.z
        }
    );

    light->color.ambient = {
        in->mColorAmbient.r,
        in->mColorAmbient.g,
        in->mColorAmbient.b,
        1.0f
    };

    light->color.diffuse = {
        in->mColorDiffuse.r,
        in->mColorDiffuse.g,
        in->mColorDiffuse.b,
        1.0f
    };

    light->color.specular = {
        in->mColorSpecular.r,
        in->mColorSpecular.g,
        in->mColorSpecular.b,
        1.0f
    };

    m_lights.push_back(node->getId());
    node->setEntity(light.get());
    out.addComponent(light.release());
    out.addNode(node.release());

    return true;
}

bool FD3D::AbstractSceneLoader::loadCamera(const aiCamera *in, Scene &out)
{
    std::unique_ptr<CameraNode> node(new CameraNode());
    std::unique_ptr<Camera> cam(new Camera());
    cam->projection.setFar(in->mClipPlaneFar);
    cam->projection.setNear(in->mClipPlaneNear);
    cam->projection.setFov(in->mHorizontalFOV);
    cam->projection.setHeight(1);
    cam->projection.setWidth(in->mAspect);
    cam->projection.setType(FD3D::ProjectionType::Perspective);

    cam->setPosition({
        in->mLookAt.x,
        in->mLookAt.y,
        in->mLookAt.z
    });

    glm::vec3 v = {
        in->mLookAt.x,
        in->mLookAt.y,
        in->mLookAt.z
    };

    glm::vec3 forward(0.0f, 0.0f, -1.0f);

    if(std::abs(glm::length(v*forward) - glm::dot(v, forward))
       <= std::numeric_limits<float>::epsilon())
    {
        glm::vec3 a = glm::cross(v, forward);
        glm::quat q;
        q.x = a.x;
        q.y = a.y;
        q.z = a.z;
        q.w = std::sqrt(
                  std::pow(glm::length(v), 2.0f) * std::pow(glm::length(forward), 2.0f)
              ) + glm::dot(v, forward);

        cam->setRotation(glm::normalize(q));
    }

    glm::vec3 up(0.0f, 1.0f, 0.0f);
    v = cam->getUp();
    if(std::abs(glm::length(v*up) - glm::dot(v, up))
       > std::numeric_limits<float>::epsilon())
        return false;

    node->setName(in->mName.C_Str());
    node->setEntity(cam.get());
    m_cameras.push_back(node->getId());
    out.addComponent(cam.release());
    out.addNode(node.release());

    return true;
}

bool FD3D::AbstractSceneLoader::loadMesh(const aiMesh *in, Scene &out)
{
    std::unique_ptr<AbstractMeshComponent> result(createMesh());
    if(!result)
        return false;

    VertexComponentFlag f = internal::getVertexComponents(in);

    result->setComponentsFlags(f);
    result->setNumberOfUvChannel(static_cast<uint8_t>(in->GetNumUVChannels()));
    result->setNumberOfColorChannel(static_cast<uint8_t>(in->GetNumColorChannels()));
    result->setNumberOfVertices(in->mNumVertices);
    result->setNumberOfIndices(in->mNumFaces * 3);
    result->setName(in->mName.C_Str());
    result->setMaterialId(m_materials[in->mMaterialIndex]);

    for(size_t i = 0; i < in->mNumVertices; ++i)
    {
        VertexProxy2 v = (*result)[i];
        {
            glm::vec3 *pos = v.getPosition();
            *pos = internal::getVertexPosition(in, i);
        }

        if(f[VertexComponentType::Normal])
        {
            glm::vec3 *norm = v.getNormal();
            *norm = internal::getVertexNormal(in, i);
        }

        if(f[VertexComponentType::Tangent])
        {
            glm::vec3 *t = v.getTangent();
            *t = internal::getVertexTangent(in, i);
            t = v.getBitangent();
            *t = internal::getVertexBitangent(in, i);
        }

        if(f[VertexComponentType::Texture])
        {
            for(uint8_t j = 0; j < result->getNumberOfUvChannel(); ++j)
            {
                glm::vec2 *tex = v.getUv(j);
                *tex = internal::getVertexUv(in, i, j);
            }
        }

        if(f[VertexComponentType::Color])
        {
            for(uint8_t j = 0; j < result->getNumberOfColorChannel(); ++j)
            {
                glm::vec4 *col = v.getColor(j);
                *col = internal::getVertexColor(in, i, j);
            }
        }
    }

    for(unsigned int i = 0; i < in->mNumFaces; i++)
    {
        size_t pos = i * 3;
        aiFace face = in->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            result->getIndex(pos + j).setValue(face.mIndices[j]);
    }

    m_meshes.push_back(result->getId());
    out.addComponent(result.release());

    return true;
}

FD3D::Scene::node_id_type FD3D::AbstractSceneLoader::loadNode(const aiNode *in, Scene &out, Scene::node_id_type parent)
{
    std::unique_ptr<ObjectNode> result(new ObjectNode());
    std::unique_ptr<Transform> trans(new Transform());

    trans->fromMatrix(in->mTransformation);

    result->setName(in->mName.C_Str());
    result->setParentId(parent);
    FD3D::SceneNodeProxy parentNode = out.getNode(parent);
    if(parentNode)
        parentNode->addChildId(result->getId());

    result->setEntity(trans.get());
    out.addComponent(trans.release());
    out.addNode(result.get());
    for(size_t i = 0; i < in->mNumMeshes; ++i)
        out.bindComponent(result->getId(), m_meshes[in->mMeshes[i]]);


    Scene::node_id_type id = result->getId();
    result.release();

    return id;
}

const aiScene *FD3D::internal2::importScene(Assimp::Importer &importer,
                                           const std::string &path,
                                           unsigned int flags)
{
    const aiScene *scene = importer.ReadFile(path, flags);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    return scene;
}

uint32_t FD3D::SceneLoader::loadTexture(const std::string &path)
{
    return m_textureLoader(path);
}

uint32_t FD3D::SceneLoader::loadEmbeddedTexture(const aiTexture *tex)
{
    return m_embeddedTextureLoader(tex);
}

FD3D::AbstractMeshComponent *FD3D::SceneLoader::createMesh()
{
    if(m_meshAllocator)
        return m_meshAllocator();

    return nullptr;
}

FD3D::AbstractMeshComponent *FD3D::SceneLoader::defaultMeshAllocator()
{
    return new MeshComponent();
}

















bool FD3D::AssetImporter::loadTextures(const aiMaterial *mat, FD3D::TextureType type, FD3D::Material &out)
{
    aiTextureType t = internal::textureTypeToAssimpType(type);
    FD3D::Material::texture_vector v = out[type];
    for(size_t i = 0, imax = mat->GetTextureCount(t); i < imax; ++i)
    {
        aiString path;
        FD3D::AbstractTexture *tex;
        mat->GetTexture(t, static_cast<unsigned int>(i), &path);

        { // Check if the texture is loaded, if it is not load it
            auto it = m_textures.find(path.C_Str());
            if(it == m_textures.end())
            {
                std::unique_ptr<FD3D::AbstractTexture> tmp;
                tmp = m_textureLoader(m_scene, m_directory, path.C_Str());
                if(!tmp)
                    return false;

                tex = tmp.get();
                m_textures[path.C_Str()] = std::move(tmp);
            }
            else
                tex = it->second.get();
        }

        v.push_back(tex);
    }

    return true;
}

bool FD3D::AssetImporter::loadMaterial(const aiMaterial *mat, FD3D::Material &out)
{
    aiColor3D color;
    aiString str;
    float num;
    int i;

    if(mat->Get(AI_MATKEY_NAME, str) == AI_SUCCESS)
        out.setName(str.C_Str());

    if(mat->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
        out.setAmbientColor({color.r, color.g, color.b});

    if(mat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
        out.setDiffuseColor({color.r, color.g, color.b});

    if(mat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
        out.setSpecularColor({color.r, color.g, color.b});

    if(mat->Get(AI_MATKEY_COLOR_EMISSIVE, color) == AI_SUCCESS)
        out.setEmissiveColor({color.r, color.g, color.b});

    if(mat->Get(AI_MATKEY_COLOR_TRANSPARENT, color) == AI_SUCCESS)
        out.setTransparentColor({color.r, color.g, color.b});

    if(mat->Get(AI_MATKEY_SHININESS, num) == AI_SUCCESS)
        out.setShininess(num);

    if(mat->Get(AI_MATKEY_SHININESS_STRENGTH, num) == AI_SUCCESS)
        out.setShininessStrength(num);

    if(mat->Get(AI_MATKEY_OPACITY, num) == AI_SUCCESS)
        out.setOpacity(num);

    if(mat->Get(AI_MATKEY_REFRACTI, num) == AI_SUCCESS)
        out.setRefractionIndex(num);

    if(mat->Get(AI_MATKEY_ENABLE_WIREFRAME, i) == AI_SUCCESS)
        out.setWireframe(i != 0);

    if(mat->Get(AI_MATKEY_TWOSIDED, i) == AI_SUCCESS)
        out.setTwoSided(i != 0);

    aiShadingMode shad;
    if(mat->Get(AI_MATKEY_SHADING_MODEL, shad) == AI_SUCCESS)
        out.setShaddingMode(internal::shadingModeFromAssimpMode(shad));

    aiBlendMode blend;
    if(mat->Get(AI_MATKEY_BLEND_FUNC, blend) == AI_SUCCESS)
        out.setBlendingOptions(internal::blendingFunctionFromAssimpMode(blend));

    return loadTextures(mat, FD3D::TextureType::None, out)
        && loadTextures(mat, FD3D::TextureType::Height, out)
        && loadTextures(mat, FD3D::TextureType::Ambient, out)
        && loadTextures(mat, FD3D::TextureType::Diffuse, out)
        && loadTextures(mat, FD3D::TextureType::Invalid, out)
        && loadTextures(mat, FD3D::TextureType::Normals, out)
        && loadTextures(mat, FD3D::TextureType::Opacity, out)
        && loadTextures(mat, FD3D::TextureType::Emissive, out)
        && loadTextures(mat, FD3D::TextureType::LightMap, out)
        && loadTextures(mat, FD3D::TextureType::Specular, out)
        && loadTextures(mat, FD3D::TextureType::Shininess, out)
        && loadTextures(mat, FD3D::TextureType::Reflection, out)
            && loadTextures(mat, FD3D::TextureType::Displacement, out);
}

bool FD3D::AssetImporter::loadCamera(const aiCamera *cam, FD3D::Camera &out)
{
    out.projection.setFar(cam->mClipPlaneFar);
    out.projection.setNear(cam->mClipPlaneNear);
    out.projection.setFov(cam->mHorizontalFOV);
    out.projection.setHeight(1);
    out.projection.setWidth(cam->mAspect);
    out.projection.setType(FD3D::ProjectionType::Perspective);

    out.setPosition(internal::vec3FromAssimpVec3(cam->mPosition));
    out.setTarget(internal::vec3FromAssimpVec3(cam->mLookAt));

    return true;
}

bool FD3D::AssetImporter::loadLight(const aiLight *light, FD3D::Light &out)
{

    out.setType(internal::lightTypeFromAsimpType(light->mType));
    out.setPosition(internal::vec3FromAssimpVec3(light->mPosition));
    out.setDirection(internal::vec3FromAssimpVec3(light->mDirection));
    out.setUp(internal::vec3FromAssimpVec3(light->mUp));
    out.color.ambient = internal::vec4FromAssimpColor3D(light->mColorAmbient);
    out.color.diffuse = internal::vec4FromAssimpColor3D(light->mColorDiffuse);
    out.color.specular = internal::vec4FromAssimpColor3D(light->mColorSpecular);

    return true;
}

bool FD3D::AssetImporter::loadMesh(const aiMesh *mesh, FD3D::AbstractMesh &out)
{
    VertexComponentFlag f = internal::vertexComponentsFromMesh(mesh);

    out.setComponentsFlags(f);
    out.setNumberOfUvChannel(static_cast<uint8_t>(mesh->GetNumUVChannels()));
    out.setNumberOfColorChannel(static_cast<uint8_t>(mesh->GetNumColorChannels()));
    out.setNumberOfVertices(mesh->mNumVertices);
    out.setNumberOfIndices(mesh->mNumFaces * 3);
    out.setResourceName(mesh->mName.C_Str());

    if(mesh->mMaterialIndex < m_scene->mNumMaterials)
    {
        FD3D::Material *mat = m_materials[mesh->mMaterialIndex].get();
        if(!mat)
        {
            std::cerr << "unable to load material" << std::endl;
            return false;
        }

        out.setMaterial(mat);
    }

    for(size_t i = 0; i < mesh->mNumVertices; ++i)
    {
        VertexProxy v = out.getVertex(i);
        {
            glm::vec3 *pos = v.getPosition();
            *pos = internal::getVertexPosition(mesh, i);
        }

        if(f[VertexComponentType::Normal])
        {
            glm::vec3 *norm = v.getNormal();
            *norm = internal::getVertexNormal(mesh, i);
        }

        if(f[VertexComponentType::Tangent])
        {
            glm::vec3 *t = v.getTangent();
            *t = internal::getVertexTangent(mesh, i);
            t = v.getBitangent();
            *t = internal::getVertexBitangent(mesh, i);
        }

        if(f[VertexComponentType::Texture])
        {
            for(uint8_t j = 0; j < out.getNumberOfUvChannel(); ++j)
            {
                glm::vec2 *tex = v.getUv(j);
                *tex = internal::getVertexUv(mesh, i, j);
            }
        }

        if(f[VertexComponentType::Color])
        {
            for(uint8_t j = 0; j < out.getNumberOfColorChannel(); ++j)
            {
                glm::vec4 *col = v.getColor(j);
                *col = internal::getVertexColor(mesh, i, j);
            }
        }
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        size_t pos = i * 3;
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            out.getIndex(pos + j).setValue(face.mIndices[j]);
    }

    return true;
}

bool FD3D::AssetImporter::loadNode(const aiNode *node, SceneNode *parent, FD3D::ObjectNode &out)
{
    if(!loadTransform(node->mTransformation, *out.getEntity()))
        return false;

    out.setName(node->mName.C_Str());
    if(parent)
    {
        out.setParentId(parent->getId());
        parent->addChildId(out.getId());
    }

    return true;
}

bool FD3D::AssetImporter::loadTransform(const aiMatrix4x4 &mat, FD3D::Transform &trans)
{
    aiVector3D scale;
    aiVector3D position;
    aiQuaternion rotation;

    mat.Decompose(scale, rotation, position);
    trans.setScale({scale.x, scale.y, scale.z});
    trans.setRotation({rotation.w, rotation.x, rotation.y, rotation.z});
    trans.setPosition({position.x, position.y, position.z});

    return true;
}

bool FD3D::AssetImporter::loadNodes()
{
    std::queue<std::pair<SceneNode*, const aiNode *>> todo;
    todo.push(std::make_pair(nullptr, m_scene->mRootNode));
    while(!todo.empty())
    {
        SceneNode *parent = nullptr;
        const aiNode *node = nullptr;
        {
            std::pair<SceneNode*, const aiNode *> current = todo.front();
            parent = current.first;
            node = current.second;
            todo.pop();
        }

        std::unique_ptr<ObjectNode> obj(new ObjectNode());
        std::unique_ptr<Transform> trans(new Transform());
        if(parent)
            obj->setParentId(parent->getId());

        obj->setEntity(trans.get());

        if(!loadNode(node, parent, *obj))
            return false;

        m_nodes.reserve(m_nodes.size() + node->mNumChildren);
        for(size_t i = 0; i < node->mNumChildren; ++i)
            todo.push(std::make_pair(obj.get(), node->mChildren[i]));

        for(size_t i = 0; i < node->mNumMeshes; ++i)
            m_meshBindings.emplace_back(obj->getId(), m_meshComponents[i]->getId());

        m_nodes.emplace_back(obj.release());
        m_transforms.emplace_back(trans.release());
    }

    return true;
}

bool FD3D::AssetImporter::loadCameras()
{
    m_cameras.reserve(m_scene->mNumCameras);
    for(size_t i = 0; i < m_scene->mNumCameras; ++i)
    {
        std::unique_ptr<FD3D::Camera> cam(new FD3D::Camera());
        if(!loadCamera(m_scene->mCameras[i], *cam))
            return false;

        m_cameras.push_back(std::move(cam));
    }

    return true;
}

bool FD3D::AssetImporter::loadMaterials()
{
    m_materials.reserve(m_scene->mNumMaterials);
    for(size_t i = 0; i < m_scene->mNumMaterials; ++i)
    {
        std::unique_ptr<FD3D::Material> mat(new FD3D::Material());
        if(!loadMaterial(m_scene->mMaterials[i], *mat))
            return false;

        m_materials.push_back(std::move(mat));
    }

    return true;
}

bool FD3D::AssetImporter::loadLights()
{
    m_lights.reserve(m_scene->mNumLights);
    for(size_t i = 0; i < m_scene->mNumLights; ++i)
    {
        std::unique_ptr<FD3D::Light> light(new FD3D::Light());
        if(!loadLight(m_scene->mLights[i], *light))
            return false;

        m_lights.push_back(std::move(light));
    }

    return true;
}

bool FD3D::AssetImporter::loadMeshes()
{
    m_meshComponents.reserve(m_scene->mNumMeshes);
    m_meshes.reserve(m_scene->mNumMeshes);
    for(size_t i = 0; i < m_scene->mNumMeshes; ++i)
    {
        std::unique_ptr<FD3D::AbstractMesh> mesh(m_meshAllocator());
        if(!loadMesh(m_scene->mMeshes[i], *mesh))
            return false;

        m_meshComponents.emplace_back(new AssetComponent<AbstractMesh>(mesh.get()));
        m_meshes.push_back(std::move(mesh));
    }

    return true;
}

bool FD3D::AssetImporter::import(std::string_view path, FD3D::SceneManager &mgr, Scene::node_id_type where,
                                 unsigned int flags)
{
    assert(mgr.hasScene() && "SceneManager need to have an instatiated scene");
    assert(mgr.hasResourceManager() && "SceneManager need to have an instatiated  resource manager");

    if(where == 0)
        where = mgr.getScene()->getRootId();

    { // Assimp scene loading
        const aiScene *scene = m_importer.ReadFile(path.data(), flags);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cerr << "Assimp error: " << m_importer.GetErrorString() << std::endl;
            return false;
        }

        if(!loadCameras())
            return false;

        if(!loadLights())
            return false;

        if(!loadMaterials())
            return false;

        if(!loadMeshes())
            return false;

        if(!loadNodes())
            return false;
    }

    { // Add resources
        FDCore::ResourceManager *resMgr = mgr.getResourceManager();
        for(auto it = m_textures.begin(); it != m_textures.end(); ++it)
            resMgr->insert(it->second.release());
        m_textures.clear();

        for(size_t i = 0, imax = m_materials.size(); i < imax; ++i)
            resMgr->insert(m_materials[i].release());
        m_materials.clear();

        for(size_t i = 0, imax = m_meshes.size(); i < imax; ++i)
            resMgr->insert(m_meshes[i].release());
        m_meshes.clear();
    }


    { // Update scenegraph
        FD3D::Scene *scene = mgr.getScene();
        for(size_t i = 0, imax = m_lights.size(); i < imax; ++i)
        {
            std::unique_ptr<FD3D::LightNode> node(new LightNode(m_lights[i].get(), where));
            scene->addComponent(m_lights[i].release());
            scene->addNode(node.release());
        }
        m_lights.clear();

        for(size_t i = 0, imax = m_cameras.size(); i < imax; ++i)
        {
            std::unique_ptr<FD3D::CameraNode> node(new CameraNode(m_cameras[i].get(), where));
            scene->addComponent(m_cameras[i].release());
            scene->addNode(node.release());
        }
        m_cameras.clear();

        for(size_t i = 0, imax = m_transforms.size(); i < imax; ++i)
            scene->addComponent(m_transforms[i].release());
        m_transforms.clear();

        for(size_t i = 0, imax = m_meshComponents.size(); i < imax; ++i)
            scene->addComponent(m_meshComponents[i].release());
        m_meshComponents.clear();

        for(size_t i = 0, imax = m_nodes.size(); i < imax; ++i)
            scene->addNode(m_nodes[i].release());
        m_nodes.clear();

        for(size_t i = 0, imax = m_meshBindings.size(); i < imax; ++i)
            scene->bindComponent(m_meshBindings[i].first, m_meshBindings[i].second);
        m_meshBindings.clear();
    }

    return true;
}

bool FD3D::AssetImporter::isEmbeddedTexture(std::string_view path)
{
    return path[0] == '*';
}

FD3D::LightType FD3D::internal::lightTypeFromAsimpType(aiLightSourceType type)
{
    switch (type)
    {
        case aiLightSource_AREA:
        return LightType::AreaLight;

        case aiLightSource_SPOT:
        return LightType::SpotLight;

        case aiLightSource_POINT:
        return LightType::PointLight;

        case aiLightSource_AMBIENT:
        return LightType::AmbientLight;

        case aiLightSource_DIRECTIONAL:
        return LightType::DirectionalLight;

        case aiLightSource_UNDEFINED:
        default:
        return LightType::Invalid;
    }
}

glm::vec3 FD3D::internal::vec3FromAssimpVec3(aiVector3D v)
{
    return { v.x, v.y, v.z };
}

glm::vec4 FD3D::internal::vec4FromAssimpColor3D(aiColor3D c)
{
    return { c.r, c.g, c.b, 1.0 };
}
