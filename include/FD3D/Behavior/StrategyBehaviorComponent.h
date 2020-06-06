#ifndef FD3D_STRATEGYBEHAVIORCOMPONENT_H
#define FD3D_STRATEGYBEHAVIORCOMPONENT_H

#include <FD3D/Behavior/BehaviorComponent.h>

#include <functional>

namespace FD3D
{
    class FD_EXPORT StrategyBehaviorComponent final : public BehaviorComponent
    {
        protected:
            std::function<void(StrategyBehaviorComponent*)> m_initStrategy;
            std::function<void(StrategyBehaviorComponent*)> m_quitStrategy;
            std::function<void(StrategyBehaviorComponent*)> m_updateStrategy;
            std::function<void(StrategyBehaviorComponent*)> m_onDisableStrategy;
            std::function<void(StrategyBehaviorComponent*)> m_onEnableStrategy;

        public:
            using BehaviorComponent::BehaviorComponent;

            ~StrategyBehaviorComponent() override = default;

            void init() override;

            void quit() override;

            void update() override;

            void onDisable() override;

            void onEnable() override;

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;

            std::function<void(StrategyBehaviorComponent*)> getInitStrategy() const
            {
                return m_initStrategy;
            }

            template<typename Strategy, typename ...Args>
            void setInitStrategy(Strategy strategy)
            {
                m_initStrategy = strategy;
            }

            template<typename Strategy, typename ...Args>
            void setInitStrategy(Strategy strategy, Args ...args)
            {
                m_initStrategy = std::bind(strategy, args..., std::placeholders::_1);
            }

            std::function<void(StrategyBehaviorComponent*)> getQuitStrategy() const
            {
                return m_quitStrategy;
            }

            template<typename Strategy, typename ...Args>
            void setQuitStrategy(Strategy strategy)
            {
                m_quitStrategy = strategy;
            }

            template<typename Strategy, typename ...Args>
            void setQuitStrategy(Strategy strategy, Args ...args)
            {
                m_quitStrategy = std::bind(strategy, args..., std::placeholders::_1);
            }

            std::function<void(StrategyBehaviorComponent*)> getUpdateStrategy() const
            {
                return m_updateStrategy;
            }

            template<typename Strategy, typename ...Args>
            void setUpdateStrategy(Strategy strategy)
            {
                m_updateStrategy = strategy;
            }

            template<typename Strategy, typename ...Args>
            void setUpdateStrategy(Strategy strategy, Args ...args)
            {
                m_updateStrategy = std::bind(strategy, args..., std::placeholders::_1);
            }

            std::function<void(StrategyBehaviorComponent*)> getOnDisableStrategy() const
            {
                return m_onDisableStrategy;
            }

            template<typename Strategy, typename ...Args>
            void setOnDisableStrategy(Strategy strategy)
            {
                m_onDisableStrategy = strategy;
            }

            template<typename Strategy, typename ...Args>
            void setOnDisableStrategy(Strategy strategy, Args ...args)
            {
                m_onDisableStrategy = std::bind(strategy, args..., std::placeholders::_1);
            }

            std::function<void(StrategyBehaviorComponent*)> getOnEnableStrategy() const
            {
                return m_onEnableStrategy;
            }

            template<typename Strategy, typename ...Args>
            void setOnEnableStrategy(Strategy strategy)
            {
                m_onEnableStrategy = strategy;
            }

            template<typename Strategy, typename ...Args>
            void setOnEnableStrategy(Strategy strategy, Args ...args)
            {
                m_onEnableStrategy = std::bind(strategy, args..., std::placeholders::_1);
            }
    };
}

generateTypeCode(FD3D::StrategyBehaviorComponent);

#endif // FD3D_STRATEGYBEHAVIORCOMPONENT_H
