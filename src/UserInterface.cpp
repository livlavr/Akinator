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
    color_printf(GREEN_TEXT, BOLD, "Играть в акинатора               [а]\n");
    color_printf(YELLOW_TEXT,BOLD, "Выйти без сохранения базы данных [в]\n");
    color_printf(RED_TEXT,   BOLD, "Выйти и сохранить                [с]\n");
}

TYPE_OF_ERROR ChooseGameMode(Akinator* akinator) {
    char answer[MAX_VALUE_SIZE] = "";

    while(1) {
        scanf("%s", answer); //TODO Костыль с локализацией
        switch(answer[1]) {
            case PLAY:
                akinator->game_mode = guess_mode;
                return SUCCESS;
            case QUIT_WITHOUT_SAVE:
                akinator->game_mode = quit_without_saving;
                return SUCCESS;
            case QUIT:
                akinator->game_mode = quit;
                return SUCCESS;
            default:
                printf("Не совсем понял тебя, так что делать то будем?\n");
                PrintOptions();
        }
    }

    return SUCCESS;
}
