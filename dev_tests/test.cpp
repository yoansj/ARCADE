/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** test
*/

#include <dlfcn.h>
#include "IDisplay.hpp"

template<typename T>
std::unique_ptr<T> class_factory(void *handle, std::string const &entryPoint)
{
    void *ptr = dlsym(handle, entryPoint.data());
    // if (!ptr)
    //     throw;
    return ((std::unique_ptr<T>(*)(void))ptr)();
}

int main(void)
{
    void *lib = dlopen("./libtest.so", RTLD_LAZY);
    std::unique_ptr<IDisplay>(ptr1) = class_factory<IDisplay>(lib, "entryPointA");
    std::unique_ptr<IDisplay>(ptr2) = class_factory<IDisplay>(lib, "entryPointB");
    std::unique_ptr<IDisplay>(ptr3) = class_factory<IDisplay>(lib, "entryPointC");

    ptr1->init();
    ptr2->init();
    ptr3->init();
    dlclose(lib);
    return (0);
}
