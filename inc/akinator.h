#ifndef AKINATOR_H_
#define AKINATOR_H_

static const int  MAX_TRIES_NUMBER  = 15;
static const int  MAX_VALUE_SIZE    = 100;
static const char PLAY              = -80;
static const char QUIT              = -127;
static const char QUIT_WITHOUT_SAVE = -78;
static const char NO                = -67;
static const char YES               = -76;

enum GameMode {
    guess_mode          = 0,
    quit_without_saving = 1 << 0,
    quit                = 1 << 1,
    play_again          = 1 << 2
};

enum UserAnswer {
    yes    = 0,
    no     = 1,
    zaebal = 2
};

struct Akinator {
    Tree<char*>* tree;
    char*        input_data_base;
    char*        output_data_base;
    GameMode     game_mode;
};

TYPE_OF_ERROR AkinatorInit(Akinator* akinator, int argc, char** argv);
TYPE_OF_ERROR GuessMode   (Akinator* akinator);
TYPE_OF_ERROR PlayAkinator(Akinator* akinator, TreeNode<char*>* node);
UserAnswer    GetAnswer   ();
TYPE_OF_ERROR AddCharacter(Akinator* akinator, TreeNode<char*>* node);
TYPE_OF_ERROR QuitWithoutSaving(Akinator* akinator);
TYPE_OF_ERROR ConnectCharacterToTree(Akinator* akinator, TreeNode<char*>* node,
                                     char* attribute, char* character);
inline void   CleanBuffer();
TYPE_OF_ERROR LinkRootCharacter(Akinator* akinator, TreeNode<char*>* node,
                                char* attribute, char* character);
TYPE_OF_ERROR LinkCharacter(Akinator* akinator, TreeNode<char*>* node,
                                char* attribute, char* character);
TYPE_OF_ERROR StartGame(Akinator* akinator);
TYPE_OF_ERROR AkinatorDtor(Akinator* akinator);

#define _ScanAnswer(value) \
    CleanBuffer();           \
    scanf("%100[^\n]", value)\

#define _WhaitForValidAnswer(function, node, variable, correct_return, message)\
    while(function != correct_return) {\
        printf(message, variable);\
        _ScanAnswer(variable);\
        node->value = variable;\
        node->hash  = Hash(variable);\
    }\
    printf("")
#endif
