/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Solarfox
*/

#ifndef Solarfox_HPP_
#define Solarfox_HPP_

#include <vector>
#include <random>
#include <iostream>
#include "IGames.hpp"
#include "Input.hpp"

class Solarfox : public IGames {
    public:
        Solarfox();
        ~Solarfox() = default;

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
                Position(Position const &cpy) : _x(cpy.getX()), _y(cpy.getY()) {};

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

        class Ennemy {
            public:
                Ennemy(int x, int y, Direction dir, Direction shootDir = Direction::DOWN) : _pos(x, y), _dir(dir), _shootDirection(shootDir), _blocksTraveled(0),_blocksToShoot(Solarfox::randomRange(8, 20)) {};
                ~Ennemy() = default;

                void update();
                void setPosition(int x, int y) {_pos.setXY(x, y);};
                void setDirection(Direction dir) {_dir = dir;};
                void setShootDirection(Direction dir) {_shootDirection = dir;};

                Position getPosition() const {return _pos;};
                Direction getDirection() const {return _dir;};
                Direction getShootDirection() const {return _shootDirection;};

            private:
                Position _pos;
                Direction _dir;
                Direction _shootDirection;
                int _blocksTraveled;
                int _blocksToShoot;
        };

        class Bullet {
            public:
                Bullet(int x, int y, Direction dir, bool active) : _pos(x, y), _dir(dir), _isActive(active), _blocksTraveled(0), _maxBlocks(-1) {};
                ~Bullet() = default;

                void update();
                void setMaxBlocks(int b) {_maxBlocks = b;};
                void setPosition(int x, int y) {_pos.setXY(x, y);};
                void setDirection(Direction dir) {_dir = dir;};
                void setActive(bool b) {_isActive = b;};
                void resetBlocksTraveled() {_blocksTraveled = 0;};
                void Destroy() {_isActive = false; setPosition(0, 0);};

                bool isPlayerBullet() const {return (_maxBlocks == -1) ? false : true;};
                bool isActive() const {return _isActive;};
                Position getPosition() const {return _pos;};
                Direction getDirection() const {return _dir;};

            private:
                Position _pos;
                Direction _dir;
                bool _isActive;
                int _blocksTraveled;
                int _maxBlocks;
        };

        class BulletPool {
            public:
                //Le 20 correspond au nombre de balles max sur l'écran
                static BulletPool &Get() {static BulletPool instance(20); return (instance);};

                std::vector<Solarfox::Bullet> &GetBullets() {return (_bullets);};

                bool Instantiate(int x, int y, Direction dir, int maxBlocks);
                bool Instantiate(Position pos, Direction dir, int maxBlocks);
                void CheckCollisions();

                void Update() {
                    for (std::size_t i = 0; i != _bullets.size(); i++) {
                        _bullets[i].update();
                    }
                };

                void Destroy(int index = -1) {
                    if (index == -1)
                        for (std::size_t i = 0; i != _bullets.size(); i++) _bullets[i].Destroy();
                    else _bullets[index].Destroy();
                }

            private:
                BulletPool& operator= (const BulletPool&) = delete;
                BulletPool (const BulletPool&) = delete;

                BulletPool(int maxsize) : _maxSize(maxsize) {
                    for (int i = 0; i != _maxSize; i++)
                        _bullets.push_back(Bullet(-1, -1, UP, false));
                };
                ~BulletPool() = default;

                int _maxSize;
                std::vector<Solarfox::Bullet> _bullets;
        };

        void run() override;

        void restart();

        void generateLevel();

        void setEvent(std::vector<Arcade::Arcade_key> eventArray) override;

        static int randomRange(int min, int max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(min, max);
            return (dis(gen));
        }

        std::vector<std::vector<int>> getMap() const;
        std::map<Arcade::Block_tile, std::string> getSprite() const { return _sprite; };
        std::map<Arcade::Block_tile, Arcade::Text> getColor() const { return _color; };
        std::vector<std::vector<int>> getPlayer() const;
        std::vector<std::vector<int>> getShoot() const;
        int getScore() const {return (_score);};
        bool getState() const { return _isRunning; };


    private:
        int _score;
        int _powerups;
        int _ennemyCount;
        Direction _dir;
        Position _player;
        std::vector<Position> _points;
        std::vector<Ennemy> _ennemies;
        std::map<Arcade::Block_tile, std::string> _sprite;
        std::map<Arcade::Block_tile, Arcade::Text> _color;
        std::vector<std::vector<int>> _map;
        std::vector<std::vector<int>> _shootMap;
        bool _isRunning;
        std::vector<std::string> _sounds;
        bool findEvent(Arcade::Arcade_key event, std::vector<Arcade::Arcade_key> eventArray) const;
};

#endif /* !Solarfox_HPP_ */
