/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <vector>
#include <random>
#include <iostream>

#include "IGames.hpp"
#include "Input.hpp"

class Snake : public IGames {
    public:
        Snake();
        ~Snake();

    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class Position {
        public:
            Position(int x = 0, int y = 0) : _x(0), _y(0) {};
            ~Position() = default;

            Position(Position const &cpy) : _x(cpy.getX()), _y(cpy.getY()) {};

            Position &operator=(const Position &other)
            {
                _x = other._x;
                _y = other._y;
                return (*this);
            }

            void setX(int x) {_x = x;};
            void setY(int y) {_y = y;};
            void setXY(int x = 0, int y = 0) {_x = x; _y = y;};

            int getX() const {return (_x);};
            int getY() const {return (_y);};

        private:
            int _x;
            int _y;
    };

    void start() override;
    void run() override;
    void close() override;
    void setEvent(std::vector<ArcadeKey> eventArray) override;

    bool findEvent(ArcadeKey event, std::vector<ArcadeKey> eventArray);

    private:
        int _size;
        int _score;
        int _speed;
        Direction _dir;
        std::vector<Position> _positions;
        Position _fruit;
        bool _paused;
};

#endif /* !SNAKE_HPP_ */
