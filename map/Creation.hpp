/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Creation
*/

#ifndef CREATION_HPP_
# define CREATION_HPP_

# include "irrlichtInc.hpp"
# include "vectorInc.hpp"
# include "ObjectMap.hpp"

# define	PATH_BLOCK			"./assets/mesh/block.obj"
# define	SCALE_BLOCK			5
# define	PATH_TEXTURE_DESTRUCT_BLK	"./assets/material/bdc_grass_path.png"
# define	PATH_TEXTURE_INDESTRUCT_BLK	"./assets/material/bdc_stonebrick01.png"
# define	SCALE_GROUND			5.6
# define	PATH_GROUND			"./assets/mesh/blocks/ground.3ds"
# define	PATH_TEXTURE_GROUND		"./assets/material/bdc_dirt03.png"

class graph_content;

class Creation
{
public:
	Creation(std::vector<std::vector<char> > map, graph_content &graph);
	~Creation();
	ObjectMap		create_block_destructible(irr::f32, irr::f32, graph_content&);
	ObjectMap		create_block_indestructible(irr::f32, irr::f32, graph_content&);
	ObjectMap		create_ground(irr::f32, irr::f32, graph_content&);
	ObjectMap		create_bomberman(irr::f32 x, irr::f32 y, graph_content &graph);
	std::vector<ObjectMap>	&get_map();
private:
	std::vector<ObjectMap> blocks;
};

#endif /* !CREATION_HPP_ */
