//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include "Graph.hpp"

graph_content::graph_content(irr::video::IVideoDriver *driver,
			     irr::scene::ISceneManager *smgr,
			     irr::gui::IGUIEnvironment *guienv, MyEventReceiver *receiver)
{
	_driver = driver;
	_smgr = smgr;
	_guienv = guienv;
	_receiver = receiver;
}

graph_content::~graph_content()
{
}

void	graph_content::set_time_count()
{
	_time = (double)clock();
}

double	graph_content::get_time(bool t_count)
{
	if (t_count == 1)
		return ((((double)clock()) - _time));
	return (((double)clock()));
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
