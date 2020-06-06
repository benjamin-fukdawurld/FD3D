#include <FD3D/Behavior/StrategyBehaviorComponent.h>

void FD3D::StrategyBehaviorComponent::init()
{
    if(m_initStrategy)
        return m_initStrategy(this);
}

void FD3D::StrategyBehaviorComponent::quit()
{
    if(m_quitStrategy)
        m_quitStrategy(this);
}

void FD3D::StrategyBehaviorComponent::update()
{
    if(m_updateStrategy)
        m_updateStrategy(this);
}

void FD3D::StrategyBehaviorComponent::onDisable()
{
    if(m_onDisableStrategy)
        m_onDisableStrategy(this);
}

void FD3D::StrategyBehaviorComponent::onEnable()
{
    if(m_onEnableStrategy)
        m_onEnableStrategy(this);
}


const char *FD3D::StrategyBehaviorComponent::getTypeCode() const
{
    return FDCore::TypeCodeHelper<StrategyBehaviorComponent>::code;
}

size_t FD3D::StrategyBehaviorComponent::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<StrategyBehaviorComponent>::hash();
}

bool FD3D::StrategyBehaviorComponent::matchTypeCodeHash(size_t hash) const
{
    return hash == StrategyBehaviorComponent::getTypeCodeHash() || BehaviorComponent::matchTypeCodeHash(hash);
}
