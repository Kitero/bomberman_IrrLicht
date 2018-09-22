//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#ifndef		SPECBOMB_HPP
# define	SPECBOMB_HPP

# include <vector>
# include "irrlichtInc.hpp"
# include "PlayerType.hpp"

class SpecBomb
{
private:
	bool			_isWallPass;
	size_t			_range;
	std::vector<irr::f32>	_pos;
	size_t			_timer;
	player_type_e		_player;
public:
	SpecBomb();
	~SpecBomb();
	void			setWallPass(bool wallPass);
	void			setRange(size_t range);
	void			setPosition(irr::f32 x, irr::f32 y);
	void			setTimer(double timer);
	void			setPlayerType(player_type_e player);
	bool			getWallPass() const;
	size_t			getRange() const;
	std::vector<irr::f32>	getPosition() const;
	double			getTimer() const;
	player_type_e		getPlayerType() const;
};

#endif		/* !SPECBOMB_HPP */
