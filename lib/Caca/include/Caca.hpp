/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Caca
*/

#ifndef CACA_HPP_
#define CACA_HPP_

#include <caca.h>
#include <iostream>
#include <memory>
#include "IGraphics.hpp"
#include "Input.hpp"
#include "GraphicError.hpp"
#include <random>

namespace Arcade {

    const std::map<int, Arcade::Arcade_key> caca_binding {
        {CACA_KEY_UP, Arcade::UP}, {CACA_KEY_DOWN, Arcade::DOWN},
        {CACA_KEY_LEFT, Arcade::LEFT}, {CACA_KEY_RIGHT, Arcade::RIGHT},
        {CACA_KEY_ESCAPE, Arcade::QUIT}, {'m', Arcade::MENU},
        {' ', Arcade::USE}, {'p', Arcade::PAUSE}, {'b', Arcade_key::NEXT_LIB},
        {'a', Arcade::NEXT_LIB}, {'q', Arcade::PREVIOUS_LIB},
        {'z', Arcade::NEXT_GAME}, {'s', Arcade::PREVIOUS_GAME}, {'r', Arcade::RESTART}
    };

class Caca : public IGraphics {
    public:
        Caca();
        ~Caca();

        void printMap(std::vector<std::vector<int>> map);
        void printLose(int score, std::string name);
        void printMenu(std::vector<std::string> libGraph, std::vector<std::string> libGame);
        void printShoot(std::vector<std::vector<int>>);

        void clearScreen() {caca_clear_canvas(_canvas);};
        void refreshScreen() {caca_refresh_display(_main);};

        void setSprite(std::map<Arcade::Block_tile, std::string>) { };
        void setColor(std::map<Arcade::Block_tile, Arcade::Text> color) { _color = color; };

        std::vector<Arcade::Arcade_key> getEvent() const;
        void printPlayer(std::vector<std::vector<int>>);
        void printUI(int score, std::string name);

    private:
        uint8_t getColor(std::vector<int> c) const;
        void printString(std::string str, int x, int y, std::vector<int> c, std::vector<int> bc) const;
        void initMap();

        caca_canvas_t *_canvas;
        caca_display_t *_main;
        caca_event_t *_events;
        int _height;
        int _width;
        std::vector<std::string> _map;
        std::map<Arcade::Block_tile, Arcade::Text> _color;
        std::pair<int, int> _map_s;
};

}
#endif /* !CACA_HPP_ */
