#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>

#include "custom_asserts.h"
#include "tree.h"
#include "Akinator.h"
#include "UserInterface.h"
#include "DataBase.h"

TYPE_OF_ERROR AkinatorInit(Akinator* akinator, int argc, char** argv) {
    akinator->tree = (Tree<char*>*)calloc(1, sizeof(Tree<char*>));

    SetDataBase(akinator, argc, argv);
    ReadDataBase(akinator);

    return SUCCESS;
}

TYPE_OF_ERROR StartGame(Akinator* akinator) {
    check_expression(akinator, POINTER_IS_NULL);

    switch(akinator->game_mode) {
        case play_akinator:
            system("clear");
            PlayAkinator(akinator, akinator->tree->root);
            return SUCCESS;
        case description:
            system("clear");
            GetDescription(akinator);
            return SUCCESS;
        case compare:
            system("clear");
            CompareCharacters(akinator);
            return SUCCESS;
        case watch_tree:
            system("clear");
            OpenDump(akinator->tree);
            return SUCCESS;
        case save:
            system("clear");
            UpdateDataBase(akinator);
            printf("415 база ответьте\n");
            sleep(1);
            return SUCCESS;
        case install:
            system("clear");
            InstallDataBase(akinator);
            printf("Подгрузил нейросетку\n");
            sleep(1);
            return SUCCESS;
        case quit_and_save:
            UpdateDataBase(akinator);
        case quit:
            AkinatorDtor(akinator);
            return SUCCESS;
        default:
            warning(false, PROGRAM_ERROR);
    }

    return SUCCESS;
}

TYPE_OF_ERROR PlayAkinator(Akinator* akinator, TreeNode<char*>* node) {
    check_expression(akinator, POINTER_IS_NULL);
    check_expression(node,     POINTER_IS_NULL);

    if(!(node->left || node->right)) {
        printf("Ты загадал %s? [д/н] ", node->value);
        switch(GetAnswer()) {
            case yes:
                color_printf(GREEN_TEXT, BOLD, "ГООООООООООООЛ, ну это было легко)\n");
                sleep(1);

                return SUCCESS;
            case no:
                AddCharacter(akinator, node);

                return SUCCESS;
            case zaebal:
                return SUCCESS;
            default:
                color_printf(RED_TEXT, BOLD, "Упс, что-то случилсоь :(\n");

                warning(false, PROGRAM_ERROR);
        }
    }
    else {
        printf("%s? [д/н] ", node->value);
        switch(GetAnswer()) {
        case yes:
            PlayAkinator(akinator, node->right);
            break;
        case no:
            PlayAkinator(akinator, node->left);
            break;
        }
    }

    return SUCCESS;
}

UserAnswer GetAnswer() {
    char answer[MAX_VALUE_SIZE] = ""; //TODO value size and answersize
    int  akinator_patience      = 0;
    int  tries_balance          = 0;

    while(akinator_patience <= MAX_TRIES_NUMBER) {
        tries_balance = MAX_TRIES_NUMBER - akinator_patience;
        scanf("%s", answer);
        if(answer[1] == YES || answer[1] == NO) break;

        if(tries_balance > 10) {
            printf("Что-то я не понял, так да или нет? [д/н] ");
        }

        else if(tries_balance > 5 && tries_balance <= 10) {
            color_printf(GREEN_TEXT, BOLD, "Бро хватит, у тебя осталось %d попыток. "
                    "Просто введи \"д\" или \"н\" вот сюда -> ",
                    tries_balance);
        }

        else if(tries_balance > 1){
            color_printf(YELLOW_TEXT, BOLD, "Ты решил мне нервы потрепать? Ок. Осталось %d попыток [д/н] ",
                    tries_balance);
        }
        else if(tries_balance == 1){
            color_printf(RED_TEXT, BOLD, "Даю тебе последний шанс, шутник хуев [д/н] ");
        }

        akinator_patience++;
    }

    if(answer[1] != YES && answer[1] != NO) {
        PrintHui();
        color_printf(RED_TEXT, BOLD, "Всё, заебал...\n");
        sleep(4);

        return zaebal;
    }
    else {
        if(answer[1] == YES) return yes;
        else                 return no;
    }

    return no;
}

void PrintHui() {
    color_printf(RED_TEXT, BOLD,
"⠀⠀⠀⠀⠀⠀⢀⣤⣶⣶⣾⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⣠⣾⡿⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⣰⣿⠆⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⢻⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⣠⣾⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠻⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⠗⠀⠀⠀⣿⣿⠀⠀⢀⣾⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠈⠻⢿⣷⣦⣄⡀⠀⠀⠀⠀⠀⠀⣶⣦⠀⠀⠀⠀⠀⠀⠀⣾⣿⠀⠀⠀⠀⠀⠀⣴⣿⠟⠁⠀⠀⠀⠀⣿⣿⠀⣰⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠈⠙⠻⣿⣷⣄⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣼⣿⠋⠀⠀⠀⠀⠀⠀⢹⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⠇⠀⠀⠹⣿⡆⠀⠀⠀⠀⣸⣿⠇⢹⣿⡀⠀⠀⢸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠈⣿⡇⠉⠛⠛⢿⣿⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⡿⠋⠀⠀⠀⠀⢻⣿⡄⠀⢀⣴⣿⠏⠀⠘⣿⣧⠀⠀⠘⣿⣷⡀⠀⢀⣤⣶⡄⠀⠀⣿⡇⠀⠀⠀⠀⠈⠙⠿⣿⣦⣄⡀⠀⠀⠀⠀\n"
"⠀⣤⣤⣤⣤⣤⣤⣤⣴⣾⡿⠛⠀⠀⠀⠀⠀⠀⠀⠻⣿⣶⣿⡿⠃⠀⠀⠀⠹⣿⠆⠀⠀⠈⠻⢿⣿⡿⠟⠉⠀⠀⠀⣿⡷⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠛⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⢀⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠈⣿⣿⣷⡄⠀⠀⠀⠀⠀⢠⣿⠏⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⣿⣿⢿⣷⡄⠀⠀⠀⢀⣾⣿⠀⣿⣿⠀⠀⠀⢠⣤⡀⠀⠀⠀⠀⠀⠀⠀⣻⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⣿⣿⠀⠈⢿⣿⡀⢀⣿⡿⠀⠀⢸⣿⡆⠀⠀⠀⠈⢿⣷⣄⠀⠀⠀⠀⢰⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⣿⣿⠀⠀⠀⠸⣿⣿⡏⠀⠀⠀⠀⣿⣷⠀⠀⠀⠀⠀⠀⠙⣿⣧⡀⠀⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠻⠟⠁⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣾⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠈⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣶⡄⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⢀⣴⣾⣿⣿⣿⣿⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠘⣿⣿⠀⠀⠀⠀⠉⠻⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣯⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠈⢿⣷⡄⠀⠀⠺⠟⠀⠀⠀⠀⠀⠀⢸⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⢺⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⢠⣤⡄⠀⠀⠀⠀⢘⣿⡇⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⣹⣿⠀⠀⠀⢀⣤⡀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣴⣶⣶⠆⠀⠀⠀⠀⢸⣿⡇⠀⠀⣰⣿⠟⠀⠀⠀⠀⠀⠀⣿⣷⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠸⣿⡇⠀⠀⠀⠀⠀⢀⣾⡿⠃⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⣼⣿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⣿⣇⠀⠀⠀⠀⢠⣾⡿⠁⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣷⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⣰⣿⡟⠀⠀⠀⠀⠀⠀⠸⣿⡇⠀⠀⠀⠀⢻⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⢸⣿⡟⠻⠿⣿⣷⣶⣦⣤⣄⣀⣀⡀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⣿⣿⠀⢀⣴⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠉⠻⣿⣷⣦⣤⣤⣤⣴⣿⡿⠀⠀⠀⢿⡇⠀⠀⠀⠈⠉⠙⠛⠛⠛⠛⠃⠀⠀⠀⣤⡄\n"
"⠀⠀⠀⠀⠀⠀⢹⣿⣶⣿⠿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠛⠙⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀\n"
"⠀⠀⠀⠀⠀⠀⠈⠻⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\n");
}

TYPE_OF_ERROR AddCharacter(Akinator* akinator, TreeNode<char*>* node) {
    check_expression(akinator, POINTER_IS_NULL);
    check_expression(node,     POINTER_IS_NULL);

    char* character = (char*)calloc(MAX_VALUE_SIZE, sizeof(char));
    char* attribute = (char*)calloc(MAX_VALUE_SIZE, sizeof(char));

    color_printf(YELLOW_TEXT, BOLD, "\nКошачий случай... А кого ты загадал?\n");
    _ScanAnswer(character); //TODO how to do normal (const) scanf limit
    _WhaitForValidAnswer(FindValueInTree(akinator->tree->root, character, Hash(character)),
                        character, SUCCESS, "Упс, в акинаторе уже есть %s, придумай что-нибудь другое\n");

    color_printf(YELLOW_TEXT, BOLD, "Хмхмхм, а чем это отличается от того, что я предложил?\n");
    _ScanAnswer(attribute);
    _WhaitForValidAnswer(FindValueInTree(akinator->tree->root, attribute, Hash(attribute)),
                        attribute, SUCCESS, "Упс, в акинаторе уже есть %s, придумай что-нибудь другое\n");

    if(!node->parent) {
        LinkRootCharacter(akinator, node, attribute, character);
    }
    else {
        LinkCharacter    (akinator, node, attribute, character);
    }

    color_printf(GREEN_TEXT, BOLD, "Окей, я запомнил ;)\n");

    sleep(1);

    TreeDump(akinator->tree);

    return SUCCESS;
}

void CleanBuffer() {
    char simbol = 0;
    while((simbol = getchar()) != '\n' && simbol != EOF) {}
}

TYPE_OF_ERROR FindValueInTree(TreeNode<char*>* node, char* value, uint32_t hash) {
    if(!node) return SUCCESS;

    if(node->hash == hash) {
        if(strcmp(node->value, value) == 0) {
            return INPUT_ERROR;
        }
    }

    if(FindValueInTree(node->left, value, hash) == SUCCESS) {
        return FindValueInTree(node->right, value, hash);
    }

    return INPUT_ERROR;

}

TYPE_OF_ERROR LinkRootCharacter(Akinator* akinator, TreeNode<char*>* node,
                                char* attribute, char* character) {
    check_expression(akinator,  POINTER_IS_NULL);
    check_expression(node,      POINTER_IS_NULL);
    check_expression(attribute, POINTER_IS_NULL);

    TreeNode<char*>* attribute_node = NULL;
    CreateNode<char*>(&attribute_node, attribute);
    LinkNodes<char*>(attribute_node, node, LEFT_SIDE);

    akinator->tree->root = attribute_node;

    _WhaitForValidAnswer(FindValueInTree(akinator->tree->root, character, Hash(character)),
                        character, SUCCESS, "Упс, в акинаторе уже есть %s, придумай что-нибудь другое\n");

    TreeNode<char*>* character_node = NULL;
    CreateNode<char*>(&character_node, character);
    LinkNodes<char*>(attribute_node, character_node, RIGHT_SIDE);

    return SUCCESS;
}

TYPE_OF_ERROR LinkCharacter(Akinator* akinator, TreeNode<char*>* node,
                                char* attribute, char* character) {
    check_expression(akinator,  POINTER_IS_NULL);
    check_expression(node,      POINTER_IS_NULL);
    check_expression(attribute, POINTER_IS_NULL);

    int side = 0;
    if(node->parent->right == node) {
        side = RIGHT_SIDE;
        node->parent->right = NULL;
    }
    else {
        side = LEFT_SIDE;
        node->parent->left = NULL;
    }

    TreeNode<char*>* attribute_node = NULL;
    CreateNode<char*>(&attribute_node, attribute);
    LinkNodes<char*>(node->parent, attribute_node, side);

    LinkNodes<char*>(attribute_node, node, LEFT_SIDE);

    _WhaitForValidAnswer(FindValueInTree(akinator->tree->root, character, Hash(character)),
                        character, SUCCESS, "Упс, в акинаторе уже есть %s, придумай что-нибудь другое\n");

    TreeNode<char*>* character_node = NULL;
    CreateNode<char*>(&character_node, character);
    LinkNodes<char*>(attribute_node, character_node, RIGHT_SIDE);

    TreeDump(akinator->tree);

    return SUCCESS;
}

TYPE_OF_ERROR GetDescription(Akinator* akinator) {
    check_expression(akinator, POINTER_IS_NULL);

    color_printf(GREEN_TEXT, BOLD, "Чьё описание хочешь?\n");

    stack* way_to_node    = NULL;
    stack_init(way_to_node, 10);
    TreeNode<char*>* node = NULL;

    node = FindCharacter(akinator, way_to_node);

    printf("%s - ", node->value);
    PrintDescription(way_to_node, akinator->tree->root);
    printf("\n");

    stack_destroy(way_to_node);

    _WaitForAnswer();

    return SUCCESS;
}

TYPE_OF_ERROR FindNode(TreeNode<char*>* node, TreeNode<char*>* character_node, TreeNode<char*>** original_node) {
    if(!node) return SUCCESS;

    if(node->hash == character_node->hash) {
        if(strcmp(node->value, character_node->value) == 0) {
            *original_node = node;
            return SUCCESS;
        }
    }
    FindNode(node->left, character_node, original_node);
    if(!(*original_node)) {
        FindNode(node->right, character_node, original_node);
    }

    return SUCCESS;
}

TYPE_OF_ERROR PrintDescription(stack* way_to_node, TreeNode<char*>* node) {
    check_expression(way_to_node, POINTER_IS_NULL);
    if(!stack_size(way_to_node)) return SUCCESS;
    if(!node)                    return SUCCESS;

    int direction = 0;
    pop(way_to_node, &direction);
    if(direction == RIGHT_SIDE) {
        if(stack_size(way_to_node)) color_printf(GREEN_TEXT, REGULAR, "%s, ", node->value);
        else                        color_printf(GREEN_TEXT, REGULAR, "%s ", node->value);
        PrintDescription(way_to_node, node->right);
    }
    else {
        if(stack_size(way_to_node)) color_printf(RED_TEXT, REGULAR, "не %s, ", node->value);
        else                        color_printf(RED_TEXT, REGULAR, "не %s ", node->value);
        PrintDescription(way_to_node, node->left);
    }

    return SUCCESS;
}

TYPE_OF_ERROR GetWayToNode(stack* way_to_node, TreeNode<char*>* node) {

    if(node->parent) {
        if(node->parent->left == node) {
            push(way_to_node, LEFT_SIDE);
            GetWayToNode(way_to_node, node->parent);
        }
        else {
            push(way_to_node, RIGHT_SIDE);
            GetWayToNode(way_to_node, node->parent);
        }
    }

    return SUCCESS;
}

TreeNode<char*>* FindCharacter(Akinator* akinator, stack* way_to_node) {
    check_expression(akinator,    NULL);
    check_expression(way_to_node, NULL);

    char*            character      = (char*)calloc(MAX_VALUE_SIZE, sizeof(char));
    TreeNode<char*>* character_node = NULL;
    TreeNode<char*>* original_node  = NULL;
    _ScanAnswer(character);
    CreateNode<char*>(&character_node, character);
    FindNode(akinator->tree->root, character_node, &original_node);

    while(!original_node) {
        color_printf(RED_TEXT, REGULAR, "Слушай a эо ты бля я ээээээ таких не знаю давай другого загадывай (prod max zubaha)\n");
        _ScanAnswer(character);
        character_node->value = character;
        character_node->hash  = Hash(character);
        FindNode(akinator->tree->root, character_node, &original_node);
    }

    GetWayToNode(way_to_node, original_node);

    NodesDtor<char*>(&character_node);

    return original_node;
}

TYPE_OF_ERROR CompareCharacters(Akinator* akinator) {
    check_expression(akinator, POINTER_IS_NULL);

    color_printf(GREEN_TEXT, BOLD, "Введи первого персонажа для сравнения\n");

    stack* way1            = NULL;
    stack_init(way1, 10);
    TreeNode<char*>* node1 = NULL;

    node1 = FindCharacter(akinator, way1);

    color_printf(GREEN_TEXT, BOLD, "С кем мне его сравнить?\n");

    stack* way2          = NULL;
    stack_init(way2, 10);
    TreeNode<char*>* node2 = NULL;

    node2 = FindCharacter(akinator, way2);

    color_printf(YELLOW_TEXT, BOLD, "%s и %s похожи тем, что они:\n", node1->value, node2->value);
    PrintComparing(akinator->tree->root, way1, way2, node1->value, node2->value);
    printf("\n");

    stack_destroy(way1);
    stack_destroy(way2);

    _WaitForAnswer();

    return SUCCESS;
}

TYPE_OF_ERROR PrintComparing(TreeNode<char*>* node, stack* way1, stack* way2, char* value1, char* value2) {
    check_expression(value1, POINTER_IS_NULL);
    check_expression(value2, POINTER_IS_NULL);
    check_expression(way1,   POINTER_IS_NULL);
    check_expression(way2,   POINTER_IS_NULL);
    if(!stack_size(way1))    return SUCCESS;
    if(!stack_size(way2))    return SUCCESS;
    if(!node)                return SUCCESS;

    int direction1 = 0;
    int direction2 = 0;

    pop(way1, &direction1);
    pop(way2, &direction2);
    if(direction1 == direction2) {
        if(direction1 == RIGHT_SIDE) {
            if(stack_size(way1)) color_printf(GREEN_TEXT, REGULAR, "%s, ", node->value);
            else                 color_printf(GREEN_TEXT, REGULAR, "%s ",  node->value);
            PrintComparing(node->right, way1, way2, value1, value2);
        }
        else {
        if(stack_size(way1)) color_printf(RED_TEXT, REGULAR, "не %s, ", node->value);
        else                 color_printf(RED_TEXT, REGULAR, "не %s ",  node->value);
        PrintComparing(node->left, way1, way2, value1, value2);
        }
    }
    else {
        push(way1, direction1);
        push(way2, direction2);
        color_printf(YELLOW_TEXT, BOLD, "\nОтличаются тем, что:");
        printf("\n%s - ", value1);
        PrintDescription(way1, node);
        printf("\n%s - ", value2);
        PrintDescription(way2, node);
    }

    return SUCCESS;
}

TYPE_OF_ERROR AkinatorDtor(Akinator* akinator) {
    check_expression(akinator, POINTER_IS_NULL);
    TreeDtor(akinator->tree);//TODO flags in node structure
    free(akinator->input_data_base );
    free(akinator->output_data_base);

    return SUCCESS;
}
