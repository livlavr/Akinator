#ifndef UserInterface_H_
#define UserInterface_H_

TYPE_OF_ERROR MainMenu      (Akinator* akinator);
void          PrintMenu     ();
void          PrintLogo     ();
void          Loading       ();
void          PrintOptions  ();
TYPE_OF_ERROR ChooseGameMode(Akinator* akinator);

#define _ModeAcitivation(mode)             \
    case mode:                             \
                akinator->game_mode = mode;\
                return SUCCESS             \

#define _ModeSelection()   \
    switch(akinator->game_mode) {\
        _ModeAcitivation(play_akinator);\
        _ModeAcitivation(description);\
        _ModeAcitivation(compare);\
        _ModeAcitivation(save);\
        _ModeAcitivation(install);\
        _ModeAcitivation(watch_tree);\
        _ModeAcitivation(quit_and_save); \
        _ModeAcitivation(quit);\
        default:\
            printf("Не совсем понял тебя, так что делать то будем?\n");\
            PrintOptions();\
    }\
    printf("")
#endif
