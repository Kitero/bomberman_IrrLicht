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
printf "${BCYAN}Processing uninstall...\nPlease wait.${NOC}\n"
cd build
make clean
rm -rf CMakeFiles CMakeCache.txt Makefile
cd ..
rm bomberman
if [ $? == 0 ]
then
    printf "${WHITE}Uninstall [$GREEN successfull$WHITE ].\n"
    exit 0
fi
if [ $? != 0 ]
then
    printf "${WHITE} Uninstall [$RED failed$WHITE ].\n"
    exit 84
fi
