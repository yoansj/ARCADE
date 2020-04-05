/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Caca
*/

#include "Caca.hpp"

Arcade::Caca::Caca() : _canvas(caca_create_canvas(50, 30)), _main(caca_create_display(_canvas)), _events(new caca_event_t), _height(25), _width(25)
{
    initMap();
    if (!_main) throw GraphicError("libcaca couldn't create new window", "libcaca");
    caca_set_display_title(_main, "Arcade");
    caca_set_display_time(_main, 00000.0667);
}

Arcade::Caca::~Caca()
{
    caca_free_canvas(_canvas);
    caca_free_display(_main);
}

void Arcade::Caca::printUI(int score, std::string name)
{
    std::string tmp = "Score : " + std::to_string(score);

    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
    caca_put_str(_canvas, 20, 25, tmp.c_str());
    caca_put_str(_canvas, 2, 26, "SPACE = SHOOT | ARROW KEYS = MOVE | P = PAUSE");
    caca_put_str(_canvas, 3, 27, "R = RESTART | M = MENU | ESC = QUIT");
    caca_put_str(_canvas, 3, 28, "Z = NEXT GAME | S = PREVIOUS GAME");
    caca_put_str(_canvas, 3, 29, "A = NEXT LIB | Q = PREVIOUS LIB");
    caca_put_str(_canvas, 3, 30, name.data());
}

void Arcade::Caca::printLose(int score, std::string name)
{
    static bool rand = false;
    static int quote = 0;
    std::vector<std::string> dumbQuotes = {{"It may be hard but you must retry"}, {"Try the tutorial (if there's one)"},
    {"Never lose sight of your goal !"}, {"Git gud noob"}, {"Failure is the first path to success"}, {"Vous conaissez Twitch Prime ?"}};
    std::string tmp = "Score : " + std::to_string(score);
    std::string go = name + " LOST, GAME OVER";

    if (rand == false) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 5);
        quote = dis(gen);
        rand = true;
    }

    caca_set_color_ansi(_canvas, CACA_RED, CACA_WHITE);
    caca_put_str(_canvas, 25 - (go.length() / 2), 12, go.c_str());
    caca_set_color_ansi(_canvas, CACA_MAGENTA, CACA_WHITE);
    caca_put_str(_canvas, 25 - (tmp.length() / 2), 14, tmp.c_str());
    caca_set_color_ansi(_canvas, CACA_BLUE, CACA_WHITE);
    caca_put_str(_canvas, 25 - 16, 16, "Use SPACE to go back to the menu");
    caca_set_color_ansi(_canvas, CACA_BLACK, CACA_WHITE);
    caca_put_str(_canvas, 25 - 7, 18, "Inspiring quote");
    caca_put_str(_canvas, 25 - (dumbQuotes[quote].length() / 2), 20, dumbQuotes[quote].c_str());
}

void Arcade::Caca::printMenu(std::vector<std::string> libGraph, std::vector<std::string> libGame)
{
    std::size_t gamesCounter = 0;
    std::size_t libCounter = 0;

    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_RED);
    caca_put_str(_canvas, 19, 0, "--- ARCADE ---");

    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLUE);
    caca_put_str(_canvas, 19, 2, "--- Games ---");
    for (; gamesCounter != libGame.size(); gamesCounter++)
        caca_put_str(_canvas, 19, gamesCounter + 3, libGame[gamesCounter].c_str());
    if (gamesCounter == 0) {
        caca_set_color_ansi(_canvas, CACA_RED, CACA_BLACK);
        caca_put_str(_canvas, 19, 0 + 3,"No games rip in potatoes :(");
    }

    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_GREEN);
    caca_put_str(_canvas, 12, 4 + gamesCounter, "--- Graphical librairies ---");
    for (; libCounter != libGraph.size() && libGraph.size() != 0; libCounter++) {
        caca_put_str(_canvas, 19, libCounter + gamesCounter + 5, libGraph[libCounter].c_str());
    }

    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLUE);
    caca_put_str(_canvas, 15, 6 + gamesCounter + libCounter, "--- Keys ---");
    caca_put_str(_canvas, 15, 7 + gamesCounter + libCounter, "Movement : Arrow keys");
    caca_put_str(_canvas, 15, 8 + gamesCounter + libCounter, "Select a game : Space key");
    caca_put_str(_canvas, 15, 9 + gamesCounter + libCounter, "Previous lib : Q key");
    caca_put_str(_canvas, 15, 10 + gamesCounter + libCounter, "Next lib : A key");

    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
    caca_put_str(_canvas, 15, 13 + gamesCounter + libCounter, "Made by :");
    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_MAGENTA);
    caca_put_str(_canvas, 15, 14 + gamesCounter + libCounter, "- Matthieu Veiga");
    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_RED);
    caca_put_str(_canvas, 15, 15 + gamesCounter + libCounter, "- Jerome Eap");
    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLUE | CACA_GREEN);
    caca_put_str(_canvas, 15, 16 + gamesCounter + libCounter, "- Yoan Saint Juste");
}

uint8_t Arcade::Caca::getColor(std::vector<int> c) const
{
    if (c[0] > 80 && c[1] > 80 && c[2] > 80)
        return (CACA_WHITE);
    else if (c[0] > 80 && c[1] <= 80 && c[2] <= 80)
        return (CACA_RED);
    else if (c[0] <= 80 && c[1] > 80 && c[2] <= 80)
        return (CACA_GREEN);
    else if (c[0] <= 80 && c[1] <= 80 && c[2] > 80)
        return (CACA_BLUE);
    else if (c[0] > 80 && c[1] > 80 && c[2] <= 80)
        return (CACA_YELLOW);
    else if (c[0] > 80 && c[1] <= 80 && c[2] > 80)
        return (CACA_MAGENTA);
    else if (c[0] <= 80 && c[1] > 80 && c[2] > 80)
        return (CACA_CYAN);
    else if (c[0] <= 80 && c[1] <= 80 && c[2] <= 80)
        return (CACA_BLACK);
    return (CACA_WHITE);
}

void Arcade::Caca::printString(std::string str, int x, int y, std::vector<int> c, std::vector<int> bc) const
{
    caca_set_color_ansi(_canvas, getColor(c), getColor(bc));
    caca_put_str(_canvas, x, y, str.c_str());
    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_WHITE);
}

void Arcade::Caca::printMap(std::vector<std::vector<int>> map)
{
    std::size_t map_h = map.size();
    std::size_t map_w = (*map.begin()).size();
    Arcade::Block_tile pixel = Arcade::VOID;

    _map_s = { _width / 2 - map_w / 2, _height / 2 - map_h / 2 };
    for (std::size_t i = 0; i < map_h * map_w; i++) {
        pixel = static_cast<Arcade::Block_tile>(map[i / map_w][i % map_w]);
        if (_color.find(pixel) != _color.end()) {
            Arcade::Text text = _color.find(pixel)->second;
            printString(text.getText() + text.getText(), _map_s.first + (i % map_w) * 2, _map_s.second + (i / map_w), text.getFColor(), text.getBColor());
        }
    }
}

void Arcade::Caca::printPlayer(std::vector<std::vector<int>> player)
{
    if (_color.find(Arcade::PLAYER) == _color.end()) return;

    Arcade::Text text = _color.find(Arcade::Block_tile::PLAYER)->second;

    printString("<>", _map_s.first + (*player.begin())[0] * 2, _map_s.second + (*player.begin())[1], text.getFColor(), text.getBColor());
    for (auto it = player.begin() + 1; it != player.end(); it++) {
        printString(text.getText() + text.getText(), _map_s.first + (*it)[0] * 2, _map_s.second + (*it)[1], text.getFColor(), text.getBColor());
    }
}

void Arcade::Caca::printShoot(std::vector<std::vector<int>> shoot)
{
    if (_color.find(Arcade::SHOOT) == _color.end()) return;

    Arcade::Text text = _color.find(Arcade::SHOOT)->second;

    for (std::size_t y = 0; y != shoot.size(); y++) {
        for (std::size_t x = 0; x != shoot[y].size(); x++) {
            if (shoot[y][x] == Arcade::SHOOT)
                printString(text.getText() + text.getText(), x * 2, y, text.getFColor(), text.getBColor());
        }
    }
}

void Arcade::Caca::initMap()
{
    _map = {{"                         "}, {"                         "}, {"                         "}, {"                         "},
    {"                         "}, {"                         "}, {"                         "}, {"                         "},
    {"                         "}, {"                         "}, {"                         "}, {"                         "}, {"                         "},
    {"                         "}, {"                         "}, {"                         "}, {"                         "},
    {"                         "}, {"                         "}, {"                         "}, {"                         "},
    {"                         "}, {"                         "}, {"                         "}, {"                         "}};
}

std::vector<Arcade::Arcade_key> Arcade::Caca::getEvent() const
{
    std::vector<Arcade::Arcade_key> tmp = { Arcade::NONE };

    //Chercher les event
    if (caca_get_event(_main, CACA_EVENT_KEY_PRESS, _events, 0) == 1 && caca_binding.find(_events->data.key.ch) != caca_binding.end())
        tmp.push_back(caca_binding.find(_events->data.key.ch)->second);
    return (tmp);
}

extern "C" {
    std::unique_ptr<Arcade::Caca> factory() {
        return (std::make_unique<Arcade::Caca>());
    }
    int magic() {
        return (0xC + 0xA * 0xCA);
    }
}