/*
** EPITECH PROJECT, 2020
** ARCADE
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <map>
#include <regex>
#include <chrono>
#include <filesystem>
#include <random>
#include "IGraphics.hpp"
#include "IGames.hpp"
#include "Dynlib.hpp"
#include "Input.hpp"

#include <unistd.h>

#define REGEX_PATH_LIB "(\\./lib/lib_arcade_)(.+)(\\.so)"
#define REGEX_PATH_GAME "(\\./games/lib_arcade_)(.+)(\\.so)"

namespace Arcade
{
    class Core {
        public:
            Core(std::string const &libPath);
            ~Core();

            void run();
            void frame();

            class Time {
                public:
                    Time() :
                        _t0(std::chrono::high_resolution_clock::now()),
                        _t1(std::chrono::high_resolution_clock::now())
                    { };
                    ~Time() = default;

                    void reset() { _t0 = std::chrono::high_resolution_clock::now(); _t1 = std::chrono::high_resolution_clock::now(); };
                    void setTimePoint() { _t1 = std::chrono::high_resolution_clock::now(); };
                    int getDuration() const { return std::chrono::duration_cast<std::chrono::microseconds>( _t1 - _t0 ).count(); };

                private:
                    std::chrono::time_point<std::chrono::high_resolution_clock> _t0;
                    std::chrono::time_point<std::chrono::high_resolution_clock> _t1;
            };

            class Sound {
                public:
                    static Sound &Get() {static Sound instance; return (instance);};

                    bool Play(unsigned int index, float volume = 1) {
                        if (index > _soundPath.size()) return (false);
                        volume *= 2;
                        std::string tmp = "play -q -v " + std::to_string(volume) + " " + _soundPath[index] + " &";
                        std::system(tmp.c_str());
                        return (true);
                    }

                    bool Play(unsigned int index, std::string volume = "1") {
                        if (index > _soundPath.size()) return (false);
                        std::string tmp = "play -q -v " + volume + " " + _soundPath[index] + " &";
                        std::system(tmp.c_str());
                        return (true);
                    }

                private:
                    Sound& operator= (const Sound&) = delete;
                    Sound (const Sound&) = delete;
                    Sound() : _soundPath({{"./games/sounds/bonus_sound.mp3"}, {"./games/sounds/death_sound.mp3"}, {"./games/sounds/menu_select.mp3"},
                    {"./games/sounds/intro1.ogg"}, {"./games/sounds/intro2.ogg"}, {"./games/sounds/intro3.ogg"}, {"./games/sounds/intro4.ogg"}, {"./games/sounds/intro5.ogg"},
                    {"./games/sounds/intro6.ogg"}})
                    {};
                    ~Sound() = default;
                    std::vector<std::string> _soundPath;
        };

        private:
            std::unique_ptr<Dynlib::Dynlib> _libGraph;
            std::map<std::string, std::string> _libGraphList;
            std::vector<std::string> _libGraphVector;
            std::unique_ptr<Dynlib::Dynlib> _libGame;
            std::map<std::string, std::string> _libGameList;
            std::vector<std::string> _libGamesVector;

            std::unique_ptr<IGraphics> _graphPtr;
            std::unique_ptr<IGames> _gamePtr;

            bool _isRunning;
            Time _updateClock;
            Time _framerateClock;
            bool _isPaused;
            bool _onMenu;
            bool _onGameOver;
            int _menuSelectedGame;
            std::string _playerName;

            void getUserName();
            void searchGraphLib();
            void searchGameLib();

            void loadGraphLib(std::unique_ptr<Dynlib::Dynlib> &lib);
            void loadGameLib(std::unique_ptr<Dynlib::Dynlib> &lib);

            void getGamesVector();
            void getLibVector();

            bool findEvent(Arcade::Arcade_key event, std::vector<Arcade::Arcade_key> eventArr) const;
            void manageEvent(std::vector<Arcade::Arcade_key> eventArr);

            void nextLib();
            void nextGame();
            void previousLib();
            void previousGame();

            std::vector<std::string> showSelection(std::vector<std::string>);
    };
}


#endif /* !CORE_HPP_ */
