/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Arcade::Ncurses::Ncurses() : _main(initscr()), _w(0), _h(0)
{
    curs_set(0);
    noecho();
    nodelay(_main, true);
    set_escdelay(1);
    start_color();
    keypad(_main, true);
    getmaxyx(_main, _h, _w);
}

Arcade::Ncurses::~Ncurses()
{
    endwin();
}

int Arcade::Ncurses::getColor(std::vector<int> c) const
{
    if (c[0] > 80 && c[1] > 80 && c[2] > 80)
        return (COLOR_WHITE);
    else if (c[0] > 80 && c[1] <= 80 && c[2] <= 80)
        return (COLOR_RED);
    else if (c[0] <= 80 && c[1] > 80 && c[2] <= 80)
        return (COLOR_GREEN);
    else if (c[0] <= 80 && c[1] <= 80 && c[2] > 80)
        return (COLOR_BLUE);
    else if (c[0] > 80 && c[1] > 80 && c[2] <= 80)
        return (COLOR_YELLOW);
    else if (c[0] > 80 && c[1] <= 80 && c[2] > 80)
        return (COLOR_MAGENTA);
    else if (c[0] <= 80 && c[1] > 80 && c[2] > 80)
        return (COLOR_CYAN);
    else if (c[0] <= 80 && c[1] <= 80 && c[2] <= 80)
        return (COLOR_BLACK);
    return (COLOR_YELLOW);
}

void Arcade::Ncurses::printString(std::string str, int x, int y, std::vector<int> c, std::vector<int> bc, int type) const
{
    init_pair(type, getColor(c), getColor(bc));
    attron(COLOR_PAIR(type));
    mvprintw(y, x, str.data());
    attroff(COLOR_PAIR(type));
}

void Arcade::Ncurses::printMap(std::vector<std::vector<int>> map)
{
    std::size_t map_h = map.size();
    std::size_t map_w = (*map.begin()).size();
    Arcade::Block_tile pixel = Arcade::VOID;

    _map_s = { _w / 2 - map_w, _h / 2 - map_h / 2 };
    for (std::size_t i = 0; i < map_h * map_w; i++) {
        pixel = static_cast<Arcade::Block_tile>(map[i / map_w][i % map_w]);
        if (_color.find(pixel) != _color.end()) {
            Arcade::Text text = _color.find(pixel)->second;
            printString(
                text.getText() + text.getText(), _map_s.first + (i % map_w) * 2, _map_s.second + (i / map_w),
                text.getFColor(), text.getBColor(), pixel
            );
        }
    }
}

void Arcade::Ncurses::printPlayer(std::vector<std::vector<int>> player)
{
    Arcade::Text text = _color.find(Arcade::Block_tile::PLAYER)->second;

    printString(
        "<>", _map_s.first + (*player.begin())[0] * 2, _map_s.second + (*player.begin())[1],
        text.getFColor(), text.getBColor(), Arcade::Block_tile::PLAYER
    );
    for (auto it = player.begin() + 1; it != player.end(); it++) {
        printString(
            text.getText() + text.getText(), _map_s.first + (*it)[0] * 2, _map_s.second + (*it)[1],
            text.getFColor(), text.getBColor(), Arcade::Block_tile::PLAYER
        );
    }
}

void Arcade::Ncurses::printShoot(std::vector<std::vector<int>> map)
{
    std::size_t map_h = map.size();
    std::size_t map_w = (*map.begin()).size();
    Arcade::Text text = _color.find(Arcade::SHOOT)->second;
    Arcade::Block_tile pixel = _color.find(Arcade::SHOOT)->first;

    for (std::size_t i = 0; i < map_h * map_w; i++) {
        if (map[i / map_w][i % map_w] == pixel)
            printString(text.getText() + text.getText(), _map_s.first + (i % map_w) * 2, _map_s.second + (i / map_w), text.getFColor(), text.getBColor(), pixel);
    }
}

std::vector<Arcade::Arcade_key> Arcade::Ncurses::getEvent() const
{
    std::vector<Arcade::Arcade_key> tmp = { Arcade::NONE };
    int ch = getch();

    if (Arcade::ncurses_binding.find(ch) != Arcade::ncurses_binding.end())
        tmp.push_back(Arcade::ncurses_binding.find(ch)->second);
    return (tmp);
}

void Arcade::Ncurses::printMenu(std::vector<std::string> graphs, std::vector<std::string> games)
{
    mvprintw(_h / 2 - 25, _w / 2 - 14, " _____               _     ");
    mvprintw(_h / 2 - 24, _w / 2 - 14, "|  _  |___ ___ ___ _| |___ ");
    mvprintw(_h / 2 - 23, _w / 2 - 14, "|     |  _|  _| .'| . | -_|");
    mvprintw(_h / 2 - 22, _w / 2 - 14, "|__|__|_| |___|__,|___|___|");
    for (std::size_t i = 0; i < 17; i++)
        mvprintw(_h / 2 + i - 15, _w / 2, "|");
    for (std::size_t i = 0; i < _w; i++)
        mvprintw(_h / 2 - 16, i, "_");
    mvprintw(_h / 2 - 15, _w / 2 - _w / 4 - 12, "| Graphical Librairies |");
    mvprintw(_h / 2 - 15, _w / 2 + _w / 4 - 9, "| Game Librairies |");
    mvprintw(_h / 2 - 14, _w / 2 + _w / 4 - 9, "|_________________|");
    mvprintw(_h / 2 - 14, _w / 2 - _w / 4 - 12, "|______________________|");
    for (std::size_t i = 0; i < graphs.size(); i++)
        mvprintw(_h / 2 - 10 + i, 5, graphs[i].data());
    for (std::size_t i = 0; i < games.size(); i++)
        mvprintw(_h / 2 - 10 + i, 5 + _w / 2, games[i].data());
    for (std::size_t i = 0; i < _w; i++)
        mvprintw(_h / 2, i, "_");

    mvprintw(_h / 2 + 1, _w / 2 - 27, "    _  _______   _____   _____ ___    ___ _      ___   __");
    mvprintw(_h / 2 + 2, _w / 2 - 27, "   | |/ / __\\ \\ / / __| |_   _/ _ \\  | _ \\ |    /_\\ \\ / /");
    mvprintw(_h / 2 + 3, _w / 2 - 27, "   | ' <| _| \\ V /\\__ \\   | || (_) | |  _/ |__ / _ \\ V / ");
    mvprintw(_h / 2 + 4, _w / 2 - 27, "   |_|\\_\\___| |_| |___/   |_| \\___/  |_| |____/_/ \\_\\_|  ");
    mvprintw(_h / 2 + 5, _w / 2 - 27, "                                                         ");

    mvprintw(_h / 2 + 6, _w / 2 - 10, "Movement : Arrow keys");
    mvprintw(_h / 2 + 8, _w / 2 - 13, "Select a game : Space key");
    mvprintw(_h / 2 + 10, _w / 2 - 10, "Previous lib : Q key");
    mvprintw(_h / 2 + 12, _w / 2 - 8, "Next lib : A key");
}

void Arcade::Ncurses::printLose(int score, std::string name)
{
    mvprintw(10, _w / 2 - 32, "  ________                         ________                     ");
    mvprintw(11, _w / 2 - 32, " /  _____/_____    _____   ____    \\_____  \\___  __ ___________ ");
    mvprintw(12, _w / 2 - 32, "/   \\  ___\\__  \\  /     \\_/ __ \\    /   |   \\  \\/ // __ \\_  __ \\");
    mvprintw(13, _w / 2 - 32, "\\    \\_\\  \\/ __ \\|  Y Y  \\  ___/   /    |    \\   /\\  ___/|  | \\/");
    mvprintw(14, _w / 2 - 32, " \\______  (____  /__|_|  /\\___  >  \\_______  /\\_/  \\___  >__|   ");
    mvprintw(15, _w / 2 - 32, "        \\/     \\/      \\/     \\/           \\/          \\/       ");

    mvprintw(20, _w / 2 - ((name + ", you lost !").size() / 2), (name + ", you lost !").data());
    mvprintw(21, _w / 2 - (("Score: " + std::to_string(score)).size() / 2), ("Score: " + std::to_string(score)).data());
    mvprintw(23, _w / 2 - (26 / 2), "Keep your Determination :)");
}

void Arcade::Ncurses::printUI(int score, std::string name)
{
    std::string tmp = name + " Score : " + std::to_string(score);
    mvprintw(_h / 2  + 15, _w / 2 - (tmp.length() / 2) + 5, tmp.c_str());
    mvprintw(_h / 2  + 17, _w / 2 - 23, "SPACE = SHOOT | ARROW KEYS = MOVE | P = PAUSE");
    mvprintw(_h / 2  + 19, _w / 2 - 17, "R = RESTART | M = MENU | ESC = QUIT");
    mvprintw(_h / 2  + 21, _w / 2 - 16, "Z = NEXT GAME | S = PREVIOUS GAME");
    mvprintw(_h / 2  + 23, _w / 2 - 16, "A = NEXT LIB | Q = PREVIOUS LIB");
}


extern "C" {
    std::unique_ptr<Arcade::Ncurses> factory() {
        return (std::make_unique<Arcade::Ncurses>());
    }
    int magic() {
        return (0xC + 0xA * 0xCA);
    }
}
