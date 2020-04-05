/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Ncurses
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>
#include "IGraphics.hpp"
#include "Input.hpp"
#include "GraphicError.hpp"

namespace Arcade {

    const std::map<int, Arcade::Arcade_key> sfml_binding {
        {sf::Keyboard::Up, Arcade::UP}, {sf::Keyboard::Down, Arcade::DOWN},
        {sf::Keyboard::Left, Arcade::LEFT}, {sf::Keyboard::Right, Arcade::RIGHT},
        {sf::Keyboard::Escape, Arcade::QUIT}, {sf::Keyboard::M, Arcade::MENU},
        {sf::Keyboard::Space, Arcade::USE}, {sf::Keyboard::P, Arcade::PAUSE},
        {sf::Keyboard::A, Arcade::NEXT_LIB}, {sf::Keyboard::Q, Arcade::PREVIOUS_LIB},
        {sf::Keyboard::Z, Arcade::NEXT_GAME}, {sf::Keyboard::S, Arcade::PREVIOUS_GAME}, {sf::Keyboard::R, Arcade::RESTART}
    };

    class Sfml : public IGraphics {
        public:
            Sfml();
            ~Sfml();

            void printMap(std::vector<std::vector<int>> map);

            void printMenu(std::vector<std::string>, std::vector<std::string>);
            void printLose(int score, std::string name);
            void printShoot(std::vector<std::vector<int>>);
            void printUI(int score, std::string name);

            void clearScreen() { _window->clear(sf::Color::Black); };
            void refreshScreen() { _window->display(); };

            void setSprite(std::map<Arcade::Block_tile, std::string>);
            void setColor(std::map<Arcade::Block_tile, Arcade::Text>) { };

            std::vector<Arcade::Arcade_key> getEvent() const;

            void printPlayer(std::vector<std::vector<int>>);

        private:
            void drawText(sf::String text, sf::Font font, float y, sf::Color color);

            std::unique_ptr<sf::RenderWindow> _window;

            sf::Texture _snakeBodyTexture;
            sf::Texture _snakeHeadTexture;

            sf::Sprite _snakeBodySprite;
            sf::Sprite _snakeHeadSprite;

            std::map<Arcade::Block_tile, sf::Texture> _resource;
    };
}

#endif /* !SFML_HPP_ */
