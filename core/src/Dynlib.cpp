/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Dynlib
*/

#include "Dynlib.hpp"

Dynlib::Dynlib::Dynlib(std::string const &dlname) :
    _dynlib(NULL)
{
    _dynlib = dlopen(dlname.data(), RTLD_LAZY);
    if (!_dynlib)
        throw DynlibError(dlerror(), "dlopen");
}

Dynlib::Dynlib::~Dynlib()
{
    if (_dynlib)
        return;
    if (dlclose(_dynlib))
        throw DynlibError(dlerror(), "dlclose");
}

void *Dynlib::Dynlib::getSymbol(std::string const &symname)
{
    void *ptr = NULL;

    if (_symbol.find(symname) == _symbol.end()) {
        ptr = dlsym(_dynlib, symname.data());
        if (!ptr)
            throw DynlibError(dlerror(), "dlsym");
        _symbol.insert(std::pair<std::string const &, void *>(symname, ptr));
    } else
        ptr = _symbol.find(symname)->second;
    return (ptr);
}
