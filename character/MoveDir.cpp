//
// EPITECH PROJECT, 2018
// move
// File description:
// move
//

#include "Character.hpp"

void	Character::move_up(std::vector<ObjectMap> &map, std::vector<Character> &chara)
{
	_pos[0] = _pos[0] + _speed;
	if (checkNextPos(map, chara) == false)
		_pos[0] = _pos[0] - _speed;
	else {
		irr::core::vector3df	rotation(0, 90, 0);
		rotate(rotation);
	}
}

void	Character::move_down(std::vector<ObjectMap> &map, std::vector<Character> &chara)
{
	_pos[0] = _pos[0] - _speed;
	if (checkNextPos(map, chara) == false)
		_pos[0] = _pos[0] + _speed;
	else {
		irr::core::vector3df	rotation(0, 270, 0);
		rotate(rotation);
	}
}

void	Character::move_left(std::vector<ObjectMap> &map, std::vector<Character> &chara)
{
	_pos[1] = _pos[1] + _speed;
	if (checkNextPos(map, chara) == false)
		_pos[1] = _pos[1] - _speed;
	else {
		irr::core::vector3df	rotation(0, 0, 0);
		rotate(rotation);
	}
}

void	Character::move_right(std::vector<ObjectMap> &map, std::vector<Character> &chara)
{
	_pos[1] = _pos[1] - _speed;
	if (checkNextPos(map, chara) == false)
		_pos[1] = _pos[1] + _speed;
	else {
		irr::core::vector3df	rotation(0, 180, 0);
		rotate(rotation);
	}
}
