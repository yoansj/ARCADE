/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sfml
*/

#include "Sfml.hpp"

Arcade::Sfml::Sfml() : _window(std::make_unique<sf::RenderWindow>(sf::VideoMode(16 * 25, 800), "Arcade", sf::Style::Titlebar | sf::Style::Close))
{
    _window->setFramerateLimit(60);
}

void Arcade::Sfml::setSprite(std::map<Arcade::Block_tile, std::string> resource)
{
    sf::Texture tmpTexture;

    _resource.clear();
    for (auto it = resource.begin(); it != resource.end(); it++) {
        if (!tmpTexture.loadFromFile(it->second))
            throw(GraphicError("Texture not loaded", "setSprite"));
        _resource.insert({it->first, tmpTexture});
    }
}

Arcade::Sfml::~Sfml()
{
}

void Arcade::Sfml::drawText(sf::String text, sf::Font font, float y, sf::Color color)
{
    sf::Text tmpText(text, font, 12);

    tmpText.setPosition((_window->getSize().x / 2) - (tmpText.getLocalBounds().width / 2), y);
    tmpText.setFillColor(color);
    _window->draw(tmpText);
}

void Arcade::Sfml::printMenu(std::vector<std::string> libraries, std::vector<std::string> games)
{
    sf::Font font;
    float verticalPos = 50;

    font.loadFromFile("games/font/retro.ttf");
    drawText("Welcome !", font, verticalPos, sf::Color::Blue);
    verticalPos += 75;
    drawText("Select a game :", font, verticalPos, sf::Color::Blue);
    for (auto it = games.begin(); it != games.end(); it++) {
        verticalPos += 50;
        drawText(*it, font, verticalPos, sf::Color::Blue);
    }
    verticalPos += 75;
    drawText("Graphical libraries implemented :", font, verticalPos, sf::Color::Blue);
    for (auto it = libraries.begin(); it != libraries.end(); it++) {
        verticalPos += 50;
        drawText(*it, font, verticalPos, sf::Color::Blue);
    }
    verticalPos += 75;
    drawText("Keys :", font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Movement : Arrow keys", font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Select a game : Space key", font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Previous lib : Q key", font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Next lib : A key", font, verticalPos, sf::Color::Blue);
}

void Arcade::Sfml::printMap(std::vector<std::vector<int>> map)
{
    sf::Sprite sprite;

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            if (_resource.find(static_cast<Arcade::Block_tile>(map[i][j])) != _resource.end()) {
                sprite.setTexture(_resource.find(static_cast<Arcade::Block_tile>(map[i][j]))->second);
                sprite.setPosition(j * 16, i * 16);
                _window->draw(sprite);
            }
        }
    }
}

std::vector<Arcade::Arcade_key> Arcade::Sfml::getEvent() const
{
    std::vector<Arcade::Arcade_key> tmp = { Arcade::NONE };
    sf::Event event;

    while (_window->isOpen() && _window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            tmp.push_back(Arcade::QUIT);
        if (event.type == sf::Event::KeyPressed && (Arcade::sfml_binding.find(event.key.code) != Arcade::sfml_binding.end()))
            tmp.push_back(Arcade::sfml_binding.find(event.key.code)->second);
    }
    return (tmp);
}

void Arcade::Sfml::printPlayer(std::vector<std::vector<int>> player)
{
    sf::Sprite sprite;

    for (auto it = player.begin(); it != player.end(); it++) {
        if (it == player.begin()) {
            sprite.setTexture(_resource.find(Arcade::Block_tile::PLAYER_HEAD)->second);
            sprite.setPosition((*it)[0] * 16, (*it)[1] * 16);
            _window->draw(sprite);
            continue;
        }
        sprite.setTexture(_resource.find(Arcade::Block_tile::PLAYER)->second);
        sprite.setPosition((*it)[0] * 16, (*it)[1] * 16);
        _window->draw(sprite);
    }
}

void Arcade::Sfml::printShoot(std::vector<std::vector<int>> shoot)
{
    sf::Sprite sprite;

    if (_resource.find(Arcade::SHOOT) == _resource.end())
        return;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            if (shoot[i][j] == Arcade::SHOOT) {
                sprite.setTexture(_resource.find(Arcade::SHOOT)->second);
                sprite.setPosition(j * 16, i * 16);
                _window->draw(sprite);
            }
        }
    }
}


void Arcade::Sfml::printUI(int score, std::string name)
{
    sf::Font font;
    float verticalPos = 415;

    font.loadFromFile("games/font/retro.ttf");
    drawText("Player : " + name + "   Score : " + std::to_string(score), font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Keys :", font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Movement : Arrow keys", font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Interaction : Space key", font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Pause : P   Restart : R", font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Menu : M   Quit : ESC", font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Previous lib : Q   Next lib : A", font, verticalPos, sf::Color::Blue);
    verticalPos += 50;
    drawText("Previous game : S  Next game : Z", font, verticalPos, sf::Color::Blue);
}

void Arcade::Sfml::printLose(int score, std::string name)
{
    sf::Font font;
    float verticalPos = 250;

    font.loadFromFile("games/font/retro.ttf");
    drawText("Game Over", font, verticalPos, sf::Color::Blue);
    verticalPos += 100;
    drawText(name + ", You lost !", font, verticalPos, sf::Color::Blue);
    verticalPos += 100;
    drawText("Your score : " + std::to_string(score), font, verticalPos, sf::Color::Blue);
    verticalPos += 100;
    drawText("Press the space key\n\nto return to the menu", font, verticalPos, sf::Color::Blue);
}

extern "C" {
    std::unique_ptr<Arcade::Sfml> factory() {
        return (std::make_unique<Arcade::Sfml>());
    }
    int magic() {
        return (0xC + 0xA * 0xCA);
    }
}