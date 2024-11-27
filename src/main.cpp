#include <stdio.h>

#include "custom_asserts.h"
#include "tree.h"
#include "Akinator.h"
#include "UserInterface.h"
#include "DataBase.h"

int main(int argc, char** argv) {
    Akinator akinator = {};
    AkinatorInit(&akinator, argc, argv);
    do {
        MainMenu (&akinator);
        StartGame(&akinator);
    } while(akinator.game_mode != quit && akinator.game_mode != quit_and_save);
    AkinatorDtor(&akinator); //TODO
}
