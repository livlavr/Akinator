#ifndef AKINATOR_H_
#define AKINATOR_H_

#include "stack_public.h"

static const int  MAX_TRIES_NUMBER  = 15;
static const int  MAX_VALUE_SIZE    = 100;
static const char NO                = -67;
static const char YES               = -76;

enum GameMode {
    play_akinator = 1,
    description   = 2,
    compare       = 3,
    save          = 4,
    install       = 5,
    watch_tree    = 6,
    quit_and_save = 7,
    quit          = 8
};

enum UserAnswer {
    yes           = 0,
    no            = 1,
    zaebal        = 2,
    sosal         = 3
};

struct Akinator {
    Tree<char*>* tree;
    char*        input_data_base;
    char*        output_data_base;
    GameMode     game_mode;
};

TYPE_OF_ERROR AkinatorInit      (Akinator* akinator, int argc, char** argv              );
TYPE_OF_ERROR GuessMode         (Akinator* akinator                                     );
TYPE_OF_ERROR PlayAkinator      (Akinator* akinator, TreeNode<char*>* node              );
UserAnswer    GetAnswer         (TreeNode<char*>* node                                  );
UserAnswer    Sosal             (char*            answer                                );
void          PrintHui          ();
TYPE_OF_ERROR AddCharacter      (Akinator* akinator, TreeNode<char*>* node              );
void          CleanBuffer       ();
TYPE_OF_ERROR GetDescription    (Akinator* akinator                                     );
TYPE_OF_ERROR LinkRootCharacter (Akinator* akinator, TreeNode<char*>* node,
                                 char* attribute, char* character                       );
TYPE_OF_ERROR LinkCharacter     (Akinator* akinator, TreeNode<char*>* node,
                                 char* attribute, char* character                       );
TYPE_OF_ERROR FindNode          (TreeNode<char*>* node, TreeNode<char*>* character_node,
                                 TreeNode<char*>** original_node                        );
TYPE_OF_ERROR FindValueInTree   (TreeNode<char*>* node, char* value, uint32_t hash      );
TYPE_OF_ERROR GetWayToNode      (stack* way_to_node, TreeNode<char*>* node              );
TreeNode<char*>* FindCharacter  (Akinator* akinator, stack* way_to_node                 );
TYPE_OF_ERROR CompareCharacters (Akinator* akinator                                     );
TYPE_OF_ERROR PrintComparing    (TreeNode<char*>* node, stack* way1,
                                 stack* way2, char* value1, char* value2                );
TYPE_OF_ERROR PrintDescription  (stack* way_to_node, TreeNode<char*>* node              );
TYPE_OF_ERROR StartGame         (Akinator* akinator                                     );
TYPE_OF_ERROR AkinatorDtor      (Akinator* akinator                                     );

#define _ScanAnswer(value)                                                     \
    CleanBuffer();                                                             \
    scanf("%100[^\n]", value)                                                  \

#define _WhaitForValidAnswer(function, variable, correct_return, message)      \
    while(function != correct_return) {                                        \
        color_printf(RED_COLOR, BOLD, message, variable);                      \
        _ScanAnswer(variable);                                                 \
    }                                                                          \
    printf("")

#define _WaitForAnswer()\
    printf("Введи что-нибудь, чтобы выйти в меню ");                            \
    char shit_word[MAX_VALUE_SIZE] = "";                                        \
    scanf("%100s", &shit_word) //говно

#define _Sosal()\
    int r = rand() % 5;\
    if(r == 0) {\
        printf("\x1b[F                                                               \n");\
        if(!(node->left || node->right)) {\
            printf("\x1b[FТы загадал %s? [д/н]\n", node->value);\
        }\
        else {\
            printf("\x1b[F%s? [д/н]\n", node->value);\
        }\
        printf("Сосал? ");\
        printf("%s\n", answer);\
        return sosal;\
    }\
    return yes\

#endif
