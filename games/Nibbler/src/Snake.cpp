/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** snake
*/

#include "Snake.hpp"

//Cherche un event dans un vector d'event
//Renvoie true si l'event est trouvé
bool Snake::findEvent(ArcadeKey event, std::vector<ArcadeKey> eventArray)
{
    for (int i = 1; eventArray.begin() + i != eventArray.end(); i++)
        if (event == eventArray[i]) return (true);
    return (false);
}

//Méthode qui process les event du jeu
void Snake::setEvent(std::vector<ArcadeKey> eventArray)
{
    if (findEvent(ArcadeKey::PAUSE, eventArray)) _paused = !_paused;
    if (findEvent(ArcadeKey::MENU, eventArray)) {
        std::cout << "Retour au menu de l'arcade" << std::endl;
    }
    if (findEvent(ArcadeKey::QUIT, eventArray)) {
        std::cout << "On quitte l'arcade faut tout free" << std::endl;
    }
    if (findEvent(ArcadeKey::LEFT, eventArray)) {
        if (_dir != RIGHT) _dir = LEFT;
    }
    if (findEvent(ArcadeKey::RIGHT, eventArray)) {
         if (_dir != LEFT) _dir = RIGHT;
    }
    if (findEvent(ArcadeKey::UP, eventArray)) {
        if (_dir != DOWN) _dir = UP;
    }
    if (findEvent(ArcadeKey::DOWN, eventArray)) {
        if (_dir != UP) _dir = DOWN;
    }
}

void Snake::start()
{
}

//Appelée à chaque tour de boucle
void Snake::run()
{
    if (_paused == true) return;

    /* Collision avec les limites de la map/écran, à faire ici */

    /* Collision avec soi même */
    for (int i = 1; _positions.begin() + i != _positions.end(); i++) {
        if (_positions[0].getX() == _positions[i].getX() && _positions[0].getY() == _positions[i].getY())
            std::cout << "T'es mort" << std::endl; //Ligne de collusion avec soi même à changer
    }

    /* Check collision avec un fruit */
    if (_positions[0].getX() && _positions[0].getY() == _fruit.getX() && _fruit.getY()) {
        _score += 1;
        _size += 1;
        _fruit = Position(std::rand() % 42, std::rand() % 42); //tp le fruit ligne à changer en prenant en compte la taille de l'écran
        _positions.push_back(Position(_positions[_positions.size() - 1]));

        for (int i = 0; _positions.begin() + i != _positions.end(); i++)
        {
            if (_positions[i].getX() == _fruit.getX() && _positions[i].getY() == _fruit.getY()) {
                _fruit = Position(std::rand() % 42, std::rand() % 42);
                i = 0;
            }
        }
    }

    /* Update des positions peut être à mettre dans une fonction membre */
    if (_dir == UP) _positions[0].setY(_positions[0].getY() - _speed);
    if (_dir == DOWN) _positions[0].setY(_positions[0].getY() + _speed);
    if (_dir == RIGHT) _positions[0].setX(_positions[0].getX() + _speed);
    if (_dir == LEFT) _positions[0].setX(_positions[0].getX() - _speed);

    Position prev(_positions[0].getX(), _positions[0].getY());
    Position pprev = _positions[1];
    for (int i = 1; _positions.begin() + i != _positions.end(); i++) {
        pprev = _positions[i];
        _positions[i] = prev;
        prev = pprev;
    }
}

void Snake::close()
{
}

Snake::Snake() : _size(4), _score(0), _speed(1), _dir((Direction)(std::rand() % 4)), _fruit(std::rand() % 42, std::rand() % 42), _paused(false)
{
    Position s(3, 0);
    Position sa(2, 0);
    Position sah(1, 0);
    Position sahh(0, 0);

    _positions.push_back(s);
    _positions.push_back(sa);
    _positions.push_back(sah);
    _positions.push_back(sahh);
}

int main(int argc, char **argv)
{
    return (0);
}

//sprite:test file:truc.png x:128 y:128
//text:Bonjour à tous file:emoji.ttf x:100 y:0