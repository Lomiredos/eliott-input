#include "input/InputManager.hpp"

bool ee::input::InputManager::update()
{
	SDL_Event events;
	// Mettre à jour les états des touches clavier
	for (auto &paire : m_keysStates)
	{

		if (paire.second.isDown)
		{
			paire.second.isDown = false;
			paire.second.isHeld = true;
		}
		if (paire.second.isRelease)
		{
			paire.second.isRelease = false;
			paire.second.isHeld = false;
		}
	}

	// mettre a jour les etats de la manette
	if (m_controller)
	{
		for (auto &paire : m_gamePadButtonsStates)
		{

			if (paire.second.isDown)
			{
				paire.second.isDown = false;
				paire.second.isHeld = true;
			}
			if (paire.second.isRelease)
			{
				paire.second.isRelease = false;
				paire.second.isHeld = false;
			}
		}
	}

	// Mettre à jour les états des boutons de souris
	for (auto &paire : m_mouseButtonsStates)
	{
		if (paire.second.isDown)
		{
			paire.second.isDown = false;
			paire.second.isHeld = true;
		}
		if (paire.second.isRelease)
		{
			paire.second.isRelease = false;
			paire.second.isHeld = false;
		}
	}
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_EVENT_QUIT:
			return false;

		case SDL_EVENT_KEY_DOWN:

			if (m_keysStates[events.key.scancode].isHeld == false)
				m_keysStates[events.key.scancode] = {true, false, false};
			break;

		case SDL_EVENT_KEY_UP:
			m_keysStates[events.key.scancode] = {false, true, false};
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (m_mouseButtonsStates[(int)events.button.button].isHeld == false)
				m_mouseButtonsStates[(int)events.button.button] = {true, false, false};
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			m_mouseButtonsStates[(int)events.button.button] = {false, true, false};
			break;
		case SDL_EVENT_MOUSE_MOTION:
			m_mouseX = events.motion.x;
			m_mouseY = events.motion.y;
			break;

		case SDL_EVENT_GAMEPAD_ADDED:
			m_controller = SDL_OpenGamepad(events.gdevice.which);

			if (m_onGamepadConnected)
				m_onGamepadConnected(SDL_GetGamepadType(m_controller));
			

			break;
		case SDL_EVENT_GAMEPAD_REMOVED:
			if (m_controller != nullptr)
			{
				SDL_CloseGamepad(m_controller);
				m_controller = nullptr;
			}
			break;
		case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
			if (m_gamePadButtonsStates[static_cast<SDL_GamepadButton>(events.gbutton.button)].isHeld == false)
				m_gamePadButtonsStates[static_cast<SDL_GamepadButton>(events.gbutton.button)] = {true, false, false};
			break;

		case SDL_EVENT_GAMEPAD_BUTTON_UP:
			m_gamePadButtonsStates[static_cast<SDL_GamepadButton>(events.gbutton.button)] = {false, true, false};
			break;
		case SDL_EVENT_GAMEPAD_AXIS_MOTION:
			m_gamePadAxesStates[static_cast<SDL_GamepadAxis>(events.gaxis.axis)] = static_cast<float>(events.gaxis.value / 32767.0f);
			break;
		}
	}
	return true;
}
