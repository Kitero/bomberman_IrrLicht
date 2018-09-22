/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Sound
*/

#ifndef SOUND_HPP_
	#define SOUND_HPP_

#include <irrKlang.h>

class Sound {
	public:
		Sound();
		~Sound();
                void    explosion();
                void    despacito();
                void    game();
                void    stop();
	private:
                irrklang::ISoundEngine *engine;
};

#endif /* !SOUND_HPP_ */
