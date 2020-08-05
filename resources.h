/**
 * Created by Aiaksei Tokarau on 3/4/2020.
 *
 * @file resources.h
 *
 * This header includes all the necessary libraries to work with console menu.
 *
 * Also defines:
 * @enum Color: int values of color table in <Windows.h>.
 * @enum Keys: int values of key table in <conio.h>
 */

#ifndef CONSOLE_MENU_RESOURCES_H
#define CONSOLE_MENU_RESOURCES_H

#include <string>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cstdio>
#include <Windows.h>
#include <vector>

enum Color {
    Black = 0,
    Blue = 1,
    Green = 2,
    Aqua = 3,
    Red = 4,
    Purple = 5,
    White = 15
};

enum Keys {
    ESC = 27,
    LEFT = 75,
    RIGHT = 77,
    UP = 72,
    DOWN = 80,
    ENTER = 13,
    ARROW_KEY = 224
};

#endif //CONSOLE_MENU_RESOURCES_H
