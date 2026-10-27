//
// EPITECH PROJECT, 2018
// menu
// File description:
// menu
//

#include "Sound.hpp"
#include "ObjectsGame.hpp"
#include "Init.hpp"
#include "Character.hpp"
#include "KeyPressedEvent.hpp"
#include "SpecBomb.hpp"
#include "driverChoice.h"
#include "stdio.h"
#include "GameClock.hpp"

# define	SPLASH_UBI_END		TICKS_TO_SECONDS(120000)
# define	SPLASH_WINDOWS_END	TICKS_TO_SECONDS(170000)

void	start_splash(graph_content &graph)
{
	int	i;
	irr::video::ITexture *ubi;
	irr::video::ITexture *windo;
	ubi = graph.get_driver()->getTexture("./assets/Ubi.jpg");
	windo = graph.get_driver()->getTexture("./assets/Windo95.jpg");
	graph.set_time_count();
	while (graph.get_time(1) < SPLASH_UBI_END && graph.get_device()->run()) {
		i = 255 * graph.get_time(1) / SPLASH_UBI_END;
		graph.get_driver()->draw2DImage(ubi, irr::core::position2d<irr::s32>(0,0),
						irr::core::rect<irr::s32>(0,0,SCREEN_WIDTH,SCREEN_HEIGHT), 0,
						irr::video::SColor(i,255,255,255), true);
		graph.get_smgr()->drawAll();
		graph.get_env()->drawAll();
		graph.get_driver()->endScene();
		graph.wait_next_frame();
	}
	while (graph.get_time(1) < SPLASH_WINDOWS_END && graph.get_device()->run()) {
		i = 255 * (graph.get_time(1) - SPLASH_UBI_END) / (SPLASH_WINDOWS_END - SPLASH_UBI_END);
		graph.get_driver()->draw2DImage(windo, irr::core::position2d<irr::s32>(0,0),
						irr::core::rect<irr::s32>(0,0,SCREEN_WIDTH,SCREEN_HEIGHT), 0,
						irr::video::SColor(i,255,255,255), true);
		graph.get_smgr()->drawAll();
		graph.get_env()->drawAll();
		graph.get_driver()->endScene();
		graph.wait_next_frame();
	}
}

int	render_menu(graph_content &graph, bool is_playing)
{
	bool	play = 1;
	irr::video::ITexture *images;
	irr::video::ITexture *exit;
	irr::video::ITexture *p_button;
	exit = graph.get_driver()->getTexture("./assets/exit.jpg");
	p_button = graph.get_driver()->getTexture("./assets/play.jpg");
	if (is_playing == 1) {
		start_splash(graph);
		images = graph.get_driver()->getTexture("./assets/Menu.jpg");
	}
	else
		images = graph.get_driver()->getTexture("./assets/black_imae.jpg");
	while (graph.get_device()->run()) {
		if (graph.get_EventRe()->IsKeyDown(irr::KEY_UP))
			play = 1;
		if (graph.get_EventRe()->IsKeyDown(irr::KEY_DOWN))
			play = 0;
		if (graph.get_EventRe()->IsKeyDown(irr::KEY_RETURN)) {
			if (play == 1)
				return (0);
			else
				return (84);
		}
		if (is_playing == 1)
			graph.get_driver()->draw2DImage(images, irr::core::position2d<irr::s32>(0,0),
							irr::core::rect<irr::s32>(0,0,SCREEN_WIDTH,SCREEN_HEIGHT), 0,
							irr::video::SColor(255,255,255,255), true);
		else
			graph.get_driver()->draw2DImage(images, irr::core::position2d<irr::s32>(0,0),
							irr::core::rect<irr::s32>(0,0,SCREEN_WIDTH, SCREEN_HEIGHT), 0,
							irr::video::SColor(255,255,255,255), true);
		if (play == 1) {
			graph.get_driver()->draw2DImage(p_button, irr::core::position2d<irr::s32>(1200,500),
							irr::core::rect<irr::s32>(0,0,500,200), 0,
							irr::video::SColor(255,255,255,255), true);
			graph.get_driver()->draw2DImage(exit, irr::core::position2d<irr::s32>(1200,700),
							irr::core::rect<irr::s32>(0,0,500,500), 0,
							irr::video::SColor(180,255,255,255), true);
		}
		else {
			graph.get_driver()->draw2DImage(p_button, irr::core::position2d<irr::s32>(1200,500),
							irr::core::rect<irr::s32>(0,0,500,200), 0,
							irr::video::SColor(180,255,255,255), true);
			graph.get_driver()->draw2DImage(exit, irr::core::position2d<irr::s32>(1200,700),
							irr::core::rect<irr::s32>(0,0,500,500), 0,
							irr::video::SColor(255,255,255,255), true);
		}
		graph.get_smgr()->drawAll();
		graph.get_env()->drawAll();
		graph.get_driver()->endScene();
		graph.wait_next_frame();
	}
	return (84);
}
