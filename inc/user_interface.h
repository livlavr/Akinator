#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

TYPE_OF_ERROR MainMenu      (Akinator* akinator);
void          PrintMenu     ();
void          PrintLogo     ();
void          Loading       ();
void          PrintOptions  ();
TYPE_OF_ERROR ChooseGameMode(Akinator* akinator);
TYPE_OF_ERROR StartGame(Akinator* akinator);

#endif
