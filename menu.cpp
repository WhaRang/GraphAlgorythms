/**
 * Created by Aiaksei Tokarau on 3/4/2020.
 *
 * @file menu.cpp
 *
 * Implementation of methods declared in "menu.h".
 */

#include "menu.h"

menu::menu(std::vector<menu_element> elements) {
    this->elements = std::move(elements);
    this->selected = 0;
    this->skippable = false;
}

void menu::run() {
    menu::was_run = true;
    int key = 1;
    this->build();
    while (key != ESC) {
        key = _getch();
        if (key == ARROW_KEY) {
            key = _getch();
            switch (key) {
                case UP: {
                    this->prev();
                    break;
                }
                case DOWN: {
                    this->next();
                    break;
                }
                default: {
                    break;
                }
            }
        }
        if (key == ENTER) {
            system("cls");
            this->enter();
            this->selected = 0;
            return;
        }
    }
}

void menu::prev() {
    if (this->selected > 0) {
        this->selected--;
    } else {
        if (this->skippable && (this->selected == 0)) {
            this->selected = (this->elements.size() - 1);
        }
    }
    this->build();
}

void menu::next() {
    if (this->selected < (this->elements.size() - 1)) {
        this->selected++;
    } else {
        if (this->skippable && (this->selected == (this->elements.size() - 1))) {
            this->selected = 0;
        }
    }
    this->build();
}

void menu::enter() {
    menu::was_run = false;
    if (!elements.at(this->selected).get_is_back()) {
        this->elements.at(this->selected).enter();
    } else {
        return;
    }
    /**
     * if (!menu::was_run) {
        int key = 1;
        while (key != ESC) {
            key = _getch();
        }
    }
     */
    this->run();
}

void menu::build() {
    system("cls");
    for (int i = 0; i < this->elements.size(); i++) {
        if (i == this->selected) {
            this->elements.at(i).print_selected();
        } else {
            this->elements.at(i).print_unselected();
        }
    }
}

boolean menu::was_run = true;

void menu::set_skippable(boolean skippable) {
    this->skippable = skippable;
}

