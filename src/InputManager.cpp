#include "input/InputManager.hpp"
#include <SDL3/SDL.h>
#include <optional>


static const SDL_Scancode s_keyTable[] = {
    // Letters
    SDL_SCANCODE_A, SDL_SCANCODE_B, SDL_SCANCODE_C, SDL_SCANCODE_D,
    SDL_SCANCODE_E, SDL_SCANCODE_F, SDL_SCANCODE_G, SDL_SCANCODE_H,
    SDL_SCANCODE_I, SDL_SCANCODE_J, SDL_SCANCODE_K, SDL_SCANCODE_L,
    SDL_SCANCODE_M, SDL_SCANCODE_N, SDL_SCANCODE_O, SDL_SCANCODE_P,
    SDL_SCANCODE_Q, SDL_SCANCODE_R, SDL_SCANCODE_S, SDL_SCANCODE_T,
    SDL_SCANCODE_U, SDL_SCANCODE_V, SDL_SCANCODE_W, SDL_SCANCODE_X,
    SDL_SCANCODE_Y, SDL_SCANCODE_Z,
    // Numbers
    SDL_SCANCODE_0, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3,
    SDL_SCANCODE_4, SDL_SCANCODE_5, SDL_SCANCODE_6, SDL_SCANCODE_7,
    SDL_SCANCODE_8, SDL_SCANCODE_9,
    // Function keys
    SDL_SCANCODE_F1,  SDL_SCANCODE_F2,  SDL_SCANCODE_F3,  SDL_SCANCODE_F4,
    SDL_SCANCODE_F5,  SDL_SCANCODE_F6,  SDL_SCANCODE_F7,  SDL_SCANCODE_F8,
    SDL_SCANCODE_F9,  SDL_SCANCODE_F10, SDL_SCANCODE_F11, SDL_SCANCODE_F12,
    // Navigation
    SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT,
    SDL_SCANCODE_HOME, SDL_SCANCODE_END, SDL_SCANCODE_PAGEUP, SDL_SCANCODE_PAGEDOWN,
    SDL_SCANCODE_INSERT, SDL_SCANCODE_DELETE,
    // Modifiers
    SDL_SCANCODE_LSHIFT, SDL_SCANCODE_RSHIFT,
    SDL_SCANCODE_LCTRL,  SDL_SCANCODE_RCTRL,
    SDL_SCANCODE_LALT,   SDL_SCANCODE_RALT,
    SDL_SCANCODE_LGUI,   SDL_SCANCODE_RGUI,
    // Special
    SDL_SCANCODE_SPACE, SDL_SCANCODE_RETURN, SDL_SCANCODE_BACKSPACE,
    SDL_SCANCODE_TAB,   SDL_SCANCODE_ESCAPE, SDL_SCANCODE_CAPSLOCK,
    // Punctuation
    SDL_SCANCODE_MINUS, SDL_SCANCODE_EQUALS,
    SDL_SCANCODE_LEFTBRACKET, SDL_SCANCODE_RIGHTBRACKET,
    SDL_SCANCODE_BACKSLASH, SDL_SCANCODE_SEMICOLON,
    SDL_SCANCODE_APOSTROPHE, SDL_SCANCODE_GRAVE,
    SDL_SCANCODE_COMMA, SDL_SCANCODE_PERIOD, SDL_SCANCODE_SLASH,
    // System
    SDL_SCANCODE_PRINTSCREEN, SDL_SCANCODE_SCROLLLOCK, SDL_SCANCODE_PAUSE,
    // Numpad
    SDL_SCANCODE_KP_0, SDL_SCANCODE_KP_1, SDL_SCANCODE_KP_2,
    SDL_SCANCODE_KP_3, SDL_SCANCODE_KP_4, SDL_SCANCODE_KP_5,
    SDL_SCANCODE_KP_6, SDL_SCANCODE_KP_7, SDL_SCANCODE_KP_8,
    SDL_SCANCODE_KP_9,
    SDL_SCANCODE_KP_PLUS, SDL_SCANCODE_KP_MINUS,
    SDL_SCANCODE_KP_MULTIPLY, SDL_SCANCODE_KP_DIVIDE,
    SDL_SCANCODE_KP_ENTER, SDL_SCANCODE_KP_PERIOD, SDL_SCANCODE_NUMLOCKCLEAR,
};

static std::optional<ee::input::Key> sdlToKey(SDL_Scancode _sc)
{
    static std::unordered_map<SDL_Scancode, ee::input::Key> s_reverse;
    static bool s_built = false;
    if (!s_built) {
        s_built = true;
        constexpr size_t count = sizeof(s_keyTable) / sizeof(s_keyTable[0]);
        for (size_t i = 0; i < count; ++i)
            s_reverse[s_keyTable[i]] = static_cast<ee::input::Key>(i);
    }
    auto it = s_reverse.find(_sc);
    if (it == s_reverse.end()) return std::nullopt;
    return it->second;
}

static std::optional<ee::input::MouseButton> sdlToMouseButton(Uint8 _btn)
{
    switch (_btn) {
        case SDL_BUTTON_LEFT:   return ee::input::MouseButton::Left;
        case SDL_BUTTON_MIDDLE: return ee::input::MouseButton::Middle;
        case SDL_BUTTON_RIGHT:  return ee::input::MouseButton::Right;
        case SDL_BUTTON_X1:     return ee::input::MouseButton::X1;
        case SDL_BUTTON_X2:     return ee::input::MouseButton::X2;
        default:                return std::nullopt;
    }
}

static std::optional<ee::input::GamepadButton> sdlToGamepadButton(Uint8 _btn)
{
    switch (static_cast<SDL_GamepadButton>(_btn)) {
        case SDL_GAMEPAD_BUTTON_SOUTH:          return ee::input::GamepadButton::South;
        case SDL_GAMEPAD_BUTTON_EAST:           return ee::input::GamepadButton::East;
        case SDL_GAMEPAD_BUTTON_WEST:           return ee::input::GamepadButton::West;
        case SDL_GAMEPAD_BUTTON_NORTH:          return ee::input::GamepadButton::North;
        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:  return ee::input::GamepadButton::LeftShoulder;
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER: return ee::input::GamepadButton::RightShoulder;
        case SDL_GAMEPAD_BUTTON_LEFT_STICK:     return ee::input::GamepadButton::LeftStick;
        case SDL_GAMEPAD_BUTTON_RIGHT_STICK:    return ee::input::GamepadButton::RightStick;
        case SDL_GAMEPAD_BUTTON_START:          return ee::input::GamepadButton::Start;
        case SDL_GAMEPAD_BUTTON_BACK:           return ee::input::GamepadButton::Back;
        case SDL_GAMEPAD_BUTTON_GUIDE:          return ee::input::GamepadButton::Guide;
        case SDL_GAMEPAD_BUTTON_DPAD_UP:        return ee::input::GamepadButton::DpadUp;
        case SDL_GAMEPAD_BUTTON_DPAD_DOWN:      return ee::input::GamepadButton::DpadDown;
        case SDL_GAMEPAD_BUTTON_DPAD_LEFT:      return ee::input::GamepadButton::DpadLeft;
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:     return ee::input::GamepadButton::DpadRight;
        default:                                return std::nullopt;
    }
}

static std::optional<ee::input::GamepadAxis> sdlToGamepadAxis(Uint8 _axis)
{
    switch (static_cast<SDL_GamepadAxis>(_axis)) {
        case SDL_GAMEPAD_AXIS_LEFTX:          return ee::input::GamepadAxis::LeftX;
        case SDL_GAMEPAD_AXIS_LEFTY:          return ee::input::GamepadAxis::LeftY;
        case SDL_GAMEPAD_AXIS_RIGHTX:         return ee::input::GamepadAxis::RightX;
        case SDL_GAMEPAD_AXIS_RIGHTY:         return ee::input::GamepadAxis::RightY;
        case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:   return ee::input::GamepadAxis::LeftTrigger;
        case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:  return ee::input::GamepadAxis::RightTrigger;
        default:                              return std::nullopt;
    }
}

// ─── InputManager ────────────────────────────────────────────────────────────

ee::input::InputManager::InputManager()
{
    m_mouseX = 0.f;
    m_mouseY = 0.f;
    SDL_Init(SDL_INIT_GAMEPAD);
}

ee::input::InputManager::~InputManager()
{
    if (m_controller != nullptr)
        SDL_CloseGamepad(m_controller);
}

bool ee::input::InputManager::IsKeyDown(Key _key) const
{
    if (auto it = m_keysStates.find(_key); it != m_keysStates.end())
        return it->second.isDown;
    return false;
}

bool ee::input::InputManager::IsKeyReleased(Key _key) const
{
    if (auto it = m_keysStates.find(_key); it != m_keysStates.end())
        return it->second.isRelease;
    return false;
}

bool ee::input::InputManager::IsKeyHeld(Key _key) const
{
    if (auto it = m_keysStates.find(_key); it != m_keysStates.end())
        return it->second.isHeld;
    return false;
}

bool ee::input::InputManager::IsMouseDown(MouseButton _key) const
{
    if (auto it = m_mouseButtonsStates.find(_key); it != m_mouseButtonsStates.end())
        return it->second.isDown;
    return false;
}

bool ee::input::InputManager::IsMouseReleased(MouseButton _key) const
{
    if (auto it = m_mouseButtonsStates.find(_key); it != m_mouseButtonsStates.end())
        return it->second.isRelease;
    return false;
}

bool ee::input::InputManager::IsMouseHeld(MouseButton _key) const
{
    if (auto it = m_mouseButtonsStates.find(_key); it != m_mouseButtonsStates.end())
        return it->second.isHeld;
    return false;
}

bool ee::input::InputManager::IsKeyDown(GamepadButton _key) const
{
    if (auto it = m_gamePadButtonsStates.find(_key); it != m_gamePadButtonsStates.end())
        return it->second.isDown;
    return false;
}

bool ee::input::InputManager::IsKeyReleased(GamepadButton _key) const
{
    if (auto it = m_gamePadButtonsStates.find(_key); it != m_gamePadButtonsStates.end())
        return it->second.isRelease;
    return false;
}

bool ee::input::InputManager::IsKeyHeld(GamepadButton _key) const
{
    if (auto it = m_gamePadButtonsStates.find(_key); it != m_gamePadButtonsStates.end())
        return it->second.isHeld;
    return false;
}

float ee::input::InputManager::getAxisForce(GamepadAxis _axis) const
{
    if (auto it = m_gamePadAxesStates.find(_axis); it != m_gamePadAxesStates.end())
        return it->second;
    return 0.f;
}

bool ee::input::InputManager::update()
{
    
    for (auto &paire : m_keysStates) {
        if (paire.second.isDown)    { paire.second.isDown = false; paire.second.isHeld = true; }
        if (paire.second.isRelease) { paire.second.isRelease = false; paire.second.isHeld = false; }
    }
    for (auto &paire : m_mouseButtonsStates) {
        if (paire.second.isDown)    { paire.second.isDown = false; paire.second.isHeld = true; }
        if (paire.second.isRelease) { paire.second.isRelease = false; paire.second.isHeld = false; }
    }
    if (m_controller) {
        for (auto &paire : m_gamePadButtonsStates) {
            if (paire.second.isDown)    { paire.second.isDown = false; paire.second.isHeld = true; }
            if (paire.second.isRelease) { paire.second.isRelease = false; paire.second.isHeld = false; }
        }
    }

    SDL_Event events;
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_EVENT_QUIT:
            return false;

        case SDL_EVENT_KEY_DOWN:
            if (auto key = sdlToKey(events.key.scancode)) {
                if (!m_keysStates[*key].isHeld)
                    m_keysStates[*key] = {true, false, false};
            }
            break;

        case SDL_EVENT_KEY_UP:
            if (auto key = sdlToKey(events.key.scancode))
                m_keysStates[*key] = {false, true, false};
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (auto btn = sdlToMouseButton(events.button.button)) {
                if (!m_mouseButtonsStates[*btn].isHeld)
                    m_mouseButtonsStates[*btn] = {true, false, false};
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (auto btn = sdlToMouseButton(events.button.button))
                m_mouseButtonsStates[*btn] = {false, true, false};
            break;

        case SDL_EVENT_MOUSE_MOTION:
            m_mouseX = events.motion.x;
            m_mouseY = events.motion.y;
            break;

        case SDL_EVENT_GAMEPAD_ADDED:
            m_controller = SDL_OpenGamepad(events.gdevice.which);
            if (m_onGamepadConnected)
                m_onGamepadConnected();
            break;

        case SDL_EVENT_GAMEPAD_REMOVED:
            if (m_controller != nullptr) {
                SDL_CloseGamepad(m_controller);
                m_controller = nullptr;
            }
            break;

        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
            if (auto btn = sdlToGamepadButton(events.gbutton.button)) {
                if (!m_gamePadButtonsStates[*btn].isHeld)
                    m_gamePadButtonsStates[*btn] = {true, false, false};
            }
            break;

        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            if (auto btn = sdlToGamepadButton(events.gbutton.button))
                m_gamePadButtonsStates[*btn] = {false, true, false};
            break;

        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
            if (auto axis = sdlToGamepadAxis(events.gaxis.axis))
                m_gamePadAxesStates[*axis] = events.gaxis.value / 32767.f;
            break;
        }
    }
    return true;
}
