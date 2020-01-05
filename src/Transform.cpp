#include <FD3D/Utils/Transform.h>

#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/euler_angles.hpp>

#include <glm/gtc/type_ptr.hpp>

FD3D::Transform::Transform() :
    m_mat(1.0f),
    m_position(0.0f),
    m_scale(1.0f),
    m_isUpToDate(false)
{}

FD3D::Transform::~Transform()
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
    invalidate();
    return m_position;
}


void FD3D::Transform::generateMatrix() const
{
    m_mat = glm::translate(glm::scale(glm::mat4(1.0f), m_scale), m_position) * glm::mat4_cast(m_rotation);
    m_isUpToDate = true;
}

const glm::vec3 &FD3D::Transform::getPosition() const
{
    invalidate();
    return m_position;
}

void FD3D::Transform::setPosition(const glm::vec3 &translation)
{
    invalidate();
    m_position = translation;
}

void FD3D::Transform::translate(const glm::vec3 &translation)
{
    invalidate();
    m_position += translation;
}

glm::vec3 &FD3D::Transform::getScale()
{
    invalidate();
    return m_scale;
}

const glm::vec3 &FD3D::Transform::getScale() const
{
    invalidate();
    return m_scale;
}

void FD3D::Transform::setScale(const glm::vec3 &scale)
{
    invalidate();
    m_scale = scale;
}

void FD3D::Transform::setScaleFactor(float scaleFactor)
{
    invalidate();
    m_scale = glm::vec3(scaleFactor, scaleFactor, scaleFactor);
}

void FD3D::Transform::scale(float factor)
{
    invalidate();
    m_scale *= factor;
}

void FD3D::Transform::scale(const glm::vec3 &scale)
{
    invalidate();
    m_scale *= scale;
}

glm::vec3 FD3D::Transform::getEulerAngles() const
{
    return glm::eulerAngles(m_rotation) * glm::pi<float>() / 180.0f;
}

glm::quat &FD3D::Transform::getRotation()
{
    invalidate();
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
    invalidate();
    m_rotation = q;
}

void FD3D::Transform::rotate(const glm::vec3 &eulerAngles)
{
    rotate(glm::quat(eulerAngles));
}

void FD3D::Transform::rotate(const glm::quat &q)
{
    invalidate();
    m_rotation *= q;
}

glm::vec3 FD3D::Transform::getForward() const
{
    return glm::normalize(m_rotation * glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3 FD3D::Transform::getBackward() const
{
    return -getForward();
}

glm::vec3 FD3D::Transform::getRight() const
{
    return glm::normalize(m_rotation * glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 FD3D::Transform::getLeft() const
{
    return -getRight();
}

glm::vec3 FD3D::Transform::getUp() const
{
    return glm::normalize(m_rotation * glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 FD3D::Transform::getDown() const
{
    return -getUp();
}

void FD3D::Transform::invalidate() const
{
    m_isUpToDate = false;
}
