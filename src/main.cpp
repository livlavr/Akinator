#include <stdio.h>

#include "custom_asserts.h"
#include "tree.h"
#include "Akinator.h"
#include "UserInterface.h"
#include "DataBase.h"

int main(int argc, char** argv) {
    Akinator akinator = {};
    AkinatorInit(&akinator, argc, argv);
    // do {
    //     MainMenu(&akinator);
    //     StartGame(&akinator);
    // } while(akinator.game_mode != quit_without_saving && akinator.game_mode != quit);
    ReadDataBase(&akinator);
    OpenDump(akinator.tree);
    // printf("%d\n", akinator.game_mode);
    // printf("%s\n", akinator.input_data_base);
    // printf("%s\n", akinator.output_data_base);
    akinator.game_mode = quit_without_saving;
    // AkinatorDtor(&akinator); //TODO we have to calloc in readbase
}
