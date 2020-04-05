/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Solarfox
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Solarfox.hpp"

Solarfox::Solarfox() :
    _score(0),_dir(RIGHT), _player(11, 12), _ennemies({Ennemy(0, 0, DOWN, DOWN)}),
    _sprite{{Arcade::VOID, "games/Solarfox/assets/void.png"}, {Arcade::WALL, "games/Solarfox/assets/wall.png"},
    {Arcade::ITEM, "games/Solarfox/assets/apple.png"}, {Arcade::PLAYER_HEAD, "games/Solarfox/assets/player.png"},
    {Arcade::SHOOT, "games/Solarfox/assets/snakeBody.png"}, {Arcade::ENEMY, "games/Solarfox/assets/ennemy.png"}},
    _color{
        {Arcade::VOID, Arcade::Text(" ", {0, 0, 0, 0}, {0, 0, 0, 0})},
        {Arcade::WALL, Arcade::Text(" ", {0, 0, 0, 0}, {255, 255, 255, 0})},
        {Arcade::ITEM, Arcade::Text("#", {255, 255, 0, 0}, {0, 0, 0, 0})},
        {Arcade::PLAYER, Arcade::Text(" ", {0, 255, 0, 0}, {0, 0, 0, 0})},
        {Arcade::SHOOT, Arcade::Text("V", {255, 0, 0, 0}, {0, 0, 0, 0})},
        {Arcade::ENEMY, Arcade::Text("U", {255, 80, 80, 0}, {0, 0, 0, 0})}
    },
    _isRunning(true),
    _sounds({"games/Solarfox/assets/bonus_sound.mp3", "games/Solarfox/assets/death_sound.mp3"})
{
    /* Init map normale */
    _map.push_back({Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL});
    for (int i = 0; i < 23; i++)
        _map.push_back({Arcade::WALL, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::WALL});
    _map.push_back({Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL, Arcade::WALL});

    /* Init map des tirs */
    for (int i = 0; i < 25; i++)
        _shootMap.push_back({Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID, Arcade::VOID});
    generateLevel();
}

void Solarfox::restart()
{
    _player.setXY(11, 12);
    _score = 0;
    _dir = RIGHT;
    BulletPool::Get().Destroy();
    _isRunning = true;
}

void Solarfox::generateLevel()
{
    std::vector<Solarfox::Position> newPowerups;
    std::vector<Solarfox::Ennemy> newNmy;

    BulletPool::Get().Destroy();
    _powerups = randomRange(5, 15);
    for (int i = 0; i != _powerups; i++) newPowerups.push_back(Position(randomRange(1, 23), randomRange(1, 23)));
    _points = newPowerups;

    _ennemyCount = randomRange(2, 6);
    for (int i = 0; i != _ennemyCount; i++) {
        Solarfox::Direction tmp = (Solarfox::Direction)randomRange(0, 3);
        if (tmp == UP) newNmy.push_back(Ennemy(randomRange(2, 23), 0, RIGHT, DOWN));
        if (tmp == DOWN) newNmy.push_back(Ennemy(randomRange(2, 23), 0, LEFT, UP));
        if (tmp == RIGHT) newNmy.push_back(Ennemy(24, randomRange(2, 23), DOWN, LEFT));
        if (tmp == LEFT) newNmy.push_back(Ennemy(0, randomRange(2, 23), UP, RIGHT));
    }
    _ennemies = newNmy;
}

//Appelée à chaque tour de boucle
void Solarfox::run()
{
    /* Update mouvement */
    if (_dir == UP)
        _player.setY(_player.getY() - 1);
    if (_dir == DOWN)
        _player.setY(_player.getY() + 1);
    if (_dir == RIGHT)
        _player.setX(_player.getX() + 1);
    if (_dir == LEFT)
        _player.setX(_player.getX() - 1);

    /* Update mouvement pour ennemis et balles */
    for (std::size_t i = 0; i != _ennemies.size(); i++)
        _ennemies[i].update();

    BulletPool::Get().CheckCollisions();
    BulletPool::Get().Update();

    /* Collisions avec joueur */
    std::vector<Bullet> bul = BulletPool::Get().GetBullets();
    for (std::size_t i = 0; i != bul.size(); i++) {
        if (_player.getX() == bul[i].getPosition().getX() && _player.getY() == bul[i].getPosition().getY() && bul[i].isPlayerBullet() == false) {
            _isRunning = false;
            generateLevel();
        }
    }

    /* Collisions avec powerup */
    std::vector<Solarfox::Bullet> bullets = BulletPool::Get().GetBullets();
    for (std::size_t i = 0; i != _points.size(); i++) {
        for (std::size_t x = 0; x != bullets.size(); x++) {
            if (bullets[x].isActive() == false || bullets[x].isPlayerBullet() == false) continue;
            if (bullets[x].getPosition().getX() == _points[i].getX() && bullets[x].getPosition().getY() == _points[i].getY()) {
                _points.erase(_points.begin() + i);
                _score += 50;
                _powerups -= 1;
                if (_powerups <= 0) {
                    generateLevel();
                    _player.setXY(11, 12);
                }
                return;
            }
        }
    }

    /* Collision avec les limites de la map/écran, à faire ici */
    if (_player.getX() >= 24 || _player.getX() <= 0) {
        generateLevel();
        _isRunning = false;
    }
    if (_player.getY() >= 24 || _player.getY() <= 0) {
        generateLevel();
        _isRunning = false;
    }
}

std::vector<std::vector<int>> Solarfox::getMap() const
{
    std::vector<std::vector<int>> newMap = _map;

    for (Solarfox::Ennemy nmy : _ennemies)
        newMap[nmy.getPosition().getY()][nmy.getPosition().getX()] = Arcade::ENEMY;
    for (std::size_t i = 0; i != _points.size(); i++) {
        if ((unsigned int)_points[i].getY() > newMap.size() - 1 || _points[i].getY() < 0) continue;
        if ((unsigned int)_points[i].getX() > newMap[i].size() - 1 || _points[i].getX() < 0) continue;
        newMap[_points[i].getY()][_points[i].getX()] = Arcade::ITEM;
    }
    return (newMap);
}

std::vector<std::vector<int>> Solarfox::getShoot() const
{
    std::vector<std::vector<int>> newMap = _shootMap;
    std::vector<Solarfox::Bullet> bullets = BulletPool::Get().GetBullets();

    for (std::size_t i = 0; i != bullets.size(); i++) {
        if (bullets[i].isActive() == true)
            newMap[bullets[i].getPosition().getY()][bullets[i].getPosition().getX()] = Arcade::SHOOT;
    }
    return (newMap);
}

//Cherche un event dans un vector d'event
//Renvoie true si l'event est trouvé
bool Solarfox::findEvent(Arcade::Arcade_key event, std::vector<Arcade::Arcade_key> eventArray) const
{
    for (int i = 0; eventArray.begin() + i != eventArray.end(); i++)
        if (event == eventArray[i]) return (true);
    return (false);
}

//Méthode qui process les event du jeu
void Solarfox::setEvent(std::vector<Arcade::Arcade_key> eventArray)
{
    if (findEvent(Arcade::RESTART, eventArray) == true) {
        restart();
        generateLevel();
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
        if (key == Arcade::Arcade_key::USE) {
            if (_player.getX() >= 24 || _player.getX() <= 1) continue;
            if (_player.getY() > 23 || _player.getY() <= 1) continue;
            if (_dir == RIGHT) {
                BulletPool::Get().Instantiate(_player.getX() + 2, _player.getY(), _dir, 2);
                BulletPool::Get().Instantiate(_player.getX() + 1, _player.getY(), _dir, 2);
            }
            if (_dir == LEFT) {
                BulletPool::Get().Instantiate(_player.getX() - 2, _player.getY(), _dir, 2);
                BulletPool::Get().Instantiate(_player.getX() - 1, _player.getY(), _dir, 2);
            }
            if (_dir == UP) {
                BulletPool::Get().Instantiate(_player.getX(), _player.getY() - 2, _dir, 2);
                BulletPool::Get().Instantiate(_player.getX(), _player.getY() - 1, _dir, 2);
            }
            if (_dir == DOWN) {
                BulletPool::Get().Instantiate(_player.getX(), _player.getY() + 2, _dir, 2);
                BulletPool::Get().Instantiate(_player.getX(), _player.getY() + 1, _dir, 2);
            }
            return;
        }
    }
}

std::vector<std::vector<int>> Solarfox::getPlayer() const
{
    std::vector<std::vector<int>> tmp;

    tmp.push_back({_player.getX(), _player.getY()});
    return (tmp);
}

void Solarfox::Ennemy::update()
{
    /* Try to shoot */
    if (_blocksTraveled >= _blocksToShoot) {
        if (_shootDirection == LEFT) {
            if (BulletPool::Get().Instantiate(_pos.getX() - 1, _pos.getY(), _shootDirection, -1)) {
                _blocksTraveled = 0;
                _blocksToShoot = Solarfox::randomRange(8, 20);
            }
        }
        if (_shootDirection == RIGHT) {
            if (BulletPool::Get().Instantiate(_pos.getX() + 1, _pos.getY(), _shootDirection, -1)) {
                _blocksTraveled = 0;
                _blocksToShoot = Solarfox::randomRange(8, 20);
            }
        }
        if (_shootDirection == UP) {
            if (BulletPool::Get().Instantiate(_pos.getX(), _pos.getY() - 1, _shootDirection, -1)) {
                _blocksTraveled = 0;
                _blocksToShoot = Solarfox::randomRange(8, 20);
            }
        }
        if (_shootDirection == DOWN) {
            if (BulletPool::Get().Instantiate(_pos.getX(), _pos.getY() + 1, _shootDirection, -1)) {
                _blocksTraveled = 0;
                _blocksToShoot = Solarfox::randomRange(8, 20);
            }
        }
    }

    /* Update des directions */
    if (_dir == UP) {
        _pos.setY(_pos.getY() - 1);
        _blocksTraveled++;
    }
    if (_dir == DOWN) {
        _pos.setY(_pos.getY() + 1);
        _blocksTraveled++;
    }
    if (_dir == RIGHT) {
        _pos.setX(_pos.getX() + 1);
        _blocksTraveled++;
    }
    if (_dir == LEFT) {
        _pos.setX(_pos.getX() - 1);
        _blocksTraveled++;
    }

    //Demi tour de droite à gauche
    if (_dir == RIGHT && _pos.getX() >= 24) {
        _pos.setX(_pos.getX() - 1);
        _dir = LEFT;
        _blocksTraveled++;
    }
    //Demi tour de gauche à droite
    if (_dir == LEFT && _pos.getX() <= 1) {
        _pos.setX(_pos.getX() + 1);
        _dir = RIGHT;
        _blocksTraveled++;
    }
    //Demi tour de Haut à bas
    if (_dir == UP && _pos.getY() <= 1) {
        _pos.setY(_pos.getY() + 1);
        _dir = DOWN;
        _blocksTraveled++;
    }
    //Demi tour de bas à haut
    if (_dir == DOWN && _pos.getY() >= 24) {
        _pos.setY(_pos.getY() - 1);
        _dir = UP;
        _blocksTraveled++;
    }
}

void Solarfox::Bullet::update()
{
    if (isActive() == false) return;

    /* Limites d'écran pour les balles */
    if (_pos.getX() >= 24 || _pos.getX() <= 0) Destroy();
    if (_pos.getY() >= 24 || _pos.getY() <= 0) Destroy();

    /* Update des directions */
    if (_dir == UP) {
        _pos.setY(_pos.getY() - 1);
        _blocksTraveled++;
    }
    if (_dir == DOWN) {
        _pos.setY(_pos.getY() + 1);
        _blocksTraveled++;
    }
    if (_dir == RIGHT) {
        _pos.setX(_pos.getX() + 1);
        _blocksTraveled++;
    }
    if (_dir == LEFT) {
        _pos.setX(_pos.getX() - 1);
        _blocksTraveled++;
    }

    /* Les balles du joueur ne se déplacent que de deux cases */
    if (_blocksTraveled >= 2 && _maxBlocks != -1) {
        _blocksTraveled = 0;
        _isActive = false;
    }
}

bool Solarfox::BulletPool::Instantiate(int x, int y, Direction dir, int maxBlocks) {
    for (int i = 0; i != _maxSize; i++) {
        if (_bullets[i].isActive() == false) {
            _bullets[i].setDirection(dir);
            _bullets[i].resetBlocksTraveled();
            _bullets[i].setPosition(x, y);
            _bullets[i].setMaxBlocks(maxBlocks);
            _bullets[i].setActive(true);
            return (true);
        }
    }
    return (false);
}

bool Solarfox::BulletPool::Instantiate(Position pos, Direction dir, int maxBlocks) {
    for (int i = 0; i != _maxSize; i++) {
        if (_bullets[i].isActive() == false) {
            _bullets[i].setDirection(dir);
            _bullets[i].resetBlocksTraveled();
            _bullets[i].setPosition(pos.getX(), pos.getY());
            _bullets[i].setMaxBlocks(maxBlocks);
            _bullets[i].setActive(true);
            return (true);
        }
    }
    return (false);
}

void Solarfox::BulletPool::CheckCollisions() {
    for (std::size_t i = 0; i != _bullets.size(); i++) {
        for (std::size_t x = i; x != _bullets.size(); x++) {
            if (i == x || _bullets[i].isActive() == false || _bullets[x].isActive()) continue;
            if (_bullets[i].getPosition().getX() == _bullets[x].getPosition().getX() && _bullets[i].getPosition().getY() == _bullets[x].getPosition().getY()) {
                    _bullets[i].Destroy();
                    _bullets[x].Destroy();
            }
        }
    }
}

extern "C" {
    std::unique_ptr<Solarfox> factory() {
        return (std::make_unique<Solarfox>());
    }

    int magic() {
        return (0xC - 0xA * 0xCA);
    }
}
