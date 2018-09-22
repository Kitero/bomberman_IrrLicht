/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Sound
*/

#include <iostream>
#include "Sound.hpp"

Sound::Sound()
{
        engine = irrklang::createIrrKlangDevice();
}

Sound::~Sound()
{
        engine->drop();
}

void    Sound::explosion()
{
        engine->play2D("sound/explosion.wav", false);
}

void    Sound::game()
{
        //std::cout <<"game is launched" << std::endl;
        engine->play2D("sound/game.ogg", true);
}

void    Sound::stop()
{
        engine->drop();
}

void    Sound::despacito()
{
        engine->play2D("sound/despacito.ogg", true);
}