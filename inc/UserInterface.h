#ifndef UserInterface_H_
#define UserInterface_H_

TYPE_OF_ERROR MainMenu      (Akinator* akinator);
void          PrintMenu     ();
void          PrintLogo     ();
void          Loading       ();
void          PrintOptions  ();
TYPE_OF_ERROR ChooseGameMode(Akinator* akinator);

#endif
