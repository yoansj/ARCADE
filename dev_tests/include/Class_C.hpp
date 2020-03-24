/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Class_C
*/

#ifndef Class_C_HPP_
#define Class_C_HPP_

#include "IDisplay.hpp"

class Class_C : public IDisplay {
    public:
        Class_C();
        ~Class_C();

        void init() const;
        void stop() const;
        std::string const &getName() const;

    private:
        std::string _name;
};

#endif /* !Class_C_HPP_ */
