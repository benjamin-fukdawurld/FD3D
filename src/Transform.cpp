#include <FD3D/Utils/Transform.h>

#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glm/gtc/type_ptr.hpp>

FD3D::Transform::Transform() :
    m_mat(1.0f),
    m_position(0.0f),
    m_scale(1.0f),
    m_rotation(1.0f, 0.0f, 0.0f, 0.0f),
    m_isUpToDate(false)
{}

FD3D::Transform::Transform(const glm::vec3 &position,
                           const glm::vec3 &scale,
                           const glm::quat &rotation) :
    m_mat(1.0f),
    m_position(position),
    m_scale(scale),
    m_rotation(rotation),
    m_isUpToDate(false)
{}

const float *FD3D::Transform::getMatrixPtr() const
{
    return glm::value_ptr(getMatrix());
}

const glm::mat4x4 &FD3D::Transform::getMatrix() const
{
    if(!m_isUpToDate)
        update();

    return m_mat;
}

glm::vec3 &FD3D::Transform::getPosition()
{
    invalidate();
    return m_position;
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
    return glm::eulerAngles(m_rotation);
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

bool FD3D::Transform::isUptoDate() const
{
    return m_isUpToDate;
}

void FD3D::Transform::update() const
{
    m_mat = generateMatrix(m_position, m_scale, m_rotation);
    m_isUpToDate = true;
}

glm::mat4 FD3D::Transform::generateMatrix(const glm::vec3 &position,
                                          const glm::vec3 &scale,
                                          const glm::quat &rotation)
{
    return glm::translate(glm::scale(glm::mat4(1.0f), scale) * glm::toMat4(rotation), position);
}
