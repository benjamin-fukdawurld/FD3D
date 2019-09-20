#include <FD3D/Projection.h>

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

FD3D::Projection::Projection() :
    m_left(0.0f),
    m_right(0.0f),
    m_bottom(0.0f),
    m_top(0.0f),
    m_fov(0.0f),
    m_near(0.0f),
    m_far(0.0f),
    m_type(FD3D::ProjectionType::Perspective),
    m_isUpToDate(false)
{

}

const float *FD3D::Projection::getPtr() const
{
    return glm::value_ptr(getMatrix());
}

const glm::mat4x4 &FD3D::Projection::getMatrix() const
{
    if(!m_isUpToDate)
        generateMatrix();

    return m_mat;
}

float FD3D::Projection::getFov() const
{
    return m_fov;
}

void FD3D::Projection::setFov(float fov)
{
    m_isUpToDate = false;
    m_fov = fov;
}

void FD3D::Projection::invalidate()
{
    m_isUpToDate = false;
}

void FD3D::Projection::generateMatrix() const
{
    switch(m_type)
    {
        case FD3D::ProjectionType::Orthographic:
        m_mat = glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far);
        break;

        case FD3D::ProjectionType::Perspective:
        m_mat = glm::perspective(m_fov, (m_right - m_left) / (m_top - m_bottom), m_near, m_far);
        break;

        case FD3D::ProjectionType::Frustum:
        m_mat = glm::frustum(m_left, m_right, m_bottom, m_top, m_near, m_far);
        break;
    }

    m_isUpToDate = true;
}

float FD3D::Projection::getLeft() const
{
    return m_left;
}

void FD3D::Projection::setLeft(float left)
{
    m_isUpToDate = false;
    m_left = left;
}

float FD3D::Projection::getRight() const
{
    return m_right;
}

void FD3D::Projection::setRight(float right)
{
    m_isUpToDate = false;
    m_right = right;
}

float FD3D::Projection::getWidth() const
{
    return m_right - m_left;
}

void FD3D::Projection::setWidth(float w)
{
    m_isUpToDate = false;
    m_right = w;
    m_left = 0;
}

float FD3D::Projection::getBottom() const
{
    return m_bottom;
}

void FD3D::Projection::setBottom(float bottom)
{
    m_isUpToDate = false;
    m_bottom = bottom;
}

float FD3D::Projection::getTop() const
{
    return m_top;
}

void FD3D::Projection::setTop(float top)
{
    m_isUpToDate = false;
    m_top = top;
}

float FD3D::Projection::getHeight() const
{
    return m_top - m_bottom;
}

void FD3D::Projection::setHeight(float h)
{
    m_isUpToDate = false;
    m_top = h;
    m_bottom = 0;
}

float FD3D::Projection::getNear() const
{
    return m_near;
}

void FD3D::Projection::setNear(float near)
{
    m_isUpToDate = false;
    m_near = near;
}

float FD3D::Projection::getFar() const
{
    return m_far;
}

void FD3D::Projection::setFar(float far)
{
    m_isUpToDate = false;
    m_far = far;
}

FD3D::ProjectionType FD3D::Projection::getType() const
{
    return m_type;
}

void FD3D::Projection::setType(const FD3D::ProjectionType &type)
{
    m_isUpToDate = false;
    m_type = type;
}
