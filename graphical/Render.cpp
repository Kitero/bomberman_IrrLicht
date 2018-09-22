//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include "Init.hpp"
#include "ObjectsGame.hpp"
#include "Character.hpp"
#include "SpecBomb.hpp"
#include "Creation.hpp"
#include "Graph.hpp"
#include "KeyPressedEvent.hpp"
#include "Sound.hpp"

int	render(graph_content &graph)
{
	Init					load_map;
	Creation				map(load_map.return_map(), graph);
	ObjectsGame				obj_game(graph, map.get_map());

	obj_game.createPlayers();
	while (graph.get_device()->run() && obj_game.charactere_alive() == 1) {
		graph.set_time_count();
		if (graph.get_time(1) < 300);
		obj_game.moveCharacters();
		obj_game.checkBombs();
		obj_game.checkCharaIsOnPowerUp();
		graph.get_driver()->beginScene(true, true, irr::video::SColor(255, 0, 100, 200));
		graph.get_smgr()->drawAll();
		graph.get_env()->drawAll();
		graph.get_driver()->endScene();
	}
	if (obj_game.charactere_alive() == 0)
		obj_game.print_winner(graph);
	graph.get_device()->drop();
	return 0;
}

irr::scene::IAnimatedMeshSceneNode      *create_props(std::string path, graph_content &graph)
{
	irr::scene::IAnimatedMesh       *mesh = graph.get_smgr()->getMesh(path.c_str());
	if (!mesh) {
		graph.get_device()->drop();
		return NULL;
	}
	irr::scene::IAnimatedMeshSceneNode      *node = graph.get_smgr()->addAnimatedMeshSceneNode(mesh);
	if (node)
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	return node;
}

int	main()
{
	Sound	*sound = new Sound();
	MyEventReceiver		receiver;
	irr::IrrlichtDevice	*device = irr::createDevice(irr::video::EDT_OPENGL,
							    irr::core::dimension2d<irr::u32>(SCREEN_WIDTH, SCREEN_HEIGHT),
							    32, false, false, false, &receiver);
	if (!device)
		return 84;
	device->setWindowCaption(L"Bomberman !");
	irr::video::IVideoDriver	*driver = device->getVideoDriver();
	irr::scene::ISceneManager	*smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment	*guienv = device->getGUIEnvironment();
	graph_content			graph(driver, smgr, guienv, &receiver);
	graph.set_device(device);
	device->getCursorControl()->setVisible(false);
	irr::scene::ICameraSceneNode	*camera =
		smgr->addCameraSceneNode(0, irr::core::vector3df(80, 430, 330),
					 irr::core::vector3df(280, -100, 330));
	camera->setFarValue(5000.0f);
	sound->despacito();
	if (render_menu(graph, 1) == 84)
		return (84);
	else {
		sound->stop();
		if (render(graph) == 84)
			return 84;
	}
	return 0;
}
