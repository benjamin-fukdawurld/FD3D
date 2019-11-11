#include <FD3D/ModelLoader.h>

#include <iostream>


const aiScene *FD3D::internal::importScene(Assimp::Importer &importer, const std::string &path, unsigned int flags)
{
    const aiScene *scene = importer.ReadFile(path, flags);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    return scene;
}

std::vector<uint32_t> FD3D::internal::getMeshIndices(const aiMesh *mesh)
{
    std::vector<uint32_t> indices;
    indices.reserve(mesh->mNumFaces * 3);

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return indices;
}

glm::vec3 FD3D::internal::getVertexPosition(const aiMesh *mesh, size_t vertexIndex)
{
    auto &v = mesh->mVertices[vertexIndex];
    return glm::vec3(v.x, v.y, v.z);
}

glm::vec3 FD3D::internal::getVertexNormal(const aiMesh *mesh, size_t vertexIndex)
{
    auto &n = mesh->mNormals[vertexIndex];
    return glm::vec3(n.x, n.y, n.z);
}

glm::vec2 FD3D::internal::getVertexTextureCoordinates(const aiMesh *mesh, size_t vertexIndex, size_t textureIndex)
{
    auto &t = mesh->mTextureCoords[textureIndex][vertexIndex];
    return glm::vec2(t.x, t.y);
}

template<>
FD3D::Vertex FD3D::generateVertex<FD3D::Vertex>(const aiMesh *mesh, size_t vertexIndex)
{
    Vertex v;
    v.setPosition(internal::getVertexPosition(mesh, vertexIndex));
    v.setNormal(internal::getVertexNormal(mesh, vertexIndex));
    v.setTexture(internal::getVertexTextureCoordinates(mesh, vertexIndex, 0));
    return v;
}

template<>
FD3D::Mesh<FD3D::Vertex> FD3D::generateMesh<FD3D::Mesh<FD3D::Vertex>>(const aiMesh *mesh)
{
    std::vector<Vertex> v;
    std::vector<Texture> t;
    v.reserve(mesh->mNumVertices);
    for(size_t i = 0; i < mesh->mNumVertices; ++i)
    {
        v.push_back(generateVertex<Vertex>(mesh, i));
    }

    return Mesh{v, internal::getMeshIndices(mesh), t};
}

template<>
FD3D::Mesh<FD3D::Vertex> FD3D::generateMesh<
    FD3D::Mesh<FD3D::Vertex>,
    std::function<FD3D::Vertex(const aiMesh*, size_t)>
>(const aiMesh *mesh, std::function<Vertex(const aiMesh*, size_t)> vertexGenerator)
{
    std::vector<Vertex> v;
    std::vector<Texture> t;
    v.reserve(mesh->mNumVertices);
    for(size_t i = 0; i < mesh->mNumVertices; ++i)
    {
        v.push_back(vertexGenerator(mesh, i));
    }

    return Mesh{v, internal::getMeshIndices(mesh), t};
}

template<>
FD3D::Model<FD3D::Mesh<FD3D::Vertex>> FD3D::generateModel<
    FD3D::Model<FD3D::Mesh<FD3D::Vertex>>,
    FD3D::MeshGeneratorFunction<FD3D::Mesh<FD3D::Vertex>>,
    FD3D::VertexGeneratorFunction<FD3D::Vertex>
>(const aiScene *scene, const aiNode *node, const std::string &directory,
  MeshGeneratorFunction<Mesh<Vertex>> meshGenerator,
  VertexGeneratorFunction<Vertex> vertexGenerator)
{
    Model<Mesh<Vertex>> model(node->mName.C_Str());
    model.setDirectory(directory);
    model.reserveMeshes(node->mNumMeshes);
    for(size_t i = 0; i < node->mNumMeshes; i++)
    {
        model.addMesh(
                    meshGenerator(
                        scene->mMeshes[node->mMeshes[i]],
                        vertexGenerator
                    )
                );
    }

    aiVector3t<float> scale;
    aiVector3t<float> position;
    aiQuaterniont<float> rotation;
    node->mTransformation.Decompose(scale, rotation, position);
    Transform &t = model.getTransform();
    t.setScale(glm::vec3(scale.x, scale.y, scale.z));
    t.setRotation(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
    t.setPosition(glm::vec3(position.x, position.y, position.z));

    return model;
}

template<>
FD3D::Model<FD3D::Mesh<FD3D::Vertex>> FD3D::loadModel<
    FD3D::Model<FD3D::Mesh<FD3D::Vertex>>,
    FD3D::MeshGeneratorFunction<FD3D::Mesh<FD3D::Vertex>>,
    FD3D::VertexGeneratorFunction<FD3D::Vertex>
>(const aiScene *scene, const std::string &directory,
  MeshGeneratorFunction<Mesh<Vertex>> meshGenerator,
  VertexGeneratorFunction<Vertex> vertexGenerator)
{
    typedef FD3D::Model<FD3D::Mesh<FD3D::Vertex>> ModelType;

    ModelType result;
    std::queue<std::pair<ModelType*, const aiNode*>> todo;
    todo.push(std::make_pair(nullptr, scene->mRootNode));

    while(!todo.empty())
    {
        std::pair<ModelType*, const aiNode*> p = todo.front();
        todo.pop();

        ModelType *parent = p.first;
        const aiNode *current = p.second;
        ModelType *model = nullptr;

        if(!parent)
            model = &result;
        else
        {
            parent->addChild({});
            model = &(parent->getChild(parent->getChildCount() - 1));
        }

        *model = generateModel<ModelType,
                FD3D::MeshGeneratorFunction<FD3D::Mesh<FD3D::Vertex>>,
                FD3D::VertexGeneratorFunction<FD3D::Vertex>
                >(scene, current, directory, meshGenerator, vertexGenerator);
        model->setParent(parent);

        for(unsigned int i = 0; i < current->mNumChildren; i++)
            todo.push(std::make_pair(model, current->mChildren[i]));
    }

    return result;
}
