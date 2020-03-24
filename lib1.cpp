/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** lib1
*/

#include <stdio.h>
#include <dlfcn.h>

extern "C"
{
    void __attribute__((constructor)) lib_init();
    void __attribute__((destructor)) lib_destroy();
}

extern "C" void lib_init()
{
    printf("[lib1] Loading lib1\n");
}

extern "C" void lib_destroy()
{
    printf("[lib1] Unloading lib1\n");
}

extern "C" void entryPoint()
{
    printf("[lib1] Entry point !\n");
}