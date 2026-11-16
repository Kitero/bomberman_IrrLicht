/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Sound
*/

#include <iostream>
#include "miniaudio.h"
#include "Sound.hpp"

struct SoundEngine {
        ma_engine       engine;
        ma_sound        music;
        bool            hasMusic;
};

Sound::Sound()
{
        engine = new SoundEngine();
        engine->hasMusic = false;
        // No audio device is not fatal: the game just runs silently.
        if (ma_engine_init(NULL, &engine->engine) != MA_SUCCESS) {
                std::cerr << "Sound: no audio device, sound disabled" << std::endl;
                delete engine;
                engine = NULL;
        }
}

Sound::~Sound()
{
        if (!engine)
                return;
        stop();
        ma_engine_uninit(&engine->engine);
        delete engine;
}

void    Sound::explosion()
{
        if (engine)
                ma_engine_play_sound(&engine->engine, "sound/explosion.wav", NULL);
}

void    Sound::game()
{
        playMusic("sound/game.ogg");
}

void    Sound::stop()
{
        if (!engine || !engine->hasMusic)
                return;
        ma_sound_uninit(&engine->music);
        engine->hasMusic = false;
}

void    Sound::despacito()
{
        playMusic("sound/despacito.ogg");
}

void    Sound::playMusic(const char *path)
{
        if (!engine)
                return;
        stop();
        if (ma_sound_init_from_file(&engine->engine, path, MA_SOUND_FLAG_STREAM,
                                    NULL, NULL, &engine->music) != MA_SUCCESS) {
                std::cerr << "Sound: cannot load " << path << std::endl;
                return;
        }
        engine->hasMusic = true;
        ma_sound_set_looping(&engine->music, MA_TRUE);
        ma_sound_start(&engine->music);
}
