#pragma once

#include <variant>
#include <vector>
#include "Keys.hpp"

namespace ee::input
{
    enum class TriggerState { Down, Held, Released };
    
    using Input = std::variant<Key, MouseButton, GamepadButton>;

    struct KeyBinding{
        std::vector<std::pair<Input, TriggerState>> inputs;
    };

}

    



