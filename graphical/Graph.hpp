//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#ifndef		MY_GRAPH_HPP
# define	MY_GRAPH_HPP

# define	SCREEN_WIDTH		1920
# define	SCREEN_HEIGHT		1080

# include "irrlichtInc.hpp"
# include <ctime>

class MyEventReceiver;

class graph_content
{
private:
	irr::video::IVideoDriver	*_driver;
	irr::scene::ISceneManager	*_smgr;
	irr::gui::IGUIEnvironment	*_guienv;
	irr::IrrlichtDevice		*_device;
	MyEventReceiver			*_receiver;
	double				_time;
public:
	graph_content(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr,
		      irr::gui::IGUIEnvironment *guienv, MyEventReceiver *receiver);
	~graph_content();
	irr::video::IVideoDriver	*get_driver() const;
	irr::scene::ISceneManager	*get_smgr() const;
	irr::gui::IGUIEnvironment	*get_env() const;
	irr::IrrlichtDevice		*get_device() const;
	MyEventReceiver			*get_EventRe();
	void				set_time_count();
	double				get_time(bool t_count);
	void				set_device(irr::IrrlichtDevice *device);
};

#endif		/* !MY_GRAPH_HPP */
