//#include <FD3D/Mesh/ModelLoader.h>

//#include <iostream>


//static aiTextureType toAssimpType(FD3D::TextureType type)
//{
//    switch (type)
//    {
//        case FD3D::TextureType::None:
//            return aiTextureType_NONE;

//        case FD3D::TextureType::Height:
//            return aiTextureType_HEIGHT;

//        case FD3D::TextureType::Ambient:
//            return aiTextureType_AMBIENT;

//        case FD3D::TextureType::Diffuse:
//            return aiTextureType_DIFFUSE;

//        case FD3D::TextureType::Normals:
//            return aiTextureType_NORMALS;

//        case FD3D::TextureType::Opacity:
//            return aiTextureType_OPACITY;

//        case FD3D::TextureType::Emissive:
//            return aiTextureType_EMISSIVE;

//        case FD3D::TextureType::LightMap:
//            return aiTextureType_LIGHTMAP;

//        case FD3D::TextureType::Specular:
//            return aiTextureType_SPECULAR;

//        case FD3D::TextureType::Shininess:
//            return aiTextureType_SHININESS;

//        case FD3D::TextureType::Reflection:
//            return aiTextureType_REFLECTION;

//        case FD3D::TextureType::Displacement:
//            return aiTextureType_DISPLACEMENT;

//        case FD3D::TextureType::Invalid:
//            return aiTextureType_UNKNOWN;
//    }

//    return aiTextureType_UNKNOWN;
//}


//FD3D::Material FD3D::DefaultMaterialGenerator::operator()(const aiMaterial *mat)
//{
//    FD3D::Material result;
//    auto textureLoop = [this, mat, &result](TextureType type)
//    {
//        aiTextureType t = toAssimpType(type);
//        for(size_t i = 0, imax = mat->GetTextureCount(t); i < imax; ++i)
//        {
//            aiString path;
//            mat->GetTexture(t, static_cast<unsigned int>(i), &path);
//            Texture tex = this->loadTexture(type, path.C_Str());
//            result.getTextures(type).push_back(tex.getTextureId());
//        }
//    };

//    textureLoop(FD3D::TextureType::None);
//    textureLoop(FD3D::TextureType::Height);
//    textureLoop(FD3D::TextureType::Ambient);
//    textureLoop(FD3D::TextureType::Diffuse);
//    textureLoop(FD3D::TextureType::Invalid);
//    textureLoop(FD3D::TextureType::Normals);
//    textureLoop(FD3D::TextureType::Opacity);
//    textureLoop(FD3D::TextureType::Emissive);
//    textureLoop(FD3D::TextureType::LightMap);
//    textureLoop(FD3D::TextureType::Specular);
//    textureLoop(FD3D::TextureType::Shininess);
//    textureLoop(FD3D::TextureType::Reflection);
//    textureLoop(FD3D::TextureType::Displacement);

//    aiColor3D color;
//    aiString name;
//    float shininess;

//    if(mat->Get(AI_MATKEY_NAME, name) == AI_SUCCESS)
//        result.setName(name.C_Str());

//    if(mat->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
//        result.setShininess(shininess);

//    if(mat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
//        result.setDiffuseColor({color.r, color.g, color.b});

//    if(mat->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
//        result.setAmbientColor({color.r, color.g, color.b});

//    if(mat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
//        result.setSpecularColor({color.r, color.g, color.b});

//    return result;
//}

//const aiScene *FD3D::internal::importScene(Assimp::Importer &importer, const std::string &path, unsigned int flags)
//{
//    const aiScene *scene = importer.ReadFile(path, flags);
//    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//    {
//        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
//        return nullptr;
//    }

//    return scene;
//}

//std::vector<uint32_t> FD3D::internal::getMeshIndices(const aiMesh *mesh)
//{
//    std::vector<uint32_t> indices;
//    indices.reserve(mesh->mNumFaces * 3);

//    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
//    {
//        aiFace face = mesh->mFaces[i];
//        for(unsigned int j = 0; j < face.mNumIndices; j++)
//            indices.push_back(face.mIndices[j]);
//    }

//    return indices;
//}

//glm::vec3 FD3D::internal::getVertexPosition(const aiMesh *mesh, size_t vertexIndex)
//{
//    auto &v = mesh->mVertices[vertexIndex];
//    return glm::vec3(v.x, v.y, v.z);
//}

//glm::vec3 FD3D::internal::getVertexNormal(const aiMesh *mesh, size_t vertexIndex)
//{
//    auto &n = mesh->mNormals[vertexIndex];
//    return glm::vec3(n.x, n.y, n.z);
//}

//glm::vec2 FD3D::internal::getVertexTextureCoordinates(const aiMesh *mesh, size_t vertexIndex, size_t textureIndex)
//{
//    auto &t = mesh->mTextureCoords[textureIndex][vertexIndex];
//    return glm::vec2(t.x, t.y);
//}

//template<>
//FD3D::Vertex FD3D::generateVertex<FD3D::Vertex>(const aiMesh *mesh, size_t vertexIndex)
//{
//    Vertex v;
//    v.setPosition(internal::getVertexPosition(mesh, vertexIndex));
//    v.setNormal(internal::getVertexNormal(mesh, vertexIndex));
//    v.setTexture(internal::getVertexTextureCoordinates(mesh, vertexIndex, 0));
//    return v;
//}

//template<>
//FD3D::Mesh<FD3D::Vertex> FD3D::generateMesh<FD3D::Mesh<FD3D::Vertex>>(const aiMesh *mesh)
//{
//    std::vector<Vertex> v;
//    std::vector<Material*> t;
//    v.reserve(mesh->mNumVertices);
//    for(size_t i = 0; i < mesh->mNumVertices; ++i)
//    {
//        v.push_back(generateVertex<Vertex>(mesh, i));
//    }

//    return Mesh{v, internal::getMeshIndices(mesh), t};
//}

//template<>
//FD3D::Mesh<FD3D::Vertex> FD3D::generateMesh<
//    FD3D::Mesh<FD3D::Vertex>,
//    std::function<FD3D::Vertex(const aiMesh*, size_t)>
//>(const aiMesh *mesh, std::function<Vertex(const aiMesh*, size_t)> vertexGenerator)
//{
//    std::vector<Vertex> v;
//    std::vector<Material*> t;
//    v.reserve(mesh->mNumVertices);
//    for(size_t i = 0; i < mesh->mNumVertices; ++i)
//    {
//        v.push_back(vertexGenerator(mesh, i));
//    }

//    return Mesh{v, internal::getMeshIndices(mesh), t};
//}

//template<>
//FD3D::Model<FD3D::Mesh<FD3D::Vertex>> FD3D::generateModel<
//    FD3D::Model<FD3D::Mesh<FD3D::Vertex>>,
//    FD3D::MeshGeneratorFunction<FD3D::Mesh<FD3D::Vertex>>,
//    FD3D::VertexGeneratorFunction<FD3D::Vertex>
//>(const aiScene *scene, const aiNode *node, const std::string &directory,
//  MeshGeneratorFunction<Mesh<Vertex>> meshGenerator,
//  VertexGeneratorFunction<Vertex> vertexGenerator)
//{
//    Model<Mesh<Vertex>> model(node->mName.C_Str());
//    model.setDirectory(directory);
//    model.reserveMeshes(node->mNumMeshes);
//    for(size_t i = 0; i < node->mNumMeshes; i++)
//    {
//        model.addMesh(
//                    meshGenerator(
//                        scene->mMeshes[node->mMeshes[i]],
//                        vertexGenerator
//                    )
//                );
//    }

//    aiVector3t<float> scale;
//    aiVector3t<float> position;
//    aiQuaterniont<float> rotation;
//    node->mTransformation.Decompose(scale, rotation, position);
//    Transform &t = model.getTransform();
//    t.setScale(glm::vec3(scale.x, scale.y, scale.z));
//    t.setRotation(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
//    t.setPosition(glm::vec3(position.x, position.y, position.z));

//    return model;
//}

//template<>
//FD3D::Model<FD3D::Mesh<FD3D::Vertex>> FD3D::loadModel<
//    FD3D::Model<FD3D::Mesh<FD3D::Vertex>>,
//    FD3D::MeshGeneratorFunction<FD3D::Mesh<FD3D::Vertex>>,
//    FD3D::VertexGeneratorFunction<FD3D::Vertex>
//>(const aiScene *scene, const std::string &directory,
//  MeshGeneratorFunction<Mesh<Vertex>> meshGenerator,
//  VertexGeneratorFunction<Vertex> vertexGenerator)
//{
//    typedef FD3D::Model<FD3D::Mesh<FD3D::Vertex>> ModelType;

//    ModelType result;
//    std::queue<std::pair<ModelType*, const aiNode*>> todo;
//    todo.push(std::make_pair(nullptr, scene->mRootNode));

//    while(!todo.empty())
//    {
//        std::pair<ModelType*, const aiNode*> p = todo.front();
//        todo.pop();

//        ModelType *parent = p.first;
//        const aiNode *current = p.second;
//        std::cout << current->mName.C_Str() << std::endl;
//        if(current->mMetaData) {
//            for (int i = 0; i < current->mMetaData->mNumProperties; ++i) {
//                std::cout << "\t" << current->mMetaData->mKeys[i].C_Str() << ": ";
//                auto v = current->mMetaData->mValues[i];
//                switch(v.mType)
//                {
//                    case AI_BOOL:
//                    {
//                        bool b;
//                        current->mMetaData->Get(current->mMetaData->mKeys[i], b);
//                        std::cout << std::boolalpha << b << std::endl;
//                    }
//                    break;

//                    case AI_INT32:
//                    {
//                        int32_t j;
//                        current->mMetaData->Get(current->mMetaData->mKeys[i], j);
//                        std::cout<< j << std::endl;
//                    }
//                    break;

//                    case AI_UINT64:
//                    {
//                        uint64_t j;
//                        current->mMetaData->Get(current->mMetaData->mKeys[i], j);
//                        std::cout<< j << std::endl;
//                    }
//                    break;

//                    case AI_FLOAT:
//                    {
//                        float j;
//                        current->mMetaData->Get(current->mMetaData->mKeys[i], j);
//                        std::cout<< j << std::endl;
//                    }
//                    break;

//                    case AI_DOUBLE:
//                    {
//                        double j;
//                        current->mMetaData->Get(current->mMetaData->mKeys[i], j);
//                        std::cout<< j << std::endl;
//                    }
//                    break;

//                    case AI_AISTRING:
//                    {
//                        aiString j;
//                        current->mMetaData->Get(current->mMetaData->mKeys[i], j);
//                        std::cout<< j.C_Str() << std::endl;
//                    }
//                    break;

//                    case AI_AIVECTOR3D:
//                    {
//                        aiVector3D j;
//                        current->mMetaData->Get(current->mMetaData->mKeys[i], j);
//                        std::cout << "{ " << j.x << ", " << j.y << ", " << j.z << " }" << std::endl;
//                    }
//                    break;

//                    default:
//                        std::cout << "unsupported type" << std::endl;
//                    break;
//                }
//            }
//        }
//        std::cout << "\n\n\n\n\n\n";

//        ModelType *model = nullptr;

//        if(!parent)
//            model = &result;
//        else
//        {
//            parent->addChild({});
//            model = &(parent->getChild(parent->getChildCount() - 1));
//        }

//        *model = generateModel<ModelType,
//                FD3D::MeshGeneratorFunction<FD3D::Mesh<FD3D::Vertex>>,
//                FD3D::VertexGeneratorFunction<FD3D::Vertex>
//                >(scene, current, directory, meshGenerator, vertexGenerator);
//        model->setParent(parent);

//        for(unsigned int i = 0; i < current->mNumChildren; i++)
//            todo.push(std::make_pair(model, current->mChildren[i]));
//    }

//    return result;
//}
