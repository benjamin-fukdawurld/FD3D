#include <FD3D/Behavior/StrategyBehavior.h>

void FD3D::StrategyBehavior::init()
{
    if(m_initStrategy)
        return m_initStrategy(this);
}

void FD3D::StrategyBehavior::quit()
{
    if(m_quitStrategy)
        m_quitStrategy(this);
}

void FD3D::StrategyBehavior::update()
{
    if(m_updateStrategy)
        m_updateStrategy(this);
}

void FD3D::StrategyBehavior::onDisable()
{
    if(m_onDisableStrategy)
        m_onDisableStrategy(this);
}

void FD3D::StrategyBehavior::onEnable()
{
    if(m_onEnableStrategy)
        m_onEnableStrategy(this);
}


const char *FD3D::StrategyBehavior::getTypeCode() const
{
    return FDCore::TypeCodeHelper<StrategyBehavior>::code;
}

size_t FD3D::StrategyBehavior::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<StrategyBehavior>::hash();
}

bool FD3D::StrategyBehavior::matchTypeCodeHash(size_t hash) const
{
    return hash == StrategyBehavior::getTypeCodeHash() || Behavior::matchTypeCodeHash(hash);
}
