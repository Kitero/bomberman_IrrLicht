//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include <vector>
#include "ObjectMap.hpp"

ObjectMap::ObjectMap()
{
}

ObjectMap::~ObjectMap()
{
}

irr::scene::IAnimatedMeshSceneNode	*ObjectMap::get_node() const
{
	return _node;
}

type_block	ObjectMap::get_type() const
{
	return _type;
}

irr::core::vector3df	ObjectMap::get_pos() const
{
	return _pos;
}

void	ObjectMap::set_type(type_block type)
{
	_type = type;
}

void	ObjectMap::set_node(irr::scene::IAnimatedMeshSceneNode *node)
{
	_node = node;
}

void	ObjectMap::set_texture(irr::u32 texture_layer, std::string path_texture, irr::video::IVideoDriver *driver)
{
	_node->setMaterialTexture(texture_layer, driver->getTexture(path_texture.c_str()));
	_node->setMaterialType(irr::video::EMT_SOLID);
}

void	ObjectMap::set_pos(irr::core::vector3df &pos)
{
	_node->setPosition(pos);
	_pos = pos;
}

void	ObjectMap::set_scale(irr::core::vector3df &scale)
{
	_node->setScale(scale);
}

void	ObjectMap::rotate(irr::core::vector3df &rotation)
{
	_node->setRotation(rotation);
}

bool	ObjectMap::isInHitbox(std::vector<irr::f32> pos) const
{
	if (pos[1] >= _pos.Z
	    && pos[1] <= _pos.Z + SIZE_BLOCK
	    && pos[0] >= _pos.X
	    && pos[0] <= _pos.X + SIZE_BLOCK)
		return true;
	return false;
}

void	ObjectMap::hide()
{
	irr::core::vector3df	pos(-100, -100, -100);
	_node->setPosition(pos);
	set_pos(pos);
}

type_block	ObjectMap::getType()
{
	return _type;
}

void	ObjectMap::destroyNode()
{
	_node->remove();
}
