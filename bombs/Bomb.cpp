//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include "Bomb.hpp"
#include "ObjectsGame.hpp"
#include <iostream>

Bomb::Bomb(SpecBomb spec, ObjectsGame &obj_game)
	: _isWallPass(spec.getWallPass()),
	  _range(spec.getRange()),
	  _pos(spec.getPosition()),
	  _timer(spec.getTimer()),
	  _status(READY)
{
	createBomb(obj_game.get_graph());
	_dropTime = std::clock();
}

Bomb::~Bomb()
{
}

bool	Bomb::explosion()
{
	if (std::clock() >= _dropTime + _timer) {
		_status = EXPLODED;
		return true;
	}
	return false;
}

void	Bomb::setIsWallPass(bool value)
{
	_isWallPass = value;
}

void	Bomb::setRange(size_t value)
{
	_range = value;
}

void	Bomb::setPosition(std::vector<irr::f32> value)
{
	_pos = value;
	irr::core::vector3df pos(_pos[0], 0, _pos[1]);
	_obj.set_pos(pos);
}

size_t	Bomb::getRange() const
{
	return _range;
}

bool	Bomb::getIsWallPass() const
{
	return _isWallPass;
}

std::vector<irr::f32>	Bomb::getPosition() const
{
	return _pos;
}

void	Bomb::createBomb(graph_content &graph)
{
	irr::scene::IAnimatedMeshSceneNode	*node =	create_props(PATH_BOMB, graph);
	_obj.set_node(node);
	irr::core::vector3df		pos(_pos[0], 0, _pos[1]);
	irr::core::vector3df		scale(SCALE_BOMB, SCALE_BOMB, SCALE_BOMB);
	_obj.set_texture(0, PATH_TEXTURE_BOMB, graph.get_driver());
	_obj.set_scale(scale);
	_obj.set_pos(pos);
}

ObjectMap	&Bomb::getObj()
{
	return _obj;
}

std::vector<irr::f32>	&Bomb::getPosition()
{
	return _pos;
}

status_e	&Bomb::getStatus()
{
	return _status;
}

void		Bomb::setStatus(status_e status)
{
	_status = status;
}

void		Bomb::setTimeDrop()
{
	_dropTime = std::clock();
}

bool		Bomb::checkExplosionsFree(irr::core::vector3df &pos)
{
	std::vector<ObjectMap>::reverse_iterator	explosion;
	for (explosion = _explosionBlocks.rbegin(); explosion != _explosionBlocks.rend(); explosion++) {
		if ((*explosion).get_type() == EXPLOSION_FREE) {
			(*explosion).set_type(EXPLOSION);
			(*explosion).set_pos(pos);
			setTimeExplosion();
		}
	}
	return false;
}

void		Bomb::createExplosionBlock(graph_content &graph, int x, int z)
{
	irr::core::vector3df pos(x, 0, z);
	if (checkExplosionsFree(pos) == true)
		return;
	ObjectMap	obj;
	irr::scene::IAnimatedMeshSceneNode	*node = create_props(PATH_BLOCK, graph);
	obj.set_node(node);
	irr::core::vector3df scale(SCALE_EXPLOSION, SCALE_EXPLOSION, SCALE_EXPLOSION);
	obj.set_texture(0, PATH_TEXTURE_EXPLOSION, graph.get_driver());
	obj.set_scale(scale);
	obj.set_pos(pos);
	obj.set_type(EXPLOSION);
	setTimeExplosion();
	_explosionBlocks.insert(_explosionBlocks.begin(), obj);
}

void		Bomb::explosionIsFinished()
{
	std::vector<ObjectMap>::reverse_iterator	explosion = _explosionBlocks.rbegin();
	if (_timeExplosion + TIME_EXPLOSION <= std::clock())
		for (explosion = _explosionBlocks.rbegin(); explosion != _explosionBlocks.rend(); explosion++) {
			(*explosion).hide();
			(*explosion).set_type(EXPLOSION_FREE);
		}
}

void		Bomb::setTimeExplosion()
{
	_timeExplosion = std::clock();
}
