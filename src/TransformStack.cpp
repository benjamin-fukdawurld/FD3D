#include "include/FD3D/Utils/TransformStack.h"

FD3D::TransformStack::TransformData &FD3D::TransformStack::getCurrentTransformData()
{
    return m_stack.top().first;
}

const FD3D::TransformStack::TransformData &FD3D::TransformStack::getCurrentTransformData() const
{
    return m_stack.top().first;
}

glm::mat4 &FD3D::TransformStack::getCurrentMatrix()
{
    return m_stack.top().second;
}

const glm::mat4 &FD3D::TransformStack::getCurrentMatrix() const
{
    return m_stack.top().second;
}

FD3D::TransformStack &FD3D::TransformStack::operator<<(const FD3D::Transform &trans)
{
    push(trans);
    return *this;
}

FD3D::TransformStack &FD3D::TransformStack::operator>>(FD3D::Transform &trans)
{
    trans = std::move(m_stack.top().first.toTransform());
    pop();
    return *this;
}

const std::pair<FD3D::TransformStack::TransformData, glm::mat4> &FD3D::TransformStack::top() const
{
    return m_stack.top();
}

std::pair<FD3D::TransformStack::TransformData, glm::mat4> &FD3D::TransformStack::top()
{
    return m_stack.top();
}

void FD3D::TransformStack::pop()
{
    m_stack.pop();
}

void FD3D::TransformStack::push(const FD3D::Transform &trans)
{
    if(!m_stack.empty())
        m_stack.push(std::make_pair(TransformData(trans),
                                    getCurrentMatrix() * trans.getMatrix()));
    else
        m_stack.push(std::make_pair(TransformData(trans), trans.getMatrix()));
}

bool FD3D::TransformStack::empty() const
{
    return m_stack.empty();
}

size_t FD3D::TransformStack::size() const
{
    return m_stack.size();
}

FD3D::TransformStack::TransformData::TransformData():
    position(0.0f),
    scale(1.0f),
    rotation(1.0f, 0.0f, 0.0f, 0.0f)
{}

FD3D::TransformStack::TransformData::TransformData(const FD3D::Transform &transform):
    position(transform.getPosition()),
    scale(transform.getScale()),
    rotation(transform.getRotation())
{}

FD3D::Transform FD3D::TransformStack::TransformData::toTransform()
{
    return FD3D::Transform(position, scale, rotation);
}
