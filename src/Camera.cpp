#include <FD3D/Camera/Camera.h>

#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/euler_angles.hpp>

#include <glm/gtc/type_ptr.hpp>

FD3D::Camera::Camera()
{}

void FD3D::Camera::generateMatrix() const
{
    m_mat = glm::lookAt(m_position, getTarget(), getUp());
    m_isUpToDate = true;
}
