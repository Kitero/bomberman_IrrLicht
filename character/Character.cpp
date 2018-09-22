//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include "Character.hpp"
#include "Bomb.hpp"
#include <iostream>

Character::Character(std::vector<irr::f32> pos, player_type_e player_type, graph_content &graph)
	:  _player_type(player_type),
	   _pos(pos),
	   _live(true),
	   _isWallPass(false),
	   _speed(DEFAULT_SPEED),
	   _range(2),
	   _maxBomb(1),
	   _droppedBombs(0)
{
	create_bomberman(graph);
}

Character::~Character()
{
}

void	Character::setIsWallPass(bool value)
{
	_isWallPass = value;
}

void	Character::rotate(irr::core::vector3df &rotation)
{
	_obj.rotate(rotation);
}

void	Character::setRange(size_t value)
{
	_range = value;
}

void	Character::setMaxBomb(size_t value)
{
	_maxBomb = value;
}
void	Character::setPlayerType(player_type_e player)
{
	_player_type = player;
}

void	Character::setSpeed(size_t value)
{
	_speed = value;
}

void	Character::setPosition(std::vector<irr::f32> value)
{
	_pos = value;
}

void	Character::setLive(bool value)
{
	_live = value;
}

player_type_e	Character::getPlayerType() const
{
	return _player_type;
}

ObjectMap	&Character::getObj()
{
	return _obj;
}

bool	Character::getIsWallPass() const
{
	return _isWallPass;
}
size_t	Character::getRange() const
{
	return _range;
}

size_t	Character::getMaxBomb() const
{
	return _maxBomb;
}

std::vector<irr::f32>	Character::getPosition() const
{
	return _pos;
}

size_t	Character::getSpeed() const
{
	return _speed;
}

bool	Character::getLive() const
{
	return _live;
}

std::vector<Bomb>	&Character::getBombs()
{
	return _bomb;
}

bool	Character::checkThisPos(ObjectMap &obj, irr::f32 x, irr::f32 z) const
{
	std::vector<irr::f32>			pos;
	pos.insert(pos.begin(), z);
	pos.insert(pos.begin(), x);
	return obj.isInHitbox(pos);
}

bool	Character::checkBombHere(Bomb &bomb, irr::f32 x, irr::f32 z) const
{
	if (x >= bomb.getPosition()[0] && x <= bomb.getPosition()[0] + SIZE_BLOCK
	    && z >= bomb.getPosition()[1] && z <= bomb.getPosition()[1] + SIZE_BLOCK)
		return true;
	return false;
}

bool	Character::isThereBombHere(std::vector<Character> &chara) const
{
	std::vector<Character>::reverse_iterator	character = chara.rbegin();
	std::vector<Bomb>::reverse_iterator		bomb;
	while (character != chara.rend()) {
		if ((*character).getPlayerType() != _player_type) {
			bomb = (*character).getBombs().rbegin();
			while (bomb != (*character).getBombs().rend()) {
				if (checkBombHere((*bomb), _pos[0] + SIZE_CHARA, _pos[1] + SIZE_CHARA) == true
				    || checkBombHere((*bomb), _pos[0] + SPRITE_MARGIN, _pos[1] + SPRITE_MARGIN) == true
				    || checkBombHere((*bomb), _pos[0] + SIZE_CHARA, _pos[1] + SPRITE_MARGIN) == true
				    || checkBombHere((*bomb), _pos[0] + SPRITE_MARGIN, _pos[1] + SIZE_CHARA) == true)
					return true;
				bomb++;
			}
		}
		character++;
	}
}

bool	Character::checkNextPos(std::vector<ObjectMap> &map, std::vector<Character> &chara) const
{
	std::vector<ObjectMap>::reverse_iterator	i = map.rbegin();
	if (isThereBombHere(chara) == true)
		return false;
	while (i != map.rend()) {
		if ((*i).get_type() != GROUND
		    && (checkThisPos((*i), _pos[0] + SIZE_CHARA, _pos[1] + SIZE_CHARA) == true
			|| checkThisPos((*i), _pos[0] + SPRITE_MARGIN, _pos[1] + SPRITE_MARGIN) == true
			|| checkThisPos((*i), _pos[0] + SIZE_CHARA, _pos[1] + SPRITE_MARGIN) == true
			|| checkThisPos((*i), _pos[0] + SPRITE_MARGIN, _pos[1] + SIZE_CHARA) == true))
			return false;
		i++;
	}
	return true;
}

void	Character::create_bomberman(graph_content &graph)
{
	irr::scene::IAnimatedMeshSceneNode	*node = create_props(PATH_BOMBERMAN, graph);
	_obj.set_node(node);
	irr::core::vector3df		pos(_pos[0], -20, _pos[1]);
	irr::core::vector3df		scale(SCALE_BOMBERMAN, SCALE_BOMBERMAN, SCALE_BOMBERMAN);
	_obj.set_texture(1, PATH_TEXTURE_BOMBERMAN, graph.get_driver());
	_obj.set_texture(1, PATH_TEXTURE_BOMBERMAN_FACE, graph.get_driver());
	_obj.set_scale(scale);
	_obj.set_pos(pos);
}

bool	Character::checkBombsHere(ObjectsGame &objGame)
{
	std::vector<irr::f32>	pos;
	pos.insert(pos.begin(), (_pos[1] + SIZE_CHARA / 2) - fmod((_pos[1] + SIZE_CHARA / 2), SIZE_BLOCK));
	pos.insert(pos.begin(), (_pos[0] + SIZE_CHARA / 2) - fmod((_pos[0] + SIZE_CHARA / 2), SIZE_BLOCK));
	if (objGame.checkBombsHere(pos) == true)
		return true;
	return false;
}

bool	Character::bombFreeToDrop(SpecBomb &spec)
{
	std::vector<Bomb>::reverse_iterator	bomb;
	for (bomb = _bomb.rbegin(); bomb != _bomb.rend(); bomb++)
		if ((*bomb).getStatus() == EXPLODED) {
			(*bomb).setStatus(READY);
			(*bomb).setTimeDrop();
			(*bomb).setRange(spec.getRange());
			(*bomb).setPosition(spec.getPosition());
			_droppedBombs++;
			return true;
		}
	return false;
}

void	Character::dropBomb(ObjectsGame &obj_game)
{
	if (_droppedBombs >= _maxBomb)
		return;
	if (checkBombsHere(obj_game) == false)
		return;
	SpecBomb	spec;
	spec.setWallPass(_isWallPass);
	spec.setRange(_range);
	spec.setPosition((_pos[0] + SIZE_CHARA / 2) - fmod((_pos[0] + SIZE_CHARA / 2), SIZE_BLOCK),
			 (_pos[1] + SIZE_CHARA / 2) - fmod((_pos[1] + SIZE_CHARA / 2), SIZE_BLOCK));
	spec.setTimer(3);
	spec.setPlayerType(_player_type);
	if (bombFreeToDrop(spec) == true)
		return;
	Bomb	bomb(spec, obj_game);
	_droppedBombs++;
	_bomb.insert(_bomb.begin(), bomb);
}

void	Character::bombExplosed()
{
	_droppedBombs--;
}

void	Character::die()
{
	irr::core::vector3df	pos(-100, -100, -100);
	std::vector<irr::f32>	pos2d;
	pos2d.insert(pos2d.begin(), -100);
	pos2d.insert(pos2d.begin(), -100);
	setPosition(pos2d);
	_obj.set_pos(pos);
	_live = false;
}
