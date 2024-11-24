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
    // ReadDataBase(&akinator);
    OpenDump(akinator.tree);
    // AkinatorDtor(&akinator); //TODO we have to calloc in readbase
}
