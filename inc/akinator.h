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
    zaebal        = 2
};

struct Akinator {
    Tree<char*>* tree;
    char*        input_data_base;
    char*        output_data_base;
    GameMode     game_mode;
};

TYPE_OF_ERROR AkinatorInit          (Akinator* akinator, int argc, char** argv);
TYPE_OF_ERROR GuessMode             (Akinator* akinator);
TYPE_OF_ERROR PlayAkinator          (Akinator* akinator, TreeNode<char*>* node);
UserAnswer    GetAnswer             ();
TYPE_OF_ERROR AddCharacter          (Akinator* akinator, TreeNode<char*>* node);
TYPE_OF_ERROR QuitWithoutSaving     (Akinator* akinator);
TYPE_OF_ERROR ConnectCharacterToTree(Akinator* akinator, TreeNode<char*>* node,
                                     char* attribute, char* character);
inline void   CleanBuffer           ();
TYPE_OF_ERROR GetDescription        (Akinator* akinator);
TYPE_OF_ERROR LinkRootCharacter     (Akinator* akinator, TreeNode<char*>* node,
                                     char* attribute, char* character);
TYPE_OF_ERROR LinkCharacter         (Akinator* akinator, TreeNode<char*>* node,
                                     char* attribute, char* character);
TYPE_OF_ERROR FindCharacter         (TreeNode<char*>* node, TreeNode<char*>* character_node,
                                     TreeNode<char*>** original_node);
TYPE_OF_ERROR GetWayToNode          (stack* way_to_node, TreeNode<char*>* node);
TYPE_OF_ERROR StartGame             (Akinator* akinator);
TYPE_OF_ERROR AkinatorDtor          (Akinator* akinator);

#define _ScanAnswer(value)   \
    CleanBuffer();           \
    scanf("%100[^\n]", value)\

#define _WhaitForValidAnswer(function, node, variable, correct_return, message)\
    while(function != correct_return) {                                        \
        printf(message, variable);                                             \
        _ScanAnswer(variable);                                                 \
        node->value = variable;                                                \
        node->hash  = Hash(variable);                                          \
    }                                                                          \
    printf("")

#define FindCharacterNode()\
    while()
#endif
