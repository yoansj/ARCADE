/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Dynlib
*/

#ifndef DYNLIB_HPP_
#define DYNLIB_HPP_

#include <iostream>
#include <memory>
#include <map>
#include <dlfcn.h>

namespace Dynlib
{
    class DynlibError : public std::exception {
        public:
            DynlibError(std::string const &message, std::string const &type) { };

            std::string const &getType() const { return _type; };
            char const *what() const noexcept override { return _message.data(); };

        private:
            std::string _message;
            std::string _type;
    };

    class Dynlib {
        public:
            Dynlib(std::string const &dlname);
            ~Dynlib();

            void *getSymbol(std::string const &symname);

            template<typename T>
            std::unique_ptr<T> classFactory(std::string const &symname)
            {
                return ((std::unique_ptr<T>(*)(void))(getSymbol(symname))->second)();
            }

        private:
            void *_dynlib;
            std::map<std::string const &, void *> _symbol;
    };
}



#endif /* !DYNLIB_HPP_ */
