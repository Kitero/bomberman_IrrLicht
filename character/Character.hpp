//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#ifndef	CHARACTER_HPP_
# define CHARACTER_HPP_

# include "ObjectsGame.hpp"

# define	PATH_BOMBERMAN			"./assets/WhiteBomber/WhiteBomber.obj"
# define	SCALE_BOMBERMAN			2
# define	PATH_TEXTURE_BOMBERMAN		"./assets/WhiteBomber/bomberman00.png"
# define	PATH_TEXTURE_BOMBERMAN_FACE	"./assets/WhiteBomber/bom_face01.png"
# define	SIZE_CHARA			35
# define	DEFAULT_SPEED			3
# define	SPRITE_MARGIN			6

class Bomb;
class SpecBomb;

class	Character
{
protected:
	player_type_e			_player_type;
	std::vector<irr::f32>		_pos;
	bool				_live;
	bool				_isWallPass;
	size_t				_speed;
	size_t				_range;
	size_t				_maxBomb;
	size_t				_droppedBombs;
	std::vector<Bomb>		_bomb;
	ObjectMap			_obj;
private:
	void				create_bomberman(graph_content &graph);
public:
	Character(std::vector<irr::f32> pos, player_type_e player_type, graph_content &graph);
	~Character();
	void				setPlayerType(player_type_e player);
	void				setPosition(std::vector<irr::f32> value);
	void				setSpeed(size_t value);
	void				setIsWallPass(bool);
	void				setRange(size_t);
	void				setMaxBomb(size_t);
	void				setLive(bool value);
	bool				getIsWallPass() const;
	size_t				getRange() const;
	size_t				getMaxBomb() const;
	std::vector<irr::f32>		getPosition() const;
	player_type_e			getPlayerType() const;
	size_t				getSpeed() const;
	bool				getLive() const;
	ObjectMap			&getObj();
	std::vector<Bomb>		&getBombs();
	bool				checkThisPos(ObjectMap &obj, irr::f32 x, irr::f32 z) const;
	bool				checkNextPos(std::vector<ObjectMap> &map, std::vector<Character> &chara) const;
	void				move_up(std::vector<ObjectMap> &map, std::vector<Character> &chara);
	void				move_down(std::vector<ObjectMap> &map, std::vector<Character> &chara);
	void				move_left(std::vector<ObjectMap> &map, std::vector<Character> &chara);
	void				move_right(std::vector<ObjectMap> &map, std::vector<Character> &chara);
	void				PlayerMove(ObjectsGame &objGame, MyEventReceiver *evtKey);
	void				ai_movement(ObjectsGame &objGame);
	void				dropBomb(ObjectsGame &obj_game);
	void				Player4Move(ObjectsGame &objGame, MyEventReceiver *evtKey);
	void				Player3Move(ObjectsGame &objGame, MyEventReceiver *evtKey);
	void				Player2Move(ObjectsGame &objGame, MyEventReceiver *evtKey);
	void				Player1Move(ObjectsGame &objGame, MyEventReceiver *evtKey);
	void				rotate(irr::core::vector3df &rotation);
	bool				checkBombsHere(ObjectsGame &objGame);
	bool				bombFreeToDrop(SpecBomb &spec);
	void				bombExplosed();
	void				die();
	bool				isThereBombHere(std::vector<Character> &chara) const;
	bool				checkBombHere(Bomb &bomb, irr::f32 x, irr::f32 z) const;
};

#endif /* !CHARACTER_HPP_ */
