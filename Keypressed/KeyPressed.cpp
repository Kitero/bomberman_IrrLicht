//
// EPITECH PROJECT, 2018
// KeyPressed
// File description:
// KeyPressed
//

#include "KeyPressedEvent.hpp"

MyEventReceiver::MyEventReceiver() {
	for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
		KeyIsDown[i] = false;
}

bool	MyEventReceiver::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	return false;
}

bool	MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode)
{
	return KeyIsDown[keyCode];
}
