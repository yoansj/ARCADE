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
#include "Input.hpp"

class IGraphics {
    public:
        ~IGraphics() = default;

        virtual bool start() = 0;
        virtual bool run() = 0;
        virtual bool close() = 0;

        virtual std::vector<ArcadeKey> getEvent() const = 0;
};

#endif /* !IGRAPHICS_HPP_ */
