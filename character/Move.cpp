//
// EPITECH PROJECT, 2018
// move
// File description:
// move
//

#include "Character.hpp"
#include "KeyPressedEvent.hpp"
#include <iostream>

void	Character::Player4Move(ObjectsGame &objGame, MyEventReceiver *evtKey)
{
	if (evtKey->IsKeyDown(irr::KEY_KEY_O) == true)
		move_up(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_L) == true)
		move_down(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_K) == true)
		move_left(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_M) == true)
		move_right(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_P) == true)
		dropBomb(objGame);
	irr::core::vector3df	pos(_pos[0], -20, _pos[1]);
	_obj.get_node()->setPosition(pos);
}

void	Character::Player3Move(ObjectsGame &objGame, MyEventReceiver *evtKey)
{
	if (evtKey->IsKeyDown(irr::KEY_KEY_T) == true)
		move_up(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_G) == true)
		move_down(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_F) == true)
		move_left(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_H) == true)
		move_right(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_Y) == true)
		dropBomb(objGame);
	irr::core::vector3df	pos(_pos[0], -20, _pos[1]);
	_obj.get_node()->setPosition(pos);
}

void	Character::Player2Move(ObjectsGame &objGame, MyEventReceiver *evtKey)
{
	if (evtKey->IsKeyDown(irr::KEY_KEY_Z) == true)
		move_up(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_S) == true)
		move_down(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_Q) == true)
		move_left(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_D) == true)
		move_right(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_E) == true)
		dropBomb(objGame);
	irr::core::vector3df	pos(_pos[0], -20, _pos[1]);
	_obj.get_node()->setPosition(pos);
}

void	Character::Player1Move(ObjectsGame &objGame, MyEventReceiver *evtKey)
{
	if (evtKey->IsKeyDown(irr::KEY_UP))
		move_up(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_DOWN))
		move_down(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_RIGHT))
		move_right(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_LEFT))
		move_left(objGame.get_map(), objGame.get_character());
	if (evtKey->IsKeyDown(irr::KEY_KEY_N) == true)
		dropBomb(objGame);
	irr::core::vector3df	pos(_pos[0], -20, _pos[1]);
	_obj.get_node()->setPosition(pos);
}

void	Character::PlayerMove(ObjectsGame &objGame, MyEventReceiver *evtKey)
{
	std::string	key;
	if (_live == false)
		return;
	if (_player_type == PLAYER_1)
		Player1Move(objGame, evtKey);
	else if (_player_type == PLAYER_2)
		Player2Move(objGame, evtKey);
	else if (_player_type == PLAYER_3)
		Player3Move(objGame, evtKey);
	else if (_player_type == PLAYER_4)
		Player4Move(objGame, evtKey);
}
