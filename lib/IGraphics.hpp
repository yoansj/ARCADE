/*
** EPITECH PROJECT, 2020
** OOP_arcade_interface_2019
** File description:
** IGraphics
*/

#ifndef IGRAPHICS_HPP_
#define IGRAPHICS_HPP_

#include <iostream>
#include <vector>
#include <map>
#include "Input.hpp"

class IGraphics {
    public:
        virtual ~IGraphics() = default;

        virtual void printMenu(std::vector<std::string> libGraph, std::vector<std::string> libGame) = 0;
        virtual void printLose(int score, std::string name) = 0;
        virtual void printMap(std::vector<std::vector<int>> map) = 0;
        virtual void printShoot(std::vector<std::vector<int>>) = 0;
        virtual void printUI(int score, std::string name) = 0;
        virtual void printPlayer(std::vector<std::vector<int>>) = 0;

        virtual void clearScreen() = 0;
        virtual void refreshScreen() = 0;

        virtual void setSprite(std::map<Arcade::Block_tile, std::string>) = 0;
        virtual void setColor(std::map<Arcade::Block_tile, Arcade::Text>) = 0;

        virtual std::vector<Arcade::Arcade_key> getEvent() const = 0;
};

#endif /* !IGRAPHICS_HPP_ */
