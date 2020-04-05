/*
** EPITECH PROJECT, 2020
** OOP_arcade_interface_2019
** File description:
** IGames
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include <iostream>
#include <vector>
#include "Input.hpp"

class IGames {
    public:
        virtual ~IGames() = default;

        virtual void run() = 0;

        virtual void setEvent(std::vector<Arcade::Arcade_key> eventArray) = 0;

        virtual std::vector<std::vector<int>> getMap() const = 0;
        virtual std::map<Arcade::Block_tile, std::string> getSprite() const = 0;
        virtual std::map<Arcade::Block_tile, Arcade::Text> getColor() const = 0;
        virtual std::vector<std::vector<int>> getPlayer() const = 0;
        virtual std::vector<std::vector<int>> getShoot() const = 0;
        virtual int getScore() const = 0;
        virtual bool getState() const = 0;
};

#endif /* !IGAMES_HPP_ */
