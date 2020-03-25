/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** snake
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../include/Snake.hpp"

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
            std::cout << "T'es mort" << std::endl; //Ligne de collision avec soi même à changer
    }

    /* Update des positions peut être à mettre dans une fonction membre */
    Position npos = _positions[0];
    if (_dir == UP)
        npos.setY(npos.getY() - _speed);
    if (_dir == DOWN)
        npos.setY(npos.getY() + _speed);
    if (_dir == RIGHT)
        npos.setX(npos.getX() + _speed);
    if (_dir == LEFT)
        npos.setX(npos.getX() - _speed);
    _positions.insert(_positions.begin(), npos);

    /* Check collision avec un fruit */
    if (_positions[0].getX() == _fruit.getX() && _positions[0].getY() == _fruit.getY()) {
        _score += 1;
        _fruit = Position(std::rand() % 30, std::rand() % 30);
        for (int i = 0; _positions.begin() + i != _positions.end(); i++) {
            if (_positions[i].getX() == _fruit.getX() && _positions[i].getY() == _fruit.getY()) {
                _fruit = Position(std::rand() % 30, std::rand() % 30);
                i = 0;
            }
        }
    } else
        _positions.pop_back();

    //std::cout << "Taille : " << _positions.size() << std::endl;
    //std::cout << "Score : " << _score << std::endl;
    std::cout << "Fruit : " << _fruit.getX() << ": " << _fruit.getY() << std::endl;
}

void Snake::close()
{
}

Snake::Snake() : _score(0), _speed(1), _dir(RIGHT), _fruit(std::rand() % 30, std::rand() % 30), _paused(false)
{
    Position s(3, 0);
    Position sa(2, 0);
    Position sah(1, 0);
    Position sahh(0, 0);

    _positions.push_back(s);
    _positions.push_back(sa);
    _positions.push_back(sah);
    _positions.push_back(sahh);
    std::cout << _fruit.getX() << ":" << _fruit.getY() << std::endl;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    Snake jeu;
    sf::RenderWindow window(sf::VideoMode(32 * 30, 32 * 30), "SnakeTest", sf::Style::Titlebar | sf::Style::Close);
    sf::Clock cloque;
    sf::Event event;
    window.setFramerateLimit(60);

    sf::Texture pomme;
    pomme.loadFromFile("assets/apple.png");
    sf::Texture head;
    head.loadFromFile("assets/head.png");
    sf::Texture body;
    body.loadFromFile("assets/body.png");

    while (window.isOpen()) {
        window.clear(sf::Color::Blue);

        std::vector<ArcadeKey> touches;
        //push back un touche vide pour qu'il n'y ait pas de seg fault dans la fonction qui cherche un event dans le tableau
        touches.push_back(ArcadeKey::NONE);

        //update le jeu toutes les 0.2s
        if (cloque.getElapsedTime().asSeconds() >= 0.2) {
            jeu.run();
            cloque.restart();
        }

        //process les event
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                touches.push_back(ArcadeKey::QUIT);
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
                touches.push_back(ArcadeKey::PAUSE);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
                touches.push_back(ArcadeKey::UP);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
                touches.push_back(ArcadeKey::DOWN);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                touches.push_back(ArcadeKey::LEFT);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
                touches.push_back(ArcadeKey::RIGHT);
        }

        std::vector<sf::Sprite*> test;
        test.push_back(new sf::Sprite);
        test.push_back(new sf::Sprite);

        std::vector<Snake::Position> pos = jeu.getSnakePositions();

        test[0]->setTexture(pomme);
        test[0]->setPosition(jeu.getFruit().getX() * 32, jeu.getFruit().getY() * 32);
        window.draw(*test[0]);

        test[1]->setTexture(head);
        test[1]->setPosition(pos[0].getX() * 32, pos[0].getY() * 32);

        for (int i = 1; i != pos.size(); i++) {
            test.push_back(new sf::Sprite);
            test[i + 1]->setTexture(body);
            test[i + 1]->setPosition(pos[i].getX() * 32, pos[i].getY() * 32);
            window.draw(*test[i+1]);
        }

        window.draw(*test[1]);

        window.display();
        //envoyer les evenements au jeu
        jeu.setEvent(touches);
    }

    return (0);
}
