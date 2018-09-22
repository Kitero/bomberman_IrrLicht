//
// EPITECH PROJECT, 2018
// KeyPressed
// File description:
// KeyPressed
//

#ifndef KEY_PRESSED_HPP_
# define KEY_PRESSED_HPP_

# include "vectorInc.hpp"
# include "irrlichtInc.hpp"

class MyEventReceiver : public irr::IEventReceiver
{
public:
	virtual bool OnEvent(const irr::SEvent& event);
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode);
	MyEventReceiver();
private:
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif // !KEY_PRESSED_HPP_
