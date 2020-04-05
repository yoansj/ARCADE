/*
** EPITECH PROJECT, 2020
** OOP_arcade_interface_2019
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

namespace Arcade {
    enum Arcade_key {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        QUIT,
        MENU,
        USE,
        NEXT_LIB,
        PREVIOUS_LIB,
        PREVIOUS_GAME,
        NEXT_GAME,
        RESTART,
        PAUSE,
        NONE,
        NOT_UPDATE
    };

    enum Block_tile {
        VOID = 0,
        WALL,
        ITEM,
        ENEMY,
        PLAYER,
        PLAYER_HEAD,
        SHOOT
    };

    class Text {
        public:
            Text(std::string text, std::vector<int> fc, std::vector<int> bc) :
                _text(text), _fcolor(fc), _bcolor(bc) { };
            ~Text() = default;

            std::string getText() const { return _text; };
            std::vector<int> getFColor() const { return _fcolor; };
            std::vector<int> getBColor() const { return _bcolor; };

        private:
            std::string _text;
            std::vector<int> _fcolor;
            std::vector<int> _bcolor;
    };
}

#endif /* !INPUT_HPP_ */
