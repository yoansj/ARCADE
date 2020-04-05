/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GraphicError
*/

#ifndef GRAPHICERROR_HPP_
#define GRAPHICERROR_HPP_

#include <iostream>

class GraphicError : public std::exception {
    public:
        GraphicError(std::string const &message, std::string const &type) :
            _message(message), _type(type) { };
        ~GraphicError() = default;

        std::string const &getType() const { return _type; };
        char const *what() const noexcept override { return _message.data(); };

    private:
        std::string _message;
        std::string _type;
};

#endif /* !GRAPHICERROR_HPP_ */
