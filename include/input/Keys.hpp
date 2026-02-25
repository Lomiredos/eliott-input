#pragma once

namespace ee::input {

    enum class Key {
        // Letters
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        // Numbers (row above letters)
        Num0, Num1, Num2, Num3, Num4,
        Num5, Num6, Num7, Num8, Num9,

        // Function keys
        F1, F2, F3, F4,  F5,  F6,
        F7, F8, F9, F10, F11, F12,

        // Navigation
        Up, Down, Left, Right,
        Home, End, PageUp, PageDown,
        Insert, Delete,

        // Modifiers
        LShift, RShift,
        LCtrl,  RCtrl,
        LAlt,   RAlt,
        LGui,   RGui,

        // Special
        Space, Enter, Backspace, Tab, Escape, CapsLock,

        // Punctuation
        Minus,        // -
        Equals,       // =
        LeftBracket,  // [
        RightBracket, // ]
        Backslash,    // '\'
        Semicolon,    // ;
        Apostrophe,   // '
        GraveAccent,  // `
        Comma,        // ,
        Period,       // .
        Slash,        // /

        // System
        PrintScreen, ScrollLock, Pause,

        // Numpad
        Numpad0, Numpad1, Numpad2, Numpad3, Numpad4,
        Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
        NumpadPlus, NumpadMinus, NumpadMultiply, NumpadDivide,
        NumpadEnter, NumpadPeriod, NumLock,
    };

    enum class MouseButton {
        Left,
        Middle,
        Right,
        X1,
        X2,
    };

    enum class GamepadButton {
        South,          // A (Xbox) / Croix (PS)
        East,           // B (Xbox) / Rond (PS)
        West,           // X (Xbox) / Carré (PS)
        North,          // Y (Xbox) / Triangle (PS)
        LeftShoulder,   // LB / L1
        RightShoulder,  // RB / R1
        LeftStick,      // LS (clic stick gauche)
        RightStick,     // RS (clic stick droit)
        Start,
        Back,
        Guide,          // bouton home
        DpadUp, DpadDown, DpadLeft, DpadRight,
    };

    enum class GamepadAxis {
        LeftX,          // stick gauche horizontal
        LeftY,          // stick gauche vertical
        RightX,         // stick droit horizontal
        RightY,         // stick droit vertical
        LeftTrigger,    // L2 / LT
        RightTrigger,   // R2 / RT
    };

} // namespace ee::input
