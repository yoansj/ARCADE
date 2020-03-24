/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Class_A
*/

#ifndef CLASS_A_HPP_
#define CLASS_A_HPP_

#include "IDisplay.hpp"

class Class_A : public IDisplay {
    public:
        Class_A();
        ~Class_A();

        void init() const;
        void stop() const;
        std::string const &getName() const;

    private:
        std::string _name;
};

#endif /* !CLASS_A_HPP_ */
