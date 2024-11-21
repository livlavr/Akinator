#include <stdio.h>

#include "custom_asserts.h"
#include "tree.h"
#include "akinator.h"
#include "user_interface.h"

int main() {
    Akinator akinator = {};
    AkinatorInit(&akinator);
    do {
        MainMenu(&akinator);
        StartGame(&akinator);
    } while(akinator.game_mode != quit_without_saving && akinator.game_mode != quit);

    AkinatorDtor(&akinator);
}
