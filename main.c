/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include <dlfcn.h>

int main()
{
    void *handle = dlopen("libwouah.so", RTLD_LAZY);
    return (0);
}