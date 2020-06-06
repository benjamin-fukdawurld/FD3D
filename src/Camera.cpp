#include <FD3D/Camera/Camera.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

void FD3D::Camera::setTarget(const glm::vec3 &target)
{
    glm::vec3 v = target - m_position;
    glm::vec3 forward(0.0f, 0.0f, -1.0f);
    setRotation(glm::rotation(forward, v));
}

void FD3D::Camera::update() const
{
    m_mat = generateLookAtMatrix(getPosition(), getTarget(), getUp());
    m_isUpToDate = true;
}

const char *FD3D::Camera::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::Camera>::code;
}

size_t FD3D::Camera::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::Camera>::hash();
}

bool FD3D::Camera::matchTypeCodeHash(size_t hash) const
{
    return hash == FD3D::Camera::getTypeCodeHash() || FD3D::Component::matchTypeCodeHash(hash);
}

glm::mat4 FD3D::Camera::generateLookAtMatrix(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up)
{
    return glm::lookAt(position, target, up);
}

bool FD3D::Camera::fromCamera(const aiCamera *cam)
{
    projection.setFar(cam->mClipPlaneFar);
    projection.setNear(cam->mClipPlaneNear);
    projection.setFov(cam->mHorizontalFOV);
    projection.setHeight(1);
    projection.setWidth(cam->mAspect);
    projection.setType(FD3D::ProjectionType::Perspective);

    setPosition({
        cam->mLookAt.x,
        cam->mLookAt.y,
        cam->mLookAt.z
    });

    glm::vec3 v = {
        cam->mLookAt.x,
        cam->mLookAt.y,
        cam->mLookAt.z
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

        setRotation(glm::normalize(q));
    }

    glm::vec3 up(0.0f, 1.0f, 0.0f);
    v = getUp();
    if(std::abs(glm::length(v*up) - glm::dot(v, up))
       > std::numeric_limits<float>::epsilon())
        return false;

    return true;
}
