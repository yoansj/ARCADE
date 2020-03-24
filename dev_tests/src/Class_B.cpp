/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Class_B
*/

#include "Class_B.hpp"

Class_B::Class_B() : _name("Class_B")
{ }

Class_B::~Class_B()
{ }

void Class_B::init() const
{
    std::cout << "Init Class_B" << std::endl;
}

void Class_B::stop() const
{
    std::cout << "Stop Class_B" << std::endl;
}

std::string const &Class_B::getName() const
{
    return (_name);
}

extern "C" {
    std::unique_ptr<Class_B> entryPointB() {
        return (std::make_unique<Class_B>());
    }
}
