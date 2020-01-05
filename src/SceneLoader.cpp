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


FD3D::AbstractSceneLoader::AbstractSceneLoader() {}

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

    m_directory = path.substr(0, path.find_last_of('/'));

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
    std::queue<std::pair<Scene::id_type, const aiNode *>> todo;
    todo.push(std::make_pair(out.getRootId(), m_scene->mRootNode));
    while(!todo.empty())
    {
        Scene::id_type parent = 0;
        const aiNode *node = nullptr;
        {
            std::pair<Scene::id_type, const aiNode *> current = todo.front();
            parent = current.first;
            node = current.second;
            todo.pop();
        }

        Scene::id_type id = loadNode(node, out, parent);
        for(size_t i = 0; i < node->mNumChildren; ++i)
            todo.push(std::make_pair(id, node->mChildren[i]));
    }

    return true;
}

bool FD3D::AbstractSceneLoader::loadMaterial(const aiMaterial *in, Scene &out)
{
    std::unique_ptr<Material> result(new Material());
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
    Light &result = node->getEntity();
    switch (in->mType)
    {
        case aiLightSource_AREA:
            result.setType(LightType::AreaLight);
        break;

        case aiLightSource_SPOT:
            result.setType(LightType::SpotLight);
        break;

        case aiLightSource_POINT:
            result.setType(LightType::PointLight);
        break;

        case aiLightSource_AMBIENT:
            result.setType(LightType::AmbientLight);
        break;

        case aiLightSource_DIRECTIONAL:
            result.setType(LightType::DirectionalLight);
        break;

        case aiLightSource_UNDEFINED:
        default:
            result.setType(LightType::Undefined);
        break;
    }

    node->setName(in->mName.C_Str());
    result.setPosition(
        {
            in->mPosition.x,
            in->mPosition.y,
            in->mPosition.z
        }
    );

    result.setDirection(
        {
            in->mDirection.x,
            in->mDirection.y,
            in->mDirection.z
        }
    );

    result.setUp(
        {
            in->mUp.x,
            in->mUp.y,
            in->mUp.z
        }
    );

    result.color.ambient = {
        in->mColorAmbient.r,
        in->mColorAmbient.g,
        in->mColorAmbient.b,
        1.0f
    };

    result.color.diffuse = {
        in->mColorDiffuse.r,
        in->mColorDiffuse.g,
        in->mColorDiffuse.b,
        1.0f
    };

    result.color.specular = {
        in->mColorSpecular.r,
        in->mColorSpecular.g,
        in->mColorSpecular.b,
        1.0f
    };

    m_lights.push_back(node->getId());
    out.addNode(node.release());

    return true;
}

bool FD3D::AbstractSceneLoader::loadCamera(const aiCamera *in, Scene &out)
{
    std::unique_ptr<CameraNode> node(new CameraNode());
    Camera &result = node->getEntity();
    result.projection.setFar(in->mClipPlaneFar);
    result.projection.setNear(in->mClipPlaneNear);
    result.projection.setFov(in->mHorizontalFOV);
    result.projection.setHeight(1);
    result.projection.setWidth(in->mAspect);
    result.projection.setType(FD3D::ProjectionType::Perspective);

    result.setPosition({
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

        result.setRotation(glm::normalize(q));
    }

    glm::vec3 up(0.0f, 1.0f, 0.0f);
    v = result.getUp();
    if(std::abs(glm::length(v*up) - glm::dot(v, up))
       > std::numeric_limits<float>::epsilon())
        return false;

    node->setName(in->mName.C_Str());
    m_cameras.push_back(node->getId());
    out.addNode(node.release());

    return true;
}

bool FD3D::AbstractSceneLoader::loadMesh(const aiMesh *in, Scene &out)
{
    std::unique_ptr<AbstractMesh> result(createMesh());
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
        VertexProxy v = (*result)[i];
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

    m_meshes.push_back(result->getId());
    out.addComponent(result.release());

    return true;
}

FD3D::Scene::id_type FD3D::AbstractSceneLoader::loadNode(const aiNode *in, Scene &out, Scene::id_type parent)
{
    std::unique_ptr<ObjectNode> result(new ObjectNode());
    Transform &t = result->getEntity();

    aiVector3D scale;
    aiVector3D position;
    aiQuaternion rotation;

    in->mTransformation.Decompose(scale, rotation, position);
    t.setScale({scale.x, scale.y, scale.z});
    t.setRotation({rotation.w, rotation.x, rotation.y, rotation.z});
    t.setPosition({position.x, position.y, position.z});

    result->setName(in->mName.C_Str());
    result->setParentId(parent);
    out.addNode(result.get());
    for(size_t i = 0; i < in->mNumMeshes; ++i)
        out.bindComponent(result->getId(), m_meshes[in->mMeshes[i]]);


    Scene::id_type id = result->getId();
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

std::function<uint32_t (const std::string &)> FD3D::SceneLoader::getTextureLoader() { return m_textureLoader; }

void FD3D::SceneLoader::setTextureLoader(std::function<uint32_t (const std::string &)> loader)
{
    m_textureLoader = loader;
}

std::function<uint32_t (const aiTexture *)> FD3D::SceneLoader::getEmbeddedTextureLoader()
{
    return m_embeddedTextureLoader;
}

void FD3D::SceneLoader::setEmbeddedTextureLoader(std::function<uint32_t (const aiTexture *)> loader)
{
    m_embeddedTextureLoader = loader;
}

uint32_t FD3D::SceneLoader::loadTexture(const std::string &path) { return m_textureLoader(path); }

uint32_t FD3D::SceneLoader::loadEmbeddedTexture(const aiTexture *tex)
{
    return m_embeddedTextureLoader(tex);
}

FD3D::AbstractMesh *FD3D::SceneLoader::createMesh() { return new Mesh(); }
