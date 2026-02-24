#pragma once
#include <unordered_map>
#include <functional>
#include <SDL3/SDL.h>

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
        std::unordered_map<SDL_GamepadButton, KeyState> m_gamePadButtonsStates;
        std::unordered_map<SDL_GamepadAxis, float> m_gamePadAxesStates;

        // clavier
        std::unordered_map<SDL_Scancode, KeyState> m_keysStates;
        std::unordered_map<int, KeyState> m_mouseButtonsStates;

        std::function<void(SDL_GamepadType)> m_onGamepadConnected;

        float m_mouseX;
        float m_mouseY;

        InputManager(const InputManager &) = delete;
        InputManager &operator=(const InputManager &) = delete;

        InputManager(){
            m_mouseX = 0.;
            m_mouseY = 0.;
            SDL_Init(SDL_INIT_GAMEPAD);

        }

    public:

        ~InputManager(){
            if (m_controller != nullptr)
                SDL_CloseGamepad(m_controller);
        }

        static InputManager &getInstance()
        {
            static InputManager instance = InputManager();
            return instance;
        }

        bool IsKeyDown(SDL_Scancode _key) const
        {
            if (auto it = m_keysStates.find(_key); it != m_keysStates.end())
                return it->second.isDown;
            return false;
        }
        bool IsKeyReleased(SDL_Scancode _key) const
        {
            if (auto it = m_keysStates.find(_key); it != m_keysStates.end())
                return it->second.isRelease;
            return false;
        }
        bool IsKeyHeld(SDL_Scancode _key) const
        {
            if (auto it = m_keysStates.find(_key); it != m_keysStates.end())
                return it->second.isHeld;
            return false;
        }

        bool IsMouseDown(int _key) const
        {
            if (auto it = m_mouseButtonsStates.find(_key); it != m_mouseButtonsStates.end())
                return it->second.isDown;
            return false;
        }
        bool IsMouseReleased(int _key) const
        {
            if (auto it = m_mouseButtonsStates.find(_key); it != m_mouseButtonsStates.end())
                return it->second.isRelease;
            return false;
        }
        bool IsMouseHeld(int _key) const
        {

            if (auto it = m_mouseButtonsStates.find(_key); it != m_mouseButtonsStates.end())
                return it->second.isHeld;
            return false;
        }

        bool IsKeyDown(SDL_GamepadButton _key) const
        {
            if (auto it = m_gamePadButtonsStates.find(_key); it != m_gamePadButtonsStates.end())
                return it->second.isDown;
            return false;
        }
        bool IsKeyReleased(SDL_GamepadButton _key) const
        {
            if (auto it = m_gamePadButtonsStates.find(_key); it != m_gamePadButtonsStates.end())
                return it->second.isRelease;
            return false;
        }
        bool IsKeyHeld(SDL_GamepadButton _key) const
        {
            if (auto it = m_gamePadButtonsStates.find(_key); it != m_gamePadButtonsStates.end())
                return it->second.isHeld;
            return false;
        }

        float getAxisForce(SDL_GamepadAxis _axis) const {

            if (auto it = m_gamePadAxesStates.find(_axis); it != m_gamePadAxesStates.end()){
                return it->second;
            }
            return 0;
        }

        float getMousePosX() const { return m_mouseX; }
        float getMousePosY() const { return m_mouseY; }

        void setOnGamepadConnected(const std::function<void(SDL_GamepadType)>& _fonc){
            m_onGamepadConnected = _fonc;
        }

        bool update();
    };
}