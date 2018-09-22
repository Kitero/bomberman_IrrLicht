//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include "SpecBomb.hpp"

SpecBomb::SpecBomb()
{
}

SpecBomb::~SpecBomb()
{
}

void		SpecBomb::setWallPass(bool wallPass)
{
	_isWallPass = wallPass;
}

void		SpecBomb::setRange(size_t range)
{
	_range = range;
}

void		SpecBomb::setPosition(irr::f32 x, irr::f32 y)
{
	_pos.insert(_pos.begin(), y);
	_pos.insert(_pos.begin(), x);
	
}

void		SpecBomb::setTimer(double timer)
{
	_timer = timer * 100000;
}

void		SpecBomb::setPlayerType(player_type_e player)
{
	_player = player;
}

bool		SpecBomb::getWallPass() const
{
	return _isWallPass;
}

size_t		SpecBomb::getRange() const
{
	return _range;
}

std::vector<irr::f32>	SpecBomb::getPosition() const
{
	return _pos;
}

double		SpecBomb::getTimer() const
{
	return _timer;
}

player_type_e	SpecBomb::getPlayerType() const
{
	return _player;
}
