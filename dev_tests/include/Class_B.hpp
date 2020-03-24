/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Class_B
*/

#ifndef Class_B_HPP_
#define Class_B_HPP_

#include "IDisplay.hpp"

class Class_B : public IDisplay {
    public:
        Class_B();
        ~Class_B();

        void init() const;
        void stop() const;
        std::string const &getName() const;

    private:
        std::string _name;
};

#endif /* !Class_B_HPP_ */
