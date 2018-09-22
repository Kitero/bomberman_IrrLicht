//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include <iostream>
#include "Init.hpp"
#include "ObjectsGame.hpp"
#include "Character.hpp"
#include "SpecBomb.hpp"
#include "Creation.hpp"
#include "Graph.hpp"
#include "KeyPressedEvent.hpp"
#include "Sound.hpp"
#include "Bomb.hpp"

ObjectsGame::ObjectsGame(graph_content &graph, std::vector<ObjectMap> &map)
	:_map(map),
	 _graph(graph)
{
	_sound = new Sound();
	_sound->game();
}

ObjectsGame::~ObjectsGame()
{
}

std::vector<ObjectMap>	&ObjectsGame::get_map()
{
	return _map;
}

std::vector<Character>	&ObjectsGame::get_character()
{
	return _character;
}

graph_content		&ObjectsGame::get_graph()
{
	return _graph;
}

void	ObjectsGame::killPlayersHere(irr::f32 z, irr::f32 x)
{
	std::vector<Character>::iterator	chara = _character.end();
	while (chara != _character.begin()) {
		chara--;
		if (((*chara).getPosition()[0] + SIZE_CHARA / 2)
		    - fmod(((*chara).getPosition()[0] + SIZE_CHARA / 2), SIZE_BLOCK) == z
		    && ((*chara).getPosition()[1] + SIZE_CHARA / 2)
		    - fmod(((*chara).getPosition()[1] + SIZE_CHARA / 2), SIZE_BLOCK) == x) {
			(*chara).die();
		}
	}
}

void	ObjectsGame::checkPowerUp(Character &chara, std::vector<ObjectMap> &powerup)
{
	std::vector<ObjectMap>::reverse_iterator	powerit;
	for (powerit = powerup.rbegin(); powerit != powerup.rend(); powerit++)
		if (chara.getPosition()[0] + SIZE_CHARA / 2 >= (*powerit).get_pos().X
		    && chara.getPosition()[0] + SIZE_CHARA / 2 <= (*powerit).get_pos().X + SIZE_BLOCK
		    && chara.getPosition()[1] + SIZE_CHARA / 2 >= (*powerit).get_pos().Z
		    && chara.getPosition()[1] + SIZE_CHARA / 2 <= (*powerit).get_pos().Z + SIZE_BLOCK) {
			if ((*powerit).get_type() == FIRE)
				chara.setRange(chara.getRange() + 1);
			if ((*powerit).get_type() == BOMB)
				chara.setMaxBomb(chara.getMaxBomb() + 1);
			if ((*powerit).get_type() == ROLLER)
				chara.setSpeed(chara.getSpeed() + 1);
			(*powerit).hide();
		}
		
}

void	ObjectsGame::checkCharaIsOnPowerUp()
{
	std::vector<Character>::reverse_iterator	chara = _character.rbegin();
	while (chara != _character.rend()) {
		checkPowerUp(*chara, _fire);
		checkPowerUp(*chara, _bomb);
		checkPowerUp(*chara, _roller);
		chara++;
	}
}

void	ObjectsGame::dropFire(irr::f32 x, irr::f32 z)
{
	irr::core::vector3df pos(x, 0.01, z);
	ObjectMap	obj;
	irr::scene::IAnimatedMeshSceneNode	*node = create_props(PATH_GROUND, _graph);
	obj.set_node(node);
	irr::core::vector3df scale(SCALE_GROUND, SCALE_GROUND, SCALE_GROUND);
	obj.set_texture(0, PATH_TEXTURE_PFIRE, _graph.get_driver());
	obj.set_scale(scale);
	obj.set_pos(pos);
	obj.set_type(FIRE);
	_fire.insert(_fire.begin(), obj);
}

void	ObjectsGame::dropBomb(irr::f32 x, irr::f32 z)
{
	irr::core::vector3df pos(x, 0.01, z);
	ObjectMap	obj;
	irr::scene::IAnimatedMeshSceneNode	*node = create_props(PATH_GROUND, _graph);
	obj.set_node(node);
	irr::core::vector3df scale(SCALE_GROUND, SCALE_GROUND, SCALE_GROUND);
	obj.set_texture(0, PATH_TEXTURE_PBOMB, _graph.get_driver());
	obj.set_scale(scale);
	obj.set_pos(pos);
	obj.set_type(BOMB);
	_bomb.insert(_bomb.begin(), obj);
}

void	ObjectsGame::dropRoller(irr::f32 x, irr::f32 z)
{
	irr::core::vector3df pos(x, 0.01, z);
	ObjectMap	obj;
	irr::scene::IAnimatedMeshSceneNode	*node = create_props(PATH_GROUND, _graph);
	obj.set_node(node);
	irr::core::vector3df scale(SCALE_GROUND, SCALE_GROUND, SCALE_GROUND);
	obj.set_texture(0, PATH_TEXTURE_PROLLER, _graph.get_driver());
	obj.set_scale(scale);
	obj.set_pos(pos);
	obj.set_type(ROLLER);
	_roller.insert(_roller.begin(), obj);
}

void	ObjectsGame::dropPowerUp(irr::f32 x, irr::f32 z)
{
	std::random_device rd;
	std::mt19937		mt(rd());
	std::uniform_int_distribution<int> dist(1, 11);
	
	int	roll = dist(mt);
	if (roll == 2)
		dropFire(x, z);
	else if (roll == 3)
		dropBomb(x, z);
	else if (roll == 4)
		dropRoller(x, z);
}

void	ObjectsGame::explosionOfBombDirection(Bomb &bomb, int xDir, int zDir)
{
	int	i = 0;
	std::vector<ObjectMap>::iterator	tile = _map.begin();
	while (i < bomb.getRange()) {
		tile = _map.begin();
		while (tile != _map.end()) {
			if ((*tile).get_pos().X == bomb.getPosition()[0] + (SIZE_BLOCK * i * xDir)
			    && (*tile).get_pos().Z == bomb.getPosition()[1] + (SIZE_BLOCK * i * zDir)) {
				killPlayersHere((*tile).get_pos().X, (*tile).get_pos().Z);
				if ((*tile).getType() == DESTRUCT_BLK) {
					dropPowerUp((*tile).get_pos().X, (*tile).get_pos().Z);
					bomb.createExplosionBlock(_graph, (*tile).get_pos().X, (*tile).get_pos().Z);
					(*tile).hide();
					return;
				}
				else if ((*tile).getType() == INDESTRUCT_BLK)
					return;
				bomb.createExplosionBlock(_graph, (*tile).get_pos().X, (*tile).get_pos().Z);
			}
			tile++;
		}
		i++;
	}
}


void	ObjectsGame::explosionOfBomb(Bomb &bomb)
{
	_sound->explosion();
	explosionOfBombDirection(bomb, 1, 0);
	explosionOfBombDirection(bomb, -1, 0);
	explosionOfBombDirection(bomb, 0, 1);
	explosionOfBombDirection(bomb, 0, -1);
	std::vector<irr::f32>	pos;
	pos.insert(pos.begin(), -100);
	pos.insert(pos.begin(), -100);
	bomb.setPosition(pos);
}

void	ObjectsGame::checkBombs()
{
	std::vector<Bomb>::reverse_iterator		bomb;
	std::vector<Character>::reverse_iterator	chara;
	for (chara = _character.rbegin(); chara != _character.rend(); chara++) {
		for (bomb = (*chara).getBombs().rbegin(); bomb != (*chara).getBombs().rend(); bomb++) {
			if ((*bomb).getStatus() == READY) {	
				if ((*bomb).explosion() == true) {
					explosionOfBomb((*bomb));
					(*chara).bombExplosed();
				}
			}
			else
				(*bomb).explosionIsFinished();
		}
	}
}

void	ObjectsGame::createCharacter(std::vector<irr::f32> pos, player_type_e playerType, graph_content &graph)
{
	Character	chara(pos, playerType, graph);
	_character.insert(_character.begin(), chara);
}

void	ObjectsGame::print_winner(graph_content &graph)
{
	irr::video::ITexture *images;
	std::vector<Character>::reverse_iterator	chara = _character.rbegin();
	int	count = 1;
	while (chara != _character.rend() && ((*chara).getLive() != 1)) {
		count = count + 1;
        	chara++;
	}
	if (count == 1)
		images = graph.get_driver()->getTexture("./assets/Player1win.png");
	else if (count == 2)
		images = graph.get_driver()->getTexture("./assets/Player2win.png");
	else if (count == 3)
		images = graph.get_driver()->getTexture("./assets/Player3win.png");
	else if (count == 4)
		images = graph.get_driver()->getTexture("./assets/Player4win.png");
	else
		images = graph.get_driver()->getTexture("./assets/Alllose.png");
	while(graph.get_time(1) < 220000 && graph.get_device()->run()) {
		graph.get_driver()->draw2DImage(images, irr::core::position2d<irr::s32>(0,0),
						irr::core::rect<irr::s32>(0,0,SCREEN_WIDTH,SCREEN_HEIGHT),
						0,irr::video::SColor(255,255,255,255), true);
		graph.get_smgr()->drawAll();
		graph.get_env()->drawAll();
		graph.get_driver()->endScene();
	}
}

bool	ObjectsGame::charactere_alive()
{
	std::vector<Character>::reverse_iterator	chara = _character.rbegin();
	int						count = 0;
	while (chara != _character.rend()) {
		if ((*chara).getLive() == 1)
			count = count + 1;
		chara++;
	}
	if (count > 1)
		return (true);
	return (false);
}

void	ObjectsGame::moveCharacters()
{
	std::vector<Character>::reverse_iterator	chara = _character.rbegin();
	while (chara != _character.rend()) {
		(*chara).PlayerMove(*this, _graph.get_EventRe());
		chara++;
	}
}

void	ObjectsGame::createPlayers()
{
	std::vector<irr::f32>			pos1;
	std::vector<irr::f32>			pos2;
	std::vector<irr::f32>			pos3;
	std::vector<irr::f32>			pos4;
	pos1.insert(pos1.begin(), 42);
	pos1.insert(pos1.begin(), 42);
	pos2.insert(pos2.begin(), 600);
	pos2.insert(pos2.begin(), 520);
	pos3.insert(pos3.begin(), 42);
	pos3.insert(pos3.begin(), 520);
	pos4.insert(pos4.begin(), 600);
	pos4.insert(pos4.begin(), 42);
	createCharacter(pos1, PLAYER_1, _graph);
	createCharacter(pos2, PLAYER_2, _graph);
	createCharacter(pos3, PLAYER_3, _graph);
	createCharacter(pos4, PLAYER_4, _graph);
}
