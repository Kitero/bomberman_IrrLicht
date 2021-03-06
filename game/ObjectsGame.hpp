//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#ifndef		MY_GAME_HPP
# define	MY_GAME_HPP

# include <fstream>
# include <math.h>
# include "Graph.hpp"
# include "ObjectMap.hpp"
# include "PlayerType.hpp"
# include "Sound.hpp"
# include "Creation.hpp"

# define	PATH_TEXTURE_PFIRE	"./assets/material/fire.jpg"
# define	PATH_TEXTURE_PBOMB	"./assets/material/bomb.jpg"
# define	PATH_TEXTURE_PROLLER	"./assets/material/roller.jpg"

class Character;
class Bomb;

class ObjectsGame
{
private:
	std::vector<ObjectMap>	_map;
	graph_content		_graph;
	std::vector<Character>	_character;
	Sound			*_sound;
	std::vector<ObjectMap>	_fire;
	std::vector<ObjectMap>	_bomb;
	std::vector<ObjectMap>	_roller;
public:
	ObjectsGame(graph_content &graph, std::vector<ObjectMap> &map);
	~ObjectsGame();
	std::vector<ObjectMap>	&get_map();
	std::vector<Character>	&get_character();
	graph_content		&get_graph();
	void			checkBombs();
	bool			checkBombsHere(std::vector<irr::f32> &pos);
	void			createCharacter(std::vector<irr::f32> pos, player_type_e PlayerType, graph_content &graph);
	void			moveCharacters();
	void			print_winner(graph_content &graph);
	bool			charactere_alive();
	void			explosionOfBomb(Bomb &bomb);
	void			explosionOfBombDirection(Bomb &bomb, int xDir, int zDir);
	void			killPlayersHere(irr::f32 x, irr::f32 z);
	void			createPlayers();
	void			dropPowerUp(irr::f32 x, irr::f32 z);
	void			dropFire(irr::f32 x, irr::f32 z);
	void			dropBomb(irr::f32 x, irr::f32 z);
	void			dropRoller(irr::f32 x, irr::f32 z);
	void			checkPowerUp(Character &chara, std::vector<ObjectMap> &powerup);
	void			checkCharaIsOnPowerUp();
};

int	render_menu(graph_content &graph, bool is_playing);

#endif		/* !MY_GAME_HPP */
