#include "include/FD3D/Utils/TrasformStack.h"

FD3D::TrasformStack::TransformData &FD3D::TrasformStack::getCurrentTransformData()
{
    return m_stack.top().first;
}

const FD3D::TrasformStack::TransformData &FD3D::TrasformStack::getCurrentTransformData() const
{
    return m_stack.top().first;
}

glm::mat4 &FD3D::TrasformStack::getCurrentMatrix()
{
    return m_stack.top().second;
}

const glm::mat4 &FD3D::TrasformStack::getCurrentMatrix() const
{
    return m_stack.top().second;
}

FD3D::TrasformStack &FD3D::TrasformStack::operator<<(const FD3D::Transform &trans)
{
    push(trans);
    return *this;
}

FD3D::TrasformStack &FD3D::TrasformStack::operator>>(FD3D::Transform &trans)
{
    trans = std::move(m_stack.top().first.toTransform());
    pop();
    return *this;
}

const std::pair<FD3D::TrasformStack::TransformData, glm::mat4> &FD3D::TrasformStack::top() const
{
    return m_stack.top();
}

std::pair<FD3D::TrasformStack::TransformData, glm::mat4> &FD3D::TrasformStack::top()
{
    return m_stack.top();
}

void FD3D::TrasformStack::pop()
{
    m_stack.pop();
}

void FD3D::TrasformStack::push(const FD3D::Transform &trans)
{
    if(!m_stack.empty())
        m_stack.push(std::make_pair(TransformData(trans),
                                    getCurrentMatrix() * trans.getMatrix()));
    else
        m_stack.push(std::make_pair(TransformData(trans), trans.getMatrix()));
}

bool FD3D::TrasformStack::empty() const
{
    return m_stack.empty();
}

size_t FD3D::TrasformStack::size() const
{
    return m_stack.size();
}

FD3D::TrasformStack::TransformData::TransformData():
    position(0.0f),
    scale(1.0f),
    rotation(1.0f, 0.0f, 0.0f, 0.0f)
{}

FD3D::TrasformStack::TransformData::TransformData(const FD3D::Transform &transform):
    position(transform.getPosition()),
    scale(transform.getScale()),
    rotation(transform.getRotation())
{}

FD3D::Transform FD3D::TrasformStack::TransformData::toTransform()
{
    return FD3D::Transform(position, scale, rotation);
}
