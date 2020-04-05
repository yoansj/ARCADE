/*
** EPITECH PROJECT, 2020
** ARCADE
** File description:
** main
*/

#include <iostream>
#include "Core.hpp"
#include "Dynlib.hpp"
#include "GraphicError.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cout
            << "USAGE: ./arcade [graphical_library]" << std::endl
            << "[graphical_library] is the path of a lib contained in the /lib directory" << std::endl
            << "Made by : Matthieu Veiga, Jerome EAP, Yoan Saint Juste Promo 2023";
        return (84);
    }
    try {
        Arcade::Core core(argv[1]);
        core.run();
    } catch (Dynlib::DynlibError const &e) {
        std::cout << e.what() << " | " << e.getType() << std::endl;
    } catch (GraphicError const &e) {
        std::cout << "Graphical error : " << e.what() << " | " << e.getType() << std::endl;
    }
}
