#pragma once

#include "InputManager.hpp"
#include "KeyBinding.hpp"

#include <unordered_map>

namespace ee::input
{

    template <typename T>
    class ActionMap
    {

    private:
        InputManager &m_inputManager = InputManager::getInstance();
        std::unordered_map<T, std::vector<KeyBinding>> m_actions;

    public:

        size_t getSize() {return m_actions.size();}

        void bind(T _action, const std::vector<std::pair<Input, TriggerState>> &_cond)
        {
            KeyBinding kb;
            for (const std::pair<Input, TriggerState> &pair : _cond)
            {
                kb.inputs.push_back(pair);
            }
            m_actions[_action].push_back(kb);
        }

        bool isActive(T _action)
        {
            auto it = m_actions.find(_action);
            if (it == m_actions.end())
                return false;

            if (it->second.empty())
                return false;

            for (auto combo : it->second)
            {
                bool valide = true;

                for (auto key : combo.inputs)
                {
                    if (std::visit([this, &key](auto val)
                                   {
                                       if constexpr (std::is_same_v<decltype(val), SDL_Scancode>){
                                           switch (key.second)
                                           {
                                           case (TriggerState::Down):
                                               return m_inputManager.IsKeyDown(val);
                                           case (TriggerState::Held):
                                               return m_inputManager.IsKeyHeld(val);
                                           case (TriggerState::Released):
                                               return m_inputManager.IsKeyReleased(val);
                                            default:
                                                return false;
                                            }
                                       }
                                       else if constexpr (std::is_same_v<decltype(val), int>)
                                       {
                                           switch (key.second)
                                           {
                                           case (TriggerState::Down):
                                               return m_inputManager.IsMouseDown(val);
                                           case (TriggerState::Held):
                                               return m_inputManager.IsMouseHeld(val);
                                           case (TriggerState::Released):
                                               return m_inputManager.IsMouseReleased(val);
                                            default:
                                                return false;
                                            }
                                       }
                                       else {
                                               switch (key.second)
                                               {
                                               case (TriggerState::Down):
                                                   return m_inputManager.IsKeyDown(val);
                                               case (TriggerState::Held):
                                                   return m_inputManager.IsKeyHeld(val);
                                               case (TriggerState::Released):
                                                   return m_inputManager.IsKeyReleased(val);
                                                default:
                                                    return false;
                                                }
                                           } },
                                   key.first) == false)
                        valide = false;
                }
                if (valide)
                    return true;
            }
            return false;
        }
    };
}
