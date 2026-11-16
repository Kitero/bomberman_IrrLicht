/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Sound
*/

#ifndef SOUND_HPP_
	#define SOUND_HPP_

// miniaudio types stay in Sound.cpp: its header is too heavy to spread.
struct SoundEngine;

class Sound {
	public:
		Sound();
		~Sound();
                void    explosion();
                void    despacito();
                void    game();
                void    stop();
	private:
                void    playMusic(const char *path);

                SoundEngine *engine;
};

#endif /* !SOUND_HPP_ */
