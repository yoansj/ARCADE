/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Class_A
*/

#include "Class_A.hpp"

Class_A::Class_A() : _name("Class_A")
{ }

Class_A::~Class_A()
{ }

void Class_A::init() const
{
    std::cout << "Init Class_A" << std::endl;
}

void Class_A::stop() const
{
    std::cout << "Stop Class_A" << std::endl;
}

std::string const &Class_A::getName() const
{
    return (_name);
}

extern "C" {
    std::unique_ptr<Class_A> entryPointA() {
        return (std::make_unique<Class_A>());
    }
}
