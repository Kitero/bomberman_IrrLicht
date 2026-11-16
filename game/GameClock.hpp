//
// EPITECH PROJECT, 2018
//
// File description:
// Portable game clock
//

#ifndef		GAME_CLOCK_HPP
# define	GAME_CLOCK_HPP

# include <chrono>

// Wall-clock time in seconds, the same on every platform.
// std::clock() was used before: it counts CPU time in microseconds on Linux
// but wall time in milliseconds on Windows, so every delay was 1000x longer there.
inline double	game_clock()
{
	return std::chrono::duration<double>(
		std::chrono::steady_clock::now().time_since_epoch()).count();
}

// The original delays were written in std::clock() ticks, assuming
// 100000 ticks per second (see SpecBomb::setTimer): convert them to seconds.
# define	TICKS_TO_SECONDS(ticks)	((ticks) / 100000.0)

#endif		/* !GAME_CLOCK_HPP */
