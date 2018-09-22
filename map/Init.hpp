/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Init
*/

#ifndef		INIT_HPP_
# define	INIT_HPP_

# include <fstream>
# include <vector>
# include "ObjectMap.hpp"

# define	MAP_FILE	"./map/Maps/Map2.txt"

class Init {
private:
        int                             nbrPlayer;
        std::vector<std::vector<char> >  map;
	std::vector<ObjectMap>		obj_map;
public:
	Init();
	~Init();
	void    get_map();
	void    print_map();
	void    fill_map();
        std::vector<std::vector<char> >	&return_map();
};

#endif /* !INIT_HPP_ */
