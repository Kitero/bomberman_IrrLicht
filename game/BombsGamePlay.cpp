//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include "ObjectsGame.hpp"
#include "Bomb.hpp"
#include "Character.hpp"
#include <iostream>

bool	ObjectsGame::checkBombsHere(std::vector<irr::f32> &pos)
{
	std::vector<Bomb>::reverse_iterator		bomb;
	std::vector<Character>::reverse_iterator	chara;
	std::vector<irr::f32>				pos_tmp;
	bool						bombsExist = false;
	for (chara = _character.rbegin(); chara != _character.rend(); chara++) {
		for (bomb = (*chara).getBombs().rbegin(); bomb != (*chara).getBombs().rend(); bomb++) {
			if ((*bomb).getPosition()[0] == pos[0] && (*bomb).getPosition()[1] == pos[1] && (*bomb).getStatus() == READY)
				return false;
		}
	}
	return true;
}
