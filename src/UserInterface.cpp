#include <stdio.h>

#include "tree.h"
#include "custom_asserts.h"
#include "color_printf.h"
#include "Akinator.h"
#include "UserInterface.h"


TYPE_OF_ERROR MainMenu(Akinator* akinator) {
    system("clear");
    PrintMenu();
    ChooseGameMode(akinator);

    return SUCCESS;
}

void PrintMenu() {
    PrintLogo   ();
    Loading     ();
    PrintOptions();
}

void PrintLogo() {
    // color_printf(RED_TEXT, BOLD, "▗▄▄▄  ▗▄▄▄▖▗▄▄▄▖ ▗▄▖ ▗▖  ▗▖ ▗▄▖▗▄▄▄▖▗▄▖ ▗▄▄▖ \n"
    //                              "▐▌  █ ▐▌     █  ▐▌ ▐▌▐▛▚▖▐▌▐▌ ▐▌ █ ▐▌ ▐▌▐▌ ▐▌\n"
    //                              "▐▌  █ ▐▛▀▀▘  █  ▐▌ ▐▌▐▌ ▝▜▌▐▛▀▜▌ █ ▐▌ ▐▌▐▛▀▚▖\n"
    //                              "▐▙▄▄▀ ▐▙▄▄▖  █  ▝▚▄▞▘▐▌  ▐▌▐▌ ▐▌ █ ▝▚▄▞▘▐▌ ▐▌\n\n");
    color_printf(RED_TEXT, BOLD,"\n\n\t\t\t\t\t      ⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                                "\t\t\t\t\t      ⠀⠀⠀⠀⠀⢰⡿⠋⠁⠀⠀⠈⠉⠙⠻⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                                "\t\t\t\t\t      ⠀⠀⠀⠀⢀⣿⠇⠀⢀⣴⣶⡾⠿⠿⠿⢿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                                "\t\t\t\t\t      ⠀⠀⣀⣀⣸⡿⠀⠀⢸⣿⣇⠀⠀⠀⠀⠀⠀⠙⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                                "\t\t\t\t\t      ⠀⣾⡟⠛⣿⡇⠀⠀⢸⣿⣿⣷⣤⣤⣤⣤⣶⣶⣿⠇⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀\n"
                                "\t\t\t\t\t      ⢀⣿⠀⢀⣿⡇⠀⠀⠀⠻⢿⣿⣿⣿⣿⣿⠿⣿⡏⠀⠀⠀⠀⢴⣶⣶⣿⣿⣿⣆\n"
                                "\t\t\t\t\t      ⢸⣿⠀⢸⣿⡇⠀⠀⠀⠀⠀⠈⠉⠁⠀⠀⠀⣿⡇⣀⣠⣴⣾⣮⣝⠿⠿⠿⣻⡟\n"
                                "\t\t\t\t\t      ⢸⣿⠀⠘⣿⡇⠀⠀⠀⠀⠀⠀⠀⣠⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠉⠀\n"
                                "\t\t\t\t\t      ⠸⣿⠀⠀⣿⡇⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠉⠀⠀⠀⠀\n"
                                "\t\t\t\t\t      ⠀⠻⣷⣶⣿⣇⠀⠀⠀⢠⣼⣿⣿⣿⣿⣿⣿⣿⣛⣛⣻⠉⠁⠀⠀⠀⠀⠀⠀⠀\n"
                                "\t\t\t\t\t      ⠀⠀⠀⠀⢸⣿⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀\n"
                                "\t\t\t\t\t      ⠀⠀⠀⠀⢸⣿⣀⣀⣀⣼⡿⢿⣿⣿⣿⣿⣿⡿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                                "\t\t\t\t\t      ⠀⠀⠀⠀⠀⠙⠛⠛⠛⠋⠁⠀⠙⠻⠿⠟⠋⠑⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    color_printf(RED_TEXT, BOLD, "\t\t\t\t   ▄▄▖ ▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▄▄▄▖▗▄▄▖  ▗▄▖▗▄▄▄▖▗▄▖ ▗▄▄▖\n"
                                 "\t\t\t\t  ▐▌ ▐▌▐▌   ▐▛▚▖▐▌  █    █  ▐▌ ▐▌▐▌ ▐▌ █ ▐▌ ▐▌▐▌ ▐▌\n"
                                 "\t\t\t\t  ▐▛▀▘ ▐▛▀▀▘▐▌ ▝▜▌  █    █  ▐▛▀▚▖▐▛▀▜▌ █ ▐▌ ▐▌▐▛▀▚▖\n"
                                 "\t\t\t\t  ▐▌   ▐▙▄▄▖▐▌  ▐▌▗▄█▄▖  █  ▐▌ ▐▌▐▌ ▐▌ █ ▝▚▄▞▘▐▌ ▐▌\n\n\n\n");
}

void Loading() {
   return;
}

void PrintOptions() {
    color_printf(GREEN_TEXT,  BOLD, "\t\t\t\t\tИграть в акинатора               [1]\n");
    color_printf(GREEN_TEXT,  BOLD, "\t\t\t\t\tОписание персонажа               [2]\n");
    color_printf(GREEN_TEXT,  BOLD, "\t\t\t\t\tСравнить персонажей              [3]\n");
    color_printf(GREEN_TEXT,  BOLD, "\t\t\t\t\tСохранить базу данных            [4]\n");
    color_printf(GREEN_TEXT,  BOLD, "\t\t\t\t\tЗагрузить базу данных            [5]\n");
    color_printf(GREEN_TEXT,  BOLD, "\t\t\t\t\tПосмотреть дерево акинатора      [6]\n");
    color_printf(YELLOW_TEXT, BOLD, "\t\t\t\t\tВыйти и сохранить                [7]\n");
    color_printf(RED_TEXT,    BOLD, "\t\t\t\t\tВыйти без сохранения             [8]\n");
}

TYPE_OF_ERROR ChooseGameMode(Akinator* akinator) {
    int answer = 0;
    while(answer <= 0 || answer >= 9) {
        _ModeSelection(answer);
    }
    return SUCCESS;
}
