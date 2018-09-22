#!/bin/sh
## EPITECH PROJECT, 2018
## 
## File description:
## 
##

BCYAN='\033[1;36m'
WHITE="\033[1;37m"
RED="\033[0;31m"
GREEN="\033[0;32m"
NOC="\033[0m"
printf "${BCYAN}Processing installation...\nPlease wait.${NOC}\n"
cd build
rm -rf build/CMakeFiles build/CMakeCache.txt build/cmake_install.cmake build/Makefile
cmake ./
make
if [ $? == 0 ]
then
    cd ..
    printf "${WHITE}Installation [$GREEN successfull$WHITE ].\n"
    exit 0
fi
if [ $? != 0 ]
then
    cd ..
    printf "${WHITE} Installation [$RED failed$WHITE ].\n"
    exit 84
fi
