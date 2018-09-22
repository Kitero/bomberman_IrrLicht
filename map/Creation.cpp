/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Creation
*/

#include "Creation.hpp"
#include "Graph.hpp"

Creation::Creation(std::vector<std::vector<char> > map, graph_content &graph)
{
	std::vector<char>::iterator	col;
        irr::f32 x = 0;
        irr::f32 y = 0;

	for (auto raw : map) {
		x = 0;
                for (col = raw.begin(); col != raw.end(); col++) {
                        if ((*col) == 'o') {
                                blocks.insert(blocks.end(), create_block_destructible(x, y, graph));
                                blocks.insert(blocks.end(), create_ground(x, y, graph));
			}
                        else if ((*col) == 'x')
                                blocks.insert(blocks.end(), create_block_indestructible(x, y, graph));
                        else
                                blocks.insert(blocks.end(), create_ground(x, y, graph));
                        x = x + SIZE_BLOCK;
                }
                y = y + SIZE_BLOCK;
        }
}

Creation::~Creation()
{

}

ObjectMap	Creation::create_block_destructible(irr::f32 x, irr::f32 y, graph_content &graph)
{
	ObjectMap				obj;
	irr::scene::IAnimatedMeshSceneNode	*node = create_props(PATH_BLOCK, graph);
	obj.set_node(node);
	irr::core::vector3df pos(x, 0, y);
	irr::core::vector3df scale(SCALE_BLOCK, SCALE_BLOCK, SCALE_BLOCK);
	obj.set_texture(0, PATH_TEXTURE_DESTRUCT_BLK, graph.get_driver());
	obj.set_scale(scale); // block de 40*40
	obj.set_pos(pos);
	obj.set_type(DESTRUCT_BLK);
	return obj;
}

ObjectMap	Creation::create_block_indestructible(irr::f32 x, irr::f32 y, graph_content &graph)
{
	ObjectMap				obj;
	irr::scene::IAnimatedMeshSceneNode	*node = create_props(PATH_BLOCK, graph);
	obj.set_node(node);
	irr::core::vector3df pos(x, 0, y);
	irr::core::vector3df scale(SCALE_BLOCK, SCALE_BLOCK, SCALE_BLOCK);
	obj.set_texture(0, PATH_TEXTURE_INDESTRUCT_BLK, graph.get_driver());
	obj.set_scale(scale);
	obj.set_pos(pos);
	obj.set_type(INDESTRUCT_BLK);
	return obj;
}

ObjectMap	Creation::create_ground(irr::f32 x, irr::f32 y, graph_content &graph)
{
	ObjectMap				obj;
	irr::scene::IAnimatedMeshSceneNode	*node = create_props(PATH_GROUND, graph);
	obj.set_node(node);
	irr::core::vector3df pos(x, -20, y);
	irr::core::vector3df scale(SCALE_GROUND, SCALE_GROUND, SCALE_GROUND);
	obj.set_texture(0, PATH_TEXTURE_GROUND, graph.get_driver());
	obj.set_scale(scale);
	obj.set_pos(pos);
	obj.set_type(GROUND);
	return obj;
}

std::vector<ObjectMap>	&Creation::get_map()
{
	return blocks;
}
