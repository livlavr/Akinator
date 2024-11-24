#include <stdio.h>
#include <unistd.h>

#include "custom_asserts.h"
#include "tree.h"
#include "Akinator.h"
#include "UserInterface.h"
#include "DataBase.h"

TYPE_OF_ERROR AkinatorInit(Akinator* akinator, int argc, char** argv) {
    akinator->tree = (Tree<char*>*)calloc(1, sizeof(Tree<char*>));
    char* root_value = (char*)calloc(30, 1);
    SetDataBase(akinator, argc, argv);
    // strcpy(root_value, "хуй пойми кто");
    // TreeInit(akinator->tree, root_value);//TODO

    return SUCCESS;
}

TYPE_OF_ERROR StartGame(Akinator* akinator) {
    check_expression(akinator, POINTER_IS_NULL);

    switch(akinator->game_mode) {
        case play_akinator:
            PlayAkinator(akinator, akinator->tree->root);
            return SUCCESS;
        case description:
            GetDescription(akinator);
            return SUCCESS;
        case quit_and_save:
            UpdateDataBase(akinator);
        case quit:
            QuitWithoutSaving(akinator);
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
        printf("\nТы загадал %s? [д/н] ", node->value);
        switch(GetAnswer()) {
            case yes:
                printf("ГООООООООООООЛ, ну это было легко)\n");
                sleep(1);

                return SUCCESS;
            case no:
                AddCharacter(akinator, node);

                return SUCCESS;
            case zaebal:
                return SUCCESS;
            default:
                printf("Упс, что-то случилсоь :(\n");

                warning(false, PROGRAM_ERROR);
        }
    }
    else {
        printf("\n%s? [д/н] ", node->value);
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

        else if(tries_balance > 3 && tries_balance <= 10) {
            printf("Бро хватит, у тебя осталось %d попыток. "
                    "Просто введи \"д\" или \"н\" вот сюда -> ",
                    tries_balance);
        }

        else if(tries_balance > 1){
            printf("Ты решил мне нервы потрепать? Ок. Осталось %d попыток [д/н] ",
                    tries_balance);
        }
        else if(tries_balance == 1){
            printf("Даю последний шанс [д/н] ");
        }

        akinator_patience++;
    }

    if(answer[1] != YES && answer[1] != NO) {
        printf("Всё, заебал...\n");
        sleep(1);

        return zaebal;
    }
    else {
        if(answer[1] == YES) return yes;
        else                 return no;
    }

    return no;
}

TYPE_OF_ERROR AddCharacter(Akinator* akinator, TreeNode<char*>* node) {
    check_expression(akinator, POINTER_IS_NULL);
    check_expression(node,     POINTER_IS_NULL);

    char* character = (char*)calloc(MAX_VALUE_SIZE, sizeof(char));
    char* attribute = (char*)calloc(MAX_VALUE_SIZE, sizeof(char));
    printf("\nКошачий случай... А кого ты загадал?\n");
    _ScanAnswer(character); //TODO how to do normal scanf limit

    printf("Хмхмхм, а чем это отличается от того, что я предложил?\n");
    _ScanAnswer(attribute);

    ConnectCharacterToTree(akinator, node, attribute, character);
    printf("Окей, я запомнил ;)\n");

    sleep(1);

    TreeDump(akinator->tree);

    return SUCCESS;
}

inline void CleanBuffer() {
    char simbol = 0;
    while((simbol = getchar()) != '\n' && simbol != EOF) {}
}

TYPE_OF_ERROR ConnectCharacterToTree(Akinator* akinator, TreeNode<char*>* node,
                                     char* attribute, char* character) {
    check_expression(akinator, POINTER_IS_NULL);
    check_expression(node,     POINTER_IS_NULL);

    if(!node->parent) {
        LinkRootCharacter(akinator, node, attribute, character);
    }
    else {
        LinkCharacter    (akinator, node, attribute, character);
    }

    return SUCCESS;
}

TYPE_OF_ERROR LinkRootCharacter(Akinator* akinator, TreeNode<char*>* node,
                                char* attribute, char* character) {
    check_expression(akinator,  POINTER_IS_NULL);
    check_expression(node,      POINTER_IS_NULL);
    check_expression(attribute, POINTER_IS_NULL);

    TreeNode<char*>* attribute_node = NULL;
    CreateNode<char*>(&attribute_node, attribute);
    TreeNode<char*>* character_node = NULL;
    CreateNode<char*>(&character_node, character);


    _WhaitForValidAnswer(LinkNodes<char*>(attribute_node, node, LEFT_SIDE),
                        attribute_node, attribute, NO_TREE_ERRORS,
                        "Упс, в акинаторе уже есть %s, придумай что-нибудь другое:\n");

    _WhaitForValidAnswer(LinkNodes<char*>(attribute_node, character_node, RIGHT_SIDE),
                        character_node, character, NO_TREE_ERRORS,
                        "Упс, в акинаторе уже есть %s, придумай что-нибудь другое:\n");

    akinator->tree->root = attribute_node;

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
    _WhaitForValidAnswer(LinkNodes<char*>(node->parent, attribute_node, side),
                        attribute_node, attribute, NO_TREE_ERRORS,
                        "Упс, в акинаторе уже есть %s, придумай что-нибудь другое:\n");

    TreeNode<char*>* character_node = NULL;
    CreateNode<char*>(&character_node, character);
    _WhaitForValidAnswer(LinkNodes<char*>(attribute_node, node, LEFT_SIDE),
                        attribute_node, attribute, NO_TREE_ERRORS,
                        "Упс, в акинаторе уже есть %s, придумай что-нибудь другое:\n");

    _WhaitForValidAnswer(LinkNodes<char*>(attribute_node, character_node, RIGHT_SIDE),
                        character_node, character, NO_TREE_ERRORS,
                        "Упс, в акинаторе уже есть %s, придумай что-нибудь другое:\n");
    TreeDump(akinator->tree);

    return SUCCESS;
}

TYPE_OF_ERROR QuitWithoutSaving(Akinator* akinator) {
    check_expression(akinator, POINTER_IS_NULL);

    // TreeDtor    (akinator->tree);
    // AkinatorDtor(akinator);//TODO

    return SUCCESS;
}

TYPE_OF_ERROR GetDescription(Akinator* akinator) {
    char character[MAX_VALUE_SIZE]  = "";
    TreeNode<char*>* character_node = NULL;
    TreeNode<char*>* original_node  = NULL;
    _ScanAnswer(character);
    CreateNode<char*>(&character_node, character);

    while(!original_node) {
        printf("Ой, я таких не знаю, спроси про кого-нибудь другого\n");
        _ScanAnswer(character);
        character_node->value = character;
        character_node->hash  = Hash(character);
        FindCharacter(akinator->tree->root, character_node, &original_node);
    }

    stack* way_to_node = NULL;
    stack_init(way_to_node, 10);

    GetWayToNode(way_to_node, character_node);

    stack_destroy(way_to_node);

    return SUCCESS;
}

TYPE_OF_ERROR FindCharacter(TreeNode<char*>* node, TreeNode<char*>* character_node, TreeNode<char*>** original_node) {
    if(!node) return SUCCESS;

    if(node->hash == character_node->hash) {
        if(strcmp(node->value, character_node->value) == 0) {
            *original_node = node;
        }
    }
    FindCharacter(node->left, character_node, original_node);
    if(!original_node) {
        FindCharacter(node->right, character_node, original_node);
    }

    return SUCCESS;
}



TYPE_OF_ERROR GetWayToNode(stack* way_to_node, TreeNode<char*>* node) {

    if(node->parent) {
        if(node->parent->left == node) {
//TODO
        }
    }

    return SUCCESS;
}

TYPE_OF_ERROR AkinatorDtor(Akinator* akinator) {
    // TreeDtor(akinator->tree);//TODO flags in node structure
    free(akinator->input_data_base );
    free(akinator->output_data_base);

    return SUCCESS;
}
