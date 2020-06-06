#ifndef STRATEGYBEHAVIOR_H
#define STRATEGYBEHAVIOR_H

#include <FD3D/Behavior/BaseBehavior.h>

#include <functional>

namespace FD3D
{
    class FD_EXPORT StrategyBehavior final : public BaseBehavior
    {
        protected:
            std::function<void(StrategyBehavior*)> m_initStrategy;
            std::function<void(StrategyBehavior*)> m_quitStrategy;
            std::function<void(StrategyBehavior*)> m_updateStrategy;
            std::function<void(StrategyBehavior*)> m_onDisableStrategy;
            std::function<void(StrategyBehavior*)> m_onEnableStrategy;

        public:
            using BaseBehavior::BaseBehavior;

            ~StrategyBehavior() override = default;

            void init() override;

            void quit() override;

            void update() override;

            void onDisable() override;

            void onEnable() override;

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;

            std::function<void(StrategyBehavior*)> getInitStrategy() const
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

            std::function<void(StrategyBehavior*)> getQuitStrategy() const
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

            std::function<void(StrategyBehavior*)> getUpdateStrategy() const
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

            std::function<void(StrategyBehavior*)> getOnDisableStrategy() const
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

            std::function<void(StrategyBehavior*)> getOnEnableStrategy() const
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

generateTypeCode(FD3D::StrategyBehavior);

#endif // STRATEGYBEHAVIOR_H
