/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <ncurses.h>
#include <iostream>
#include <memory>
#include "IGraphics.hpp"
#include "Input.hpp"

namespace Arcade {

    const std::map<int, Arcade::Arcade_key> ncurses_binding{
        {KEY_UP, Arcade::UP}, {KEY_DOWN, Arcade::DOWN},
        {KEY_LEFT, Arcade::LEFT}, {KEY_RIGHT, Arcade::RIGHT},
        {27, Arcade::QUIT}, {'m', Arcade::MENU},
        {' ', Arcade::USE}, {'p', Arcade::PAUSE},
        {'a', Arcade::NEXT_LIB}, {'q', Arcade::PREVIOUS_LIB},
        {'z', Arcade::NEXT_GAME}, {'s', Arcade::PREVIOUS_GAME}, {'r', Arcade::RESTART}
    };

    class Ncurses : public IGraphics {
        public:
            Ncurses();
            ~Ncurses();

            void printMenu(std::vector<std::string> graphs, std::vector<std::string> games);
            void printLose(int score, std::string name);
            void printMap(std::vector<std::vector<int>> map);
            void printShoot(std::vector<std::vector<int>>);
            void printUI(int score, std::string name);

            void clearScreen() { clear(); };
            void refreshScreen() { refresh(); };

            void setSprite(__attribute__((unused)) std::map<Arcade::Block_tile, std::string>) { };
            void setColor(std::map<Arcade::Block_tile, Arcade::Text> color) { _color = color; };

            std::vector<Arcade::Arcade_key> getEvent() const;

            void printPlayer(std::vector<std::vector<int>>);

        private:
            WINDOW *_main;
            std::size_t _w;
            std::size_t _h;
            std::map<Arcade::Block_tile, Arcade::Text> _color;
            std::pair<int, int> _map_s;

            void printString(std::string str, int x, int y, std::vector<int> c, std::vector<int> bc, int type) const;
            int getColor(std::vector<int> c) const;
    };
}

#endif /* !NCURSES_HPP_ */
