#include <stdio.h>
#include <unistd.h>

#include "custom_asserts.h"
#include "tree.h"
#include "akinator.h"
#include "user_interface.h"

TYPE_OF_ERROR AkinatorInit(Akinator* akinator) {
    akinator->tree = (Tree<char*>*)calloc(1, sizeof(Tree<char*>));
    char* root_value = (char*)calloc(30, 1);
    strcpy(root_value, "хуй пойми кто");
    TreeInit(akinator->tree, root_value);

    return SUCCESS;
}

TYPE_OF_ERROR GuessMode(Akinator* akinator) {
    PlayAkinator(akinator, akinator->tree->root);

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

    while(akinator_patience < MAX_TRIES_NUMBER) {
        tries_balance = MAX_TRIES_NUMBER - akinator_patience;
        scanf("%s", answer);
        if(answer[1] == YES || answer[1] == NO) break;

        if(tries_balance > 10) {
            printf("\nЧто-то я не понял, так да или нет? [д/н] ");
        }

        else if(3 < tries_balance <= 10) {
            printf("\nБро хватит, у тебя осталось %d попыток."
                    "Просто введи \"д\" или \"н\" вот сюда -> ",
                    tries_balance);
        }

        else if(tries_balance > 1){
            printf("\nТы решил мне нервы потрепать? Ок. Осталось %d попыток [д/н] ",
                    tries_balance);
        }

        akinator_patience++;
    }

    if(answer[1] != YES && answer[1] != NO) {
        printf("\nВсё, заебал...\n");
        sleep(1);

        return no;
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
        LinkCharacter(akinator, node, attribute, character);
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

    akinator->tree->root = attribute_node;

    LinkNodes<char*>(attribute_node, node, LEFT_SIDE);

    LinkNodes<char*>(attribute_node, character_node, RIGHT_SIDE);

    return SUCCESS;
}

TYPE_OF_ERROR LinkCharacter(Akinator* akinator, TreeNode<char*>* node,
                                char* attribute, char* character) {
    check_expression(akinator,  POINTER_IS_NULL);
    check_expression(node,     POINTER_IS_NULL);
    check_expression(attribute, POINTER_IS_NULL);

    int side = 0;
    if(node->parent->right == node) {
        side = RIGHT_SIDE;
        node->parent->right = NULL;
    }
    else {
        side = LEFT_SIDE;
    }

    TreeNode<char*>* attribute_node = NULL;
    CreateNode<char*>(&attribute_node, attribute);
    LinkNodes<char*>(node->parent, attribute_node, side);

    TreeNode<char*>* character_node = NULL;
    CreateNode<char*>(&character_node, character);
    LinkNodes<char*>(attribute_node, character_node, RIGHT_SIDE);
    LinkNodes<char*>(attribute_node, node, LEFT_SIDE);

    return SUCCESS;
}

TYPE_OF_ERROR QuitWithoutSaving(Akinator* akinator) {
    check_expression(akinator, POINTER_IS_NULL);

    TreeDtor    (akinator->tree);
    AkinatorDtor(akinator);

    return SUCCESS;
}

TYPE_OF_ERROR AkinatorDtor(Akinator* akinator) {
    switch(akinator->game_mode) {
        case quit:
        case quit_without_saving:
            TreeDtor(akinator->tree);
            return SUCCESS;
    }

    return SUCCESS;
}
