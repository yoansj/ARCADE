/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Class_C
*/

#include "Class_C.hpp"

Class_C::Class_C() : _name("Class_C")
{ }

Class_C::~Class_C()
{ }

void Class_C::init() const
{
    std::cout << "Init Class_C" << std::endl;
}

void Class_C::stop() const
{
    std::cout << "Stop Class_C" << std::endl;
}

std::string const &Class_C::getName() const
{
    return (_name);
}

extern "C" {
    std::unique_ptr<Class_C> entryPointC() {
        return (std::make_unique<Class_C>());
    }
}
