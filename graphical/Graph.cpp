//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include <thread>
#include "Graph.hpp"
#include "GameClock.hpp"

#ifdef _WIN32
// Windows sleeps have a ~15.6 ms granularity by default: too coarse for MAX_FPS.
extern "C" __declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int period);
#endif

graph_content::graph_content(irr::video::IVideoDriver *driver,
			     irr::scene::ISceneManager *smgr,
			     irr::gui::IGUIEnvironment *guienv, MyEventReceiver *receiver)
{
	_driver = driver;
	_smgr = smgr;
	_guienv = guienv;
	_receiver = receiver;
	_time = game_clock();
#ifdef _WIN32
	timeBeginPeriod(1);
#endif
}

graph_content::~graph_content()
{
}

void	graph_content::set_time_count()
{
	_time = game_clock();
}

double	graph_content::get_time(bool t_count)
{
	if (t_count == 1)
		return (game_clock() - _time);
	return (game_clock());
}

void	graph_content::wait_next_frame()
{
	const std::chrono::steady_clock::time_point	now = std::chrono::steady_clock::now();

	// Running late: start again from now instead of rushing to catch up
	if (_nextFrame < now)
		_nextFrame = now;
	std::this_thread::sleep_until(_nextFrame);
	_nextFrame += std::chrono::microseconds(1000000 / MAX_FPS);
}

irr::video::IVideoDriver	*graph_content::get_driver() const
{
	return _driver;
}

irr::scene::ISceneManager	*graph_content::get_smgr() const
{
	return _smgr;
}

irr::gui::IGUIEnvironment	*graph_content::get_env() const
{
	return _guienv;
}

irr::IrrlichtDevice	*graph_content::get_device() const
{
	return _device;
}

MyEventReceiver		*graph_content::get_EventRe()
{
	return (_receiver);
}

void	graph_content::set_device(irr::IrrlichtDevice *device)
{
	_device = device;
}
