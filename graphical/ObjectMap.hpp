//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#ifndef		MY_OBJ_HPP
# define	MY_OBJ_HPP

# include <string>
# include <ctime>
# include <random>
# include "irrlichtInc.hpp"
# include "vectorInc.hpp"

# define	SIZE_BLOCK		40.0

class graph_content;

typedef enum
{
	DESTRUCT_BLK,
	INDESTRUCT_BLK,
	GROUND,
	EXPLOSION,
	EXPLOSION_FREE,
	FIRE,
	BOMB,
	ROLLER
}	type_block;

class ObjectMap
{
private:
	irr::scene::IAnimatedMeshSceneNode	*_node;
	irr::core::vector3df			_pos;
	type_block				_type;
	std::clock_t				_timeCreation;
public:
	ObjectMap();
	~ObjectMap();
	irr::scene::IAnimatedMeshSceneNode	*get_node() const;
	type_block				get_type() const;
	bool					isInHitbox(std::vector<irr::f32> pos) const;
	irr::core::vector3df			get_pos() const;
	void					set_type(type_block type);
	void					set_node(irr::scene::IAnimatedMeshSceneNode *node);
	void					set_texture(irr::u32 texture_layer, std::string path_texture, irr::video::IVideoDriver *driver);
	void					set_pos(irr::core::vector3df &pos);
	void					set_scale(irr::core::vector3df &scale);
	void					rotate(irr::core::vector3df &rotation);
	void					destroyNode();
	void					hide();
	type_block				getType();
};

std::vector<ObjectMap>			init_objects(graph_content &graph);
irr::scene::IAnimatedMeshSceneNode      *create_props(std::string path, graph_content &graph);

#endif		/* !MY_OBJ_HPP */
