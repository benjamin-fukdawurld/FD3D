#include <FD3D/Camera/Camera.h>

#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/euler_angles.hpp>

#include <glm/gtc/type_ptr.hpp>

FD3D::Camera::Camera()
{}

void FD3D::Camera::update() const
{
    m_mat = generateLookAtMatrix(getPosition(), getTarget(), getUp());
    m_isUpToDate = true;
}

glm::mat4 FD3D::Camera::generateLookAtMatrix(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up)
{
    return glm::lookAt(position, target, up);
}
