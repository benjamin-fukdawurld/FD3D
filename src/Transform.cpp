#include <FD3D/Transform.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <glm/gtc/type_ptr.hpp>

FD3D::Transform::Transform() :
    m_mat(1.0f),
    m_position(0.0f),
    m_scale(1.0f),
    m_isUpToDate(false)
{}

const float *FD3D::Transform::getPtr() const
{
    return glm::value_ptr(getMatrix());
}

const glm::mat4x4 &FD3D::Transform::getMatrix() const
{
    if(!m_isUpToDate)
        generateMatrix();

    return m_mat;
}

glm::vec3 &FD3D::Transform::getPosition()
{
    m_isUpToDate = false;
    return m_position;
}


void FD3D::Transform::generateMatrix() const
{
    m_mat = glm::translate(glm::scale(glm::mat4(1.0f), m_scale), m_position) * glm::mat4_cast(m_rotation);
    m_isUpToDate = true;
}

const glm::vec3 &FD3D::Transform::getPosition() const
{
    return m_position;
}

void FD3D::Transform::setPosition(const glm::vec3 &translation)
{
    m_isUpToDate = false;
    m_position = translation;
}

void FD3D::Transform::translate(const glm::vec3 &translation)
{
    m_isUpToDate = false;
    m_position += translation;
}

glm::vec3 &FD3D::Transform::getScale()
{
    m_isUpToDate = false;
    return m_scale;
}

const glm::vec3 &FD3D::Transform::getScale() const
{
    return m_scale;
}

void FD3D::Transform::setScale(const glm::vec3 &scale)
{
    m_isUpToDate = false;
    m_scale = scale;
}

void FD3D::Transform::setScaleFactor(float scaleFactor)
{
    m_isUpToDate = false;
    m_scale = glm::vec3(scaleFactor, scaleFactor, scaleFactor);
}

void FD3D::Transform::scale(float factor)
{
    m_isUpToDate = false;
    m_scale *= factor;
}

void FD3D::Transform::scale(const glm::vec3 &scale)
{
    m_isUpToDate = false;
    m_scale *= scale;
}

glm::vec3 FD3D::Transform::getEulerAngles() const
{
    return glm::eulerAngles(m_rotation) * glm::pi<float>() / 180.0f;
}

glm::quat &FD3D::Transform::getRotation()
{
    m_isUpToDate = false;
    return m_rotation;
}

const glm::quat &FD3D::Transform::getRotation() const
{
    return m_rotation;
}

void FD3D::Transform::setRotation(const glm::vec3 &eulerAngles)
{
    setRotation(glm::quat(eulerAngles));
}

void FD3D::Transform::setRotation(const glm::quat &q)
{
    m_isUpToDate = false;
    m_rotation = q;
}

void FD3D::Transform::rotate(const glm::vec3 &eulerAngles)
{
    rotate(glm::quat(eulerAngles));
}

void FD3D::Transform::rotate(const glm::quat &q)
{
    m_isUpToDate = false;
    m_rotation *= q;
}
