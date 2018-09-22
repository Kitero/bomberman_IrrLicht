/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Init
*/

#include <iostream>
#include <random>
#include "Init.hpp"

Init::Init()
{
        get_map();
        fill_map();
        print_map();
}

Init::~Init()
{
}

void    Init::print_map()
{
        int i = 0;
        int y = 0;

        while (i <= 16) {
                y = 0;
                while (y <= 15) {
			std::cout << map[i][y];
                        y++;
                }
                std::cout << std::endl;
                i++;
        }
}

void    Init::fill_map()
{
        int i = 0;
        int y = 0;
        std::random_device      rd;
        std::mt19937            mt(rd());
        std::uniform_int_distribution<int> dist(1, 11);

        while (i <= 16) {
                y = 0;
                while (y <= 15) {
                        if (dist(mt) >= 8 && map[i][y] == 'o')
                                map[i][y] = '.';
                        y++;
                }
                i++;
        }
}

void    Init::get_map()
{
        std::ifstream   file;
        char            c;
        int             i = 0;

        map.push_back(std::vector<char>());
        file.open(MAP_FILE);
        if (file){
                while (file.get(c)) {
                        if (c != '\n')
                                this->map[i].push_back(c);
                        else {
                                i += 1;
                                map.push_back(std::vector<char>());
                        }
                                
                }
        } else {
                std::cerr << "Error: Cannot open file ." << std::endl;
                exit(84);
        }
        file.close();
}

std::vector<std::vector<char> >	&Init::return_map()
{
	return map;
}
