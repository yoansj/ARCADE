/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include <iostream>
#include <memory>

class IDisplay {
    public:
        ~IDisplay() = default;

        virtual void init() const = 0;
        virtual void stop() const = 0;
        virtual std::string const &getName() const = 0;
};

#endif /* !IDISPLAY_HPP_ */
