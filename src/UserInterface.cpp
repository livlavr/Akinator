#include <stdio.h>

#include "tree.h"
#include "custom_asserts.h"
#include "color_printf.h"
#include "Akinator.h"
#include "UserInterface.h"


TYPE_OF_ERROR MainMenu(Akinator* akinator) {
    PrintMenu();
    Loading();
    ChooseGameMode(akinator);

    return SUCCESS;
}

void PrintMenu() {
    PrintLogo   ();
    Loading     ();
    PrintOptions();
}

void PrintLogo() {
    color_printf(RED_TEXT, BOLD, "▗▄▄▄  ▗▄▄▄▖▗▄▄▄▖ ▗▄▖ ▗▖  ▗▖ ▗▄▖▗▄▄▄▖▗▄▖ ▗▄▄▖ \n"
                                 "▐▌  █ ▐▌     █  ▐▌ ▐▌▐▛▚▖▐▌▐▌ ▐▌ █ ▐▌ ▐▌▐▌ ▐▌\n"
                                 "▐▌  █ ▐▛▀▀▘  █  ▐▌ ▐▌▐▌ ▝▜▌▐▛▀▜▌ █ ▐▌ ▐▌▐▛▀▚▖\n"
                                 "▐▙▄▄▀ ▐▙▄▄▖  █  ▝▚▄▞▘▐▌  ▐▌▐▌ ▐▌ █ ▝▚▄▞▘▐▌ ▐▌\n\n");
}

void Loading() {
   return;
}

void PrintOptions() {
    color_printf(GREEN_TEXT,  BOLD, "Играть в акинатора               [1]\n");
    color_printf(GREEN_TEXT,  BOLD, "Описание персонажа               [2]\n");
    color_printf(GREEN_TEXT,  BOLD, "Сравнить персонажей              [3]\n");
    color_printf(GREEN_TEXT,  BOLD, "Сохранить базу данных            [4]\n");
    color_printf(GREEN_TEXT,  BOLD, "Загрузить базу данных            [5]\n");
    color_printf(GREEN_TEXT,  BOLD, "Посмотреть дерево акинатора      [6]\n");
    color_printf(YELLOW_TEXT, BOLD, "Выйти и сохранить                [7]\n");
    color_printf(RED_TEXT,    BOLD, "Выйти без сохранения             [8]\n");
}

TYPE_OF_ERROR ChooseGameMode(Akinator* akinator) {
    int answer = 0;
    while(1) {
        _ModeSelection();
        }

    return SUCCESS;
}
