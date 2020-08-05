/**
 * Created by Aiaksei Tokarau on 3/4/2020.
 *
 * @file menu_element.cpp
 *
 * Implementation of methods declared in "menu_element.h".
 */

#include "menu_element.h"

Color menu_element::console_bg = Black;

Color menu_element::console_fg = White;

menu_element::menu_element(const std::string &text) : menu_element(text, nullptr){
    this->is_back = true;
}

menu_element::menu_element(const std::string &text, void (*foo)()) :
        menu_element(text, Black, White, foo) {
}

menu_element::menu_element(const std::string &text, Color first_color, Color second_color, void (*foo)()) :
        menu_element(text, 0, text.size(), Black, White, foo) {
}

menu_element::menu_element(const std::string &text, const std::string &highlighted, Color first_color,
                           Color second_color, void (*foo)()) : menu_element(text, text.find(highlighted),
                                                                             text.find(highlighted) +
                                                                             highlighted.size(),
                                                                             first_color, second_color, foo) {
    this->is_back = false;
}

menu_element::menu_element(const std::string &text, uint16_t from, uint16_t to,
                           Color first_color, Color second_color, void (*foo)()) {
    this->text = text;
    if (!this->set_from(from)) {
        this->from = 0;
    }
    if (!this->set_to(to)) {
        this->to = this->text.size();
    }

    this->first_color = first_color;
    this->second_color = second_color;

    this->foo = foo;
}

void menu_element::print_unselected() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, (WORD) ((this->first_color << 4) | this->second_color));
    for (char c : this->text) {
        std::cout << c;
    }

    SetConsoleTextAttribute(hConsole, (WORD) ((this->console_bg << 4) | this->console_fg));

    std::cout << std::endl;
}

void menu_element::print_selected() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, (WORD) ((this->first_color << 4) | this->second_color));
    for (int i = 0; i < this->from; i++) {
        std::cout << this->text.at(i);
    }

    SetConsoleTextAttribute(hConsole, (WORD) ((this->second_color << 4) | this->first_color));
    for (int i = this->from; i < this->to; i++) {
        std::cout << this->text.at(i);
    }

    SetConsoleTextAttribute(hConsole, (WORD) ((this->first_color << 4) | this->second_color));
    for (int i = to; i < this->text.size(); i++) {
        std::cout << this->text.at(i);
    }

    SetConsoleTextAttribute(hConsole, (WORD) ((this->console_bg << 4) | this->console_fg));

    std::cout << std::endl;
}

void menu_element::enter() {
    (*this->foo)();
}

boolean menu_element::set_from(uint16_t _from) {
    if (_from < text.size()) {
        this->from = _from;
        return true;
    }
    return false;
}

boolean menu_element::set_to(uint16_t _to) {
    if (_to < text.size()) {
        this->to = _to;
        return true;
    }
    return false;
}

void menu_element::setFirstColor(Color color) {
    this->first_color = color;
}

void menu_element::setSecondColor(Color color) {
    this->second_color = color;
}

void menu_element::SetConsoleBg(Color bg) {
    menu_element::console_bg = bg;
}

void menu_element::SetConsoleFg(Color fg) {
    menu_element::console_fg = fg;
}

bool menu_element::get_is_back() {
    return this->is_back;
}


