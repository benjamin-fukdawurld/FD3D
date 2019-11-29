#include <FD3D/Camera.h>

#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/euler_angles.hpp>

#include <glm/gtc/type_ptr.hpp>

FD3D::Camera::Camera() :
    m_mat(1.0f),
    m_position(0.0f, 0.0f, 0.0f),
    m_rotation(1.0f, 0.0f, 0.0f, 0.0f),
    m_isUpToDate(false)
{}

const float *FD3D::Camera::getPtr() const
{
    return glm::value_ptr(getMatrix());
}

const glm::mat4x4 &FD3D::Camera::getMatrix() const
{
    if(!m_isUpToDate)
        generateMatrix();

    return m_mat;
}

glm::vec3 &FD3D::Camera::getPosition()
{
    return m_position;
}

const glm::vec3 &FD3D::Camera::getPosition() const
{
    return m_position;
}

void FD3D::Camera::setPosition(const glm::vec3 &position)
{
    m_isUpToDate = false;
    m_position = position;
}

void FD3D::Camera::translate(const glm::vec3 &v)
{
    m_position += v;
}

glm::vec3 FD3D::Camera::getEulerAngles() const
{
    return glm::eulerAngles(m_rotation) / glm::pi<float>() * 180.0f;
}

glm::quat &FD3D::Camera::getRotation()
{
    m_isUpToDate = false;
    return m_rotation;
}

const glm::quat &FD3D::Camera::getRotation() const
{
    return m_rotation;
}

void FD3D::Camera::setRotation(const glm::vec3 &eulerAngles)
{
    setRotation(glm::quat(eulerAngles));
}

void FD3D::Camera::setRotation(const glm::quat &q)
{
    m_isUpToDate = false;
    m_rotation = q;
}

void FD3D::Camera::rotate(const glm::vec3 &eulerAngles)
{
    rotate(glm::quat(eulerAngles));
}

void FD3D::Camera::rotate(const glm::quat &q)
{
    m_isUpToDate = false;
    m_rotation *= q;
}

glm::vec3 FD3D::Camera::getUpVector() const
{
    glm::vec4 v(0.0f, 1.0f, 0.0f, 0.0f);
    v = glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z) * v;
    return glm::vec3(v.x, v.y, v.z);
}

glm::vec3 FD3D::Camera::getTarget() const
{
    glm::vec4 v(0.0f, 0.0f, -1.0f, 0.0f);
    v = glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z) * v;
    v += glm::vec4(m_position, 0.0f);
    return glm::vec3(v.x, v.y, v.z);
}

void FD3D::Camera::generateMatrix() const
{
    m_mat = glm::lookAt(m_position, getTarget(), getUpVector());
    m_isUpToDate = true;
}


