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
        ~Snake() = default;

        enum Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        class Position {
            public:
                Position(int x = 0, int y = 0) : _x(x), _y(y) {};
                ~Position() = default;
                Position(Position const &cpy) : _x(cpy.getX()), _y(cpy.getY()) { };

                Position &operator=(const Position &other)
                {
                    _x = other._x;
                    _y = other._y;
                    return (*this);
                };

                void setX(int x) {_x = x;};
                void setY(int y) {_y = y;};
                void setXY(int x = 0, int y = 0) {_x = x; _y = y;};

                int getX() const {return (_x);};
                int getY() const {return (_y);};

            private:
                int _x;
                int _y;
        };

        void run() override;

        void restart();

        void setEvent(std::vector<Arcade::Arcade_key> eventArray) override;

        std::vector<std::vector<int>> getMap() const { return _map; };
        std::vector<std::vector<int>> getShoot() const { return _shootMap; };
        std::map<Arcade::Block_tile, std::string> getSprite() const { return _sprite; };
        std::map<Arcade::Block_tile, Arcade::Text> getColor() const { return _color; };
        std::vector<std::vector<int>> getPlayer() const;
        int getScore() const {return (_score);};
        bool getState() const { return _isRunning; };

    private:
        int _score;
        Direction _dir;
        Position _fruit;
        std::vector<Position> _positions;
        std::map<Arcade::Block_tile, std::string> _sprite;
        std::map<Arcade::Block_tile, Arcade::Text> _color;
        std::vector<std::vector<int>> _map;
        std::vector<std::vector<int>> _shootMap;
        bool _isRunning;

        static int randomRange(int min, int max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(min, max);
            return (dis(gen));
        }

        bool findEvent(Arcade::Arcade_key event, std::vector<Arcade::Arcade_key> eventArray) const;
};

#endif /* !SNAKE_HPP_ */
