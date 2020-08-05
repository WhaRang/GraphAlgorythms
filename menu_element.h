/**
 * Created by Aiaksei Tokarau on 3/4/2020.
 *
 * @file menu_element.h
 *
 * Declaration of methods implemented in "menu_element.cpp".
 *
 * This class represents a menu element.
 * The main task of a particular object of this class is to redirect user
 * to @foo when this element entered.
 * @text of menu element can be customized.
 * Contains two static methods for setting console background and fg color.
 */

#ifndef CONSOLE_MENU_MENU_ELEMENT_H
#define CONSOLE_MENU_MENU_ELEMENT_H


#include "resources.h"


class menu_element {

public:

    /**
     * just for current project
     * constructor for back button
     */
    menu_element(const std::string &text);


    /**
     * Basic constructor for menu_element.
     * Whole text is highlighted when element is selected.
     * Sets @first_color on Black, @second_color on White.
     *
     * @param text is printed in console. Graphic representation of menu_element.
     * @param foo function to which user is redirected when menu_element is entered.
     */
    menu_element(const std::string &text, void (*foo)());


    /**
     * Constructor for menu_element.
     * Whole @text is highlighted when element is selected.
     * Allows to choose @first_color and @second_color during initialization.
     *
     * @param text is printed in console. Graphic representation of menu_element.
     * @param first_color is bg color when element is unselected and fg color when selected.
     * @param second_color is fg color when element is unselected and bg color when selected.
     * @param foo function to which user is redirected when menu_element is entered.
     */
    menu_element(const std::string &text, Color first_color, Color second_color, void (*foo)());


    /**
     * Constructor for menu_element.
     * Allows to choose highlighted part of the @text when element is selected.
     * The first occurrence of @highlighted in @text is taking.
     * Allows to choose @first_color and @second_color during initialization.
     *
     * @param text is printed in console. Graphic representation of menu_element.
     * @param highlighted is highlighted part of @text when element is selected. Must be part of @text.
     * @param first_color is bg color when element is unselected and fg color when selected.
     * @param second_color is fg color when element is unselected and bg color when selected.
     * @param foo function to which user is redirected when menu_element is entered.
     */
    menu_element(const std::string &text, const std::string &highlighted,
                 Color first_color, Color second_color, void (*foo)());


    /**
     * Main constructor for menu_element.
     * Allows precisely choose highlighted part of @text when element is selected
     * by picking up the borders of highlighted string in @text.
     * Allows to choose @first_color and @second_color during initialization.
     *
     * @param text is printed in console. Graphic representation of menu_element.
     * @param from index of @text highlighted part starts from.
     * @param to index of @text highlighted part ends with.
     * @param first_color is bg color when element is unselected and fg color when selected.
     * @param second_color is fg color when element is unselected and bg color when selected.
     * @param foo function to which user is redirected when menu_element is entered.
     */
    menu_element(const std::string &text, uint16_t from, uint16_t to,
                 Color first_color, Color second_color, void (*foo)());


    /**
     * Prints @text in console.
     * @first_color is bg color.
     * @second_color is fg color.
     */
    void print_selected();


    /**
     * Prints @text in console.
     * @first_color is fg color.
     * @second_color is bg color.
     */
    void print_unselected();


    /**
     * Redirects user to @foo.
     */
    void enter();


    /**
     * Sets @from to a new value if required conditions are met.
     *
     * @param from should be less than @to and must be less @text size.
     * @return true if conditions are met, false otherwise.
     */
    boolean set_from(uint16_t from);


    /**
     * Sets @to to a new value if required conditions are met.
     *
     * @param from should be greater than @from and must be less @text size.
     * @return true if conditions are met, false otherwise.
     */
    boolean set_to(uint16_t to);


    /**
     * Sets @first_color to a new value.
     *
     * @param color is enum Color type.
     */
    void setFirstColor(Color color);


    /**
     * Sets @second_color to a new value.
     *
     * @param color is enum Color type.
     */
    void setSecondColor(Color color);

    /**
     *
     * @return is_back
     */
    bool get_is_back();


    /**
     * Sets console bg color.
     * Black by default.
     *
     * @param bg is enum Color type.
     */
    static void SetConsoleBg(Color bg);


    /**
     * Sets console fg color.
     * White by default.
     *
     * @param fg is enum Color type.
     */
    static void SetConsoleFg(Color fg);


private:

    /**
     * When menu_element is selected the @text part
     * [from] -> [to] is highlighted.
     */
    uint16_t from{}, to{};

    /**
     * Represents menu_element in console.
     */
    std::string text;

    /**
     * void type function with no parameters is called when menu_element os entered.
     */
    void (*foo)(){};

    /**
     * menu_element is selected: bg -> @first_color, fg -> @second_color.
     * menu_element is unselected: bg -> @second_color, fg -> @first_color
     */
    Color first_color;
    Color second_color;

    /**
     * Console colors.
     * Allows to customize @text without affecting the console.
     */
    static Color console_bg;
    static Color console_fg;

    /**
     * just for current project
     */
     bool is_back;
};


#endif //CONSOLE_MENU_MENU_ELEMENT_H
