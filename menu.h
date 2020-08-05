/**
 * Created by Aiaksei Tokarau on 3/4/2020.
 *
 * @file menu.h
 *
 * Declaration of methods implemented in "menu.cpp".
 *
 * This class represents simple menu.
 * In fact it's a wrapper for menu_element array.
 * Allows to print_horiz, edit and go through the menu_element array.
 */

#ifndef CONSOLE_MENU_MENU_H
#define CONSOLE_MENU_MENU_H

#include "menu_element.h"

class menu {

public:

    /**
     * Main menu constructor.
     * @selected is first element by default (or 0 in array).
     * "non-skippable" by default.
     *
     * @param elements array of menu_elements
     */
    explicit menu(std::vector<menu_element> elements);


    /**.
     * Launches menu.
     * Allows user to go through menu by pressing DOWN and UP.
     * To enter menu_element press ENTER.
     */
    virtual void run();


    /**
     * Sets spikkable to a new value
     *
     * @param skippable is a boolean value
     */
    void set_skippable(boolean skippable);


protected:

    /**
     * Sets the @selected "pointer" on previous element of @elements.
     * Depending on @skippable passes through menu edges or stays on place
     */
    void prev();


    /**
     * Sets the @selected "pointer" on next element of @elements.
     * Depending on @skippable passes through menu edges or stays on place
     */
    void next();


    /**
     * Enters the selected menu_element.
     */
    void enter();


    /**
     * Prints out menu by printing out menu_element in @elements one by one.
     */
    void build();


private:

    /*
     * Array of menu_element
     */
    std::vector<menu_element> elements;


    /**
     * Index of selected menu_element in @elements
     */
    int selected;


    /**
     * true: If @selected is 0 previous element is last one in @elements.
     * If @selected is last one next element is first in @elements.
     *
     * false: If @selected is 0 there is no previous element.
     * If selected is last one there is no next element.
     */
    boolean skippable;


    /**
     * Allows to track where menu was launched from.
     * With this variable "infinite" number of connected menus are possible.
     *
     * true: menu was launched from another menu
     * false: menu was launched after returning from @foo that was launched by entering in menu_element
     */
    static boolean was_run;
};


#endif //CONSOLE_MENU_MENU_H
