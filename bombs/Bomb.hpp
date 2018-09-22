/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Bomb
*/

#ifndef		BOMB_HPP_
# define	BOMB_HPP_

# include <ctime>
# include "SpecBomb.hpp"
# include "ObjectMap.hpp"

# define	PATH_BOMB		"./assets/mesh/bomb/black-handbomb.obj"
# define	SCALE_BOMB		3
# define	PATH_TEXTURE_BOMB	"./assets/mesh/bomb/sprite bomb.png"

# define	PATH_BLOCK		"./assets/mesh/block.obj"
# define	SCALE_EXPLOSION		5
# define	PATH_TEXTURE_EXPLOSION	"./assets/material/lava_still.png"

# define	TIME_EXPLOSION		2

class ObjectsGame;

typedef enum
{
	READY,
	EXPLODED
}	status_e;

class Bomb
{
private:
	bool			_isWallPass;
	size_t			_range;
	std::vector<irr::f32>	_pos;
	ObjectMap		_obj;
	size_t			_timer;
	std::clock_t		_dropTime;
	status_e		_status;
	std::vector<ObjectMap>	_explosionBlocks;
	std::clock_t		_timeExplosion;
public:
	Bomb(SpecBomb spec, ObjectsGame &obj_game);
	~Bomb();
	void			setRange(size_t value);
	void			setIsWallPass(bool value);
	void			setPosition(std::vector<irr::f32> value);
	std::vector<irr::f32>	&getPosition();
	ObjectMap		&getObj();
	status_e		&getStatus();
	void			setTimeDrop();
	void			setStatus(status_e status);
	size_t			getRange() const;
	bool			getIsWallPass() const;
	std::vector<irr::f32>	getPosition() const;
	void			createBomb(graph_content &graph);
	bool			explosion();
	void			createExplosionBlock(graph_content &graph, int x, int z);
	void			explosionIsFinished();
	void			setTimeExplosion();
	bool			checkExplosionsFree(irr::core::vector3df &pos);
};

#endif		/* !BOMB_HPP_ */
