/*
** EPITECH PROJECT, 2020
** ARCADE
** File description:
** Core
*/

#include "Core.hpp"

Arcade::Core::Core(std::string const &libPath) :
    _libGraph(std::make_unique<Dynlib::Dynlib>(libPath.substr(0, 2) == "./" ? libPath : "./" + libPath)),
     _libGraphVector({}), _libGamesVector({}), _isRunning(true), _isPaused(false),
     _onMenu(true), _onGameOver(false), _menuSelectedGame(0)
{
    std::cout << "Enter your name (Max 8) : ";
    std::string tmpName;
    std::getline(std::cin, tmpName);
    tmpName.substr(0, 8);
    if (std::cin.bad() || std::cin.eof()) _playerName = "Noob";
    else _playerName = tmpName;
    Sound::Get().Play(0, 0.2);
    searchGameLib();
    searchGraphLib();
    loadGraphLib(_libGraph);

    getLibVector();
    getGamesVector();
}

Arcade::Core::~Core()
{ }

void Arcade::Core::loadGraphLib(std::unique_ptr<Dynlib::Dynlib> &lib)
{
    int (*ptr)(void) = (int (*)(void))(lib->getSymbol("magic"));

    if (!ptr || ptr() != 0xC + 0xA * 0xCA)
        throw Dynlib::DynlibError("Error when trying to load '" + lib->getName() + "'", "Invalid Graphical Librairy");
    _graphPtr = lib->classFactory<IGraphics>("factory");
    if (_gamePtr.get() != nullptr) {
        _graphPtr->setColor(_gamePtr->getColor());
        _graphPtr->setSprite(_gamePtr->getSprite());
    }
}

void Arcade::Core::loadGameLib(std::unique_ptr<Dynlib::Dynlib> &lib)
{
    int (*ptr)(void) = (int (*)(void))(lib->getSymbol("magic"));

    if (!ptr || ptr() != 0xC - 0xA * 0xCA)
        throw Dynlib::DynlibError("Error when trying to load '" + lib->getName() + "'", "Invalid Game Librairy");
    _gamePtr = lib->classFactory<IGames>("factory");
    if (_gamePtr.get() != nullptr) {
        _graphPtr->setColor(_gamePtr->getColor());
        _graphPtr->setSprite(_gamePtr->getSprite());
    }
}

void Arcade::Core::searchGraphLib()
{
    std::string path = "./lib";
    std::smatch m;

    for (auto const &entry : std::filesystem::directory_iterator(path)) {
        std::string str = entry.path().string();
        if (std::regex_search(str, m, std::basic_regex<char>(REGEX_PATH_LIB)))
            _libGraphList.insert({str, m[2]});
    }
}

void Arcade::Core::searchGameLib()
{
    std::string path = "./games";
    std::smatch m;

    for (auto const &entry : std::filesystem::directory_iterator(path)) {
        std::string str = entry.path().string();
        if (std::regex_search(str, m, std::basic_regex<char>(REGEX_PATH_GAME)))
            _libGameList.insert({str, m[2]});
    }
}

void Arcade::Core::getLibVector()
{
    for (auto it = _libGraphList.begin(); it != _libGraphList.end(); it++)
        _libGraphVector.push_back(it->second);
}

void Arcade::Core::getGamesVector()
{
    for (auto it = _libGameList.begin(); it != _libGameList.end(); it++)
        _libGamesVector.push_back(it->second);
}

std::vector<std::string> Arcade::Core::showSelection(std::vector<std::string> in)
{
    if (in.size() == 0 || (unsigned int)_menuSelectedGame > in.size() || _menuSelectedGame < 0) return (in);
    in[_menuSelectedGame] = "> " + in[_menuSelectedGame];
    return (in);
}

void Arcade::Core::run()
{
    _updateClock.reset();
    _framerateClock.reset();
    while (_isRunning) {
        _updateClock.setTimePoint();
        _framerateClock.setTimePoint();
        frame();
    }
}

void Arcade::Core::frame()
{
    std::vector<Arcade::Arcade_key> event;

    if (_framerateClock.getDuration() > 1000000.0 / 20.0) {
        _graphPtr->clearScreen();
        event = _graphPtr->getEvent();
        if (findEvent(Arcade::QUIT, event)) {
            _isRunning = false;
            return;
        }
        manageEvent(event);
        if (_onGameOver) {
            _graphPtr->printLose(_gamePtr->getScore(), _playerName);
            _onMenu = true;
        } else if (_onMenu == false) {
            _graphPtr->printMap(_gamePtr->getMap());
            _graphPtr->printShoot(_gamePtr->getShoot());
            _graphPtr->printPlayer(_gamePtr->getPlayer());
            _graphPtr->printUI(_gamePtr->getScore(), _playerName);
            _gamePtr->setEvent(event);
            _onGameOver = !_gamePtr->getState();
        } else
            _graphPtr->printMenu(_libGraphVector, showSelection(_libGamesVector));
        if (_updateClock.getDuration() > 0.1 * 1000000) {
            if (!_isPaused && !_onMenu)
                _gamePtr->run();
            _updateClock.reset();
        }
        event.clear();
        _graphPtr->refreshScreen();
        _framerateClock.reset();
    }
}

bool Arcade::Core::findEvent(Arcade::Arcade_key event, std::vector<Arcade::Arcade_key> eventArr) const
{
    for (auto const &e : eventArr)
        if (event == e)
            return (true);
    return (false);
}

void Arcade::Core::nextLib()
{
    auto it = _libGraphList.begin();

    for (; it->first != _libGraph->getName(); it++);
    Dynlib::Dynlib *ptr = _libGraph.release();
    if (++it != _libGraphList.end())
        _libGraph = std::make_unique<Dynlib::Dynlib>(it->first);
    else
        _libGraph = std::make_unique<Dynlib::Dynlib>(_libGraphList.begin()->first);
    loadGraphLib(_libGraph);
    delete ptr;
}

void Arcade::Core::nextGame()
{
    auto it = _libGameList.begin();

    for (; it->first != _libGame->getName(); it++);
    Dynlib::Dynlib *ptr = _libGame.release();
    if (++it != _libGameList.end())
        _libGame = std::make_unique<Dynlib::Dynlib>(it->first);
    else
        _libGame = std::make_unique<Dynlib::Dynlib>(_libGameList.begin()->first);
    loadGameLib(_libGame);
    delete ptr;
}

void Arcade::Core::previousLib()
{
    auto it = _libGraphList.begin();

    for (; it->first != _libGraph->getName(); it++);
    Dynlib::Dynlib *ptr = _libGraph.release();
    if (it != _libGraphList.begin())
        _libGraph = std::make_unique<Dynlib::Dynlib>((--it)->first);
    else
        _libGraph = std::make_unique<Dynlib::Dynlib>(_libGraphList.rbegin()->first);
    loadGraphLib(_libGraph);
    delete ptr;
}

void Arcade::Core::previousGame()
{
    auto it = _libGameList.begin();

    for (; it->first != _libGame->getName(); it++);
    Dynlib::Dynlib *ptr = _libGame.release();
    if (it != _libGameList.begin())
        _libGame = std::make_unique<Dynlib::Dynlib>((--it)->first);
    else
        _libGame = std::make_unique<Dynlib::Dynlib>(_libGameList.rbegin()->first);
    loadGameLib(_libGame);
    delete ptr;
}

void Arcade::Core::manageEvent(std::vector<Arcade::Arcade_key> eventArr)
{
    for (auto const &event : eventArr) {
        if (event == Arcade::PREVIOUS_GAME && !_onMenu)
            previousGame();
        if (event == Arcade::PREVIOUS_LIB)
            previousLib();
        if (event == Arcade::NEXT_GAME && !_onMenu)
            nextGame();
        if (event == Arcade::NEXT_LIB)
            nextLib();
        if (event == Arcade::PAUSE && !_onMenu)
            _isPaused = !_isPaused;
        if (event == Arcade::UP && _onMenu) {
            if ((unsigned int)_menuSelectedGame + 1 > _libGameList.size() - 1) _menuSelectedGame = 0;
            else _menuSelectedGame++;
        }
        if (event == Arcade::DOWN && _onMenu) {
            if (_menuSelectedGame == 0) _menuSelectedGame = _libGameList.size() - 1;
            else _menuSelectedGame--;
        }
        if (event == Arcade::USE && _onMenu && !_onGameOver) {
            _onMenu = false;
            Dynlib::Dynlib *ptr = _libGame.release();
            for (auto const &[first, second] : _libGameList)
                if (second == _libGamesVector[_menuSelectedGame])
                    _libGame = std::make_unique<Dynlib::Dynlib>(first);
            loadGameLib(_libGame);
            delete ptr;
        }
        if (event == Arcade::MENU)
            _onMenu = true;
        if (event == Arcade::USE && _onGameOver)
            _onGameOver = false;
    }
}
