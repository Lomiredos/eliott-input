#pragma once
#include <unordered_map>
#include <functional>
#include "input/Keys.hpp"

struct SDL_Gamepad;

namespace ee::input
{
    struct KeyState
    {
        bool isDown;
        bool isRelease;
        bool isHeld;
    };

    class InputManager
    {

    private:
        // manette
        SDL_Gamepad *m_controller = nullptr;
        std::unordered_map<GamepadButton, KeyState> m_gamePadButtonsStates;
        std::unordered_map<GamepadAxis, float> m_gamePadAxesStates;

        // clavier
        std::unordered_map<Key, KeyState> m_keysStates;
        std::unordered_map<MouseButton, KeyState> m_mouseButtonsStates;

        std::function<void()> m_onGamepadConnected;

        float m_mouseX;
        float m_mouseY;

        InputManager(const InputManager &) = delete;
        InputManager &operator=(const InputManager &) = delete;

        InputManager();

    public:

        ~InputManager();
        static InputManager &getInstance()
        {
            static InputManager instance = InputManager();
            return instance;
        }

        bool IsKeyDown(Key _key) const;

        bool IsKeyReleased(Key _key) const;
        bool IsKeyHeld(Key _key) const;

        bool IsMouseDown(MouseButton _key) const;
        bool IsMouseReleased(MouseButton _key) const;
        bool IsMouseHeld(MouseButton _key) const;

        bool IsKeyDown(GamepadButton _key) const;
        bool IsKeyReleased(GamepadButton _key) const;
        bool IsKeyHeld(GamepadButton _key) const;

        float getAxisForce(GamepadAxis _axis) const;

        float getMousePosX() const { return m_mouseX; }
        float getMousePosY() const { return m_mouseY; }

        void setOnGamepadConnected(const std::function<void()>& _fonc){
            m_onGamepadConnected = _fonc;
        }

        bool update();
    };
}