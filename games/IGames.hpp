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
        ~IGames() = default;

        virtual void start() = 0;
        virtual void run() = 0;
        virtual void close() = 0;

        virtual void setEvent(std::vector<ArcadeKey> eventArray) = 0;
};

#endif /* !IGAMES_HPP_ */
