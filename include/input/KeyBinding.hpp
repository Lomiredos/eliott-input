#pragma once

#include <variant>
#include <vector>
#include "SDL3/SDL.h"


namespace ee::input
{
    enum class TriggerState { Down, Held, Released };
    
    using Input = std::variant<SDL_Scancode, int, SDL_GamepadButton>;

    struct KeyBinding{
        std::vector<std::pair<Input, TriggerState>> inputs;
    };

}

    



