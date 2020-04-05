/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** snake
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Snake.hpp"

Snake::Snake() :
    _score(0), _dir(RIGHT),
    _fruit(randomRange(1, 23), randomRange(1, 23)),
    _positions{Position(11, 12), Position(10, 12), Position(9, 12), Position(8, 12)},
    _sprite{{Arcade::VOID, "games/Nibbler/assets/void.png"}, {Arcade::WALL, "games/Nibbler/assets/wall.png"}, {Arcade::ITEM, "games/Nibbler/assets/apple.png"}, {Arcade::PLAYER, "games/Nibbler/assets/snakeBody.png"}, {Arcade::PLAYER_HEAD, "games/Nibbler/assets/snakeHead.png"}},
    _color{
        {Arcade::VOID, Arcade::Text(" ", {255, 255, 255, 0}, {255, 255, 255, 0})},
        {Arcade::WALL, Arcade::Text("X", {0, 0, 0, 0}, {255, 255, 255, 0})},
        {Arcade::ITEM, Arcade::Text(" ", {0, 0, 0, 0}, {255, 0, 0, 0})},
        {Arcade::PLAYER, Arcade::Text(" ", {255, 255, 255, 0}, {0, 255, 0, 0})},
        {Arcade::SHOOT, Arcade::Text("", {0, 0, 0, 0}, {0, 0, 0, 0})},
    },
    _isRunning(true)
{
    _map.push_back({Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL});
    for (int i = 0; i < 23; i++)
        _map.push_back({Arcade::WALL, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::WALL});
    _map.push_back({Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL});
    _map[_fruit.getY()][_fruit.getX()] = Arcade::ITEM;

    /* Init map des tirs */
    _shootMap.push_back({Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID});
    for (int i = 0; i < 23; i++)
        _shootMap.push_back({Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID});
    _shootMap.push_back({Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID});
}

void Snake::restart()
{
    _positions.empty();
    _positions[0].setXY(11, 12);
    _positions[1].setXY(10, 12);
    _positions[2].setXY(9, 12);
    _positions[3].setXY(8, 12);
    _positions.erase(_positions.begin() + 4, _positions.end());
    _map[_fruit.getY()][_fruit.getX()] = Arcade::VOID;
    _fruit = Position(randomRange(1, 23), randomRange(1, 23));
    _map[_fruit.getY()][_fruit.getX()] = Arcade::ITEM;
    _score = 0;
    _dir = RIGHT;
    _isRunning = true;
}

//Appelée à chaque tour de boucle
void Snake::run()
{
    /* Update des positions peut être à mettre dans une fonction membre */
    Position npos = _positions[0];
    if (_dir == UP)
        npos.setY(npos.getY() - 1);
    if (_dir == DOWN)
        npos.setY(npos.getY() + 1);
    if (_dir == RIGHT)
        npos.setX(npos.getX() + 1);
    if (_dir == LEFT)
        npos.setX(npos.getX() - 1);
    _positions.insert(_positions.begin(), npos);

    /* Check collision avec un fruit */
    if (_positions[0].getX() == _fruit.getX() && _positions[0].getY() == _fruit.getY()) {
        _score += 1;

        _map[_fruit.getY()][_fruit.getX()] = Arcade::VOID;
        _fruit = Position(randomRange(1, 23), randomRange(1, 23));
        _map[_fruit.getY()][_fruit.getX()] = Arcade::ITEM;

        for (int i = 0; _positions.begin() + i != _positions.end(); i++) {
            if (_positions[i].getX() == _fruit.getX() && _positions[i].getY() == _fruit.getY()) {
                _map[_fruit.getY()][_fruit.getX()] = Arcade::VOID;
                _fruit = Position(randomRange(1, 23), randomRange(1, 23));
                _map[_fruit.getY()][_fruit.getX()] = Arcade::ITEM;

                i = 0;
            }
        }
    } else
        _positions.pop_back();

    /* Collision avec les limites de la map/écran, à faire ici */
    if (_positions[0].getX() >= 24 || _positions[0].getX() <= 0)
        _isRunning = false;
    if (_positions[0].getY() >= 24 || _positions[0].getY() <= 0)
        _isRunning = false;

    /* Collision avec soi même */
    for (int i = 1; _positions.begin() + i != _positions.end(); i++) {
        if (_positions[0].getX() == _positions[i].getX() && _positions[0].getY() == _positions[i].getY()) {
            _isRunning = false;
            break;
        }
    }
}

//Cherche un event dans un vector d'event
//Renvoie true si l'event est trouvé
bool Snake::findEvent(Arcade::Arcade_key event, std::vector<Arcade::Arcade_key> eventArray) const
{
    for (int i = 0; eventArray.begin() + i != eventArray.end(); i++)
        if (event == eventArray[i]) return (true);
    return (false);
}

//Méthode qui process les event du jeu
void Snake::setEvent(std::vector<Arcade::Arcade_key> eventArray)
{
    if (findEvent(Arcade::RESTART, eventArray) == true) {
        restart();
        return;
    }
    for (Arcade::Arcade_key key : eventArray) {
        if (key == Arcade::Arcade_key::LEFT) {
            if (_dir != RIGHT) _dir = LEFT;
            return;
        }
        if (key == Arcade::Arcade_key::RIGHT) {
            if (_dir != LEFT) _dir = RIGHT;
            return;
        }
        if (key == Arcade::Arcade_key::UP) {
            if (_dir != DOWN) _dir = UP;
            return;
        }
        if (key == Arcade::Arcade_key::DOWN) {
            if (_dir != UP) _dir = DOWN;
            return;
        }
    }
}

std::vector<std::vector<int>> Snake::getPlayer() const
{
    std::vector<std::vector<int>> tmp;

    for (auto it = _positions.begin(); it != _positions.end(); it++)
        tmp.push_back({it->getX(), it->getY()});
    return (tmp);
}

extern "C" {
    std::unique_ptr<Snake> factory() {
        return (std::make_unique<Snake>());
    }

    int magic() {
        return (0xC - 0xA * 0xCA);
    }
}
