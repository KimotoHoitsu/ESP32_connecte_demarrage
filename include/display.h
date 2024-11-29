#ifndef display_h
#define display_h

#include <display.h>

void afficher_message_accueil(void);
void initialize_screen(void);
void EffaceLigne4(void);
void SetBacklight(int brightness);
void EffaceLigne3(void);
void SetContrast(int contrast);
void Ecran_Allume(void);
void EffaceLigne2(void);
void EffaceLigne1(void);
void MoveCursor(int cursor);
/**
   @Param
    aucun
   @Returns
    aucun
   @Description
    Envoi la commande pour allumer l'�cran
   @Example
    Ecran_Allume();
 */
void Ecran_Eteint(void);
/**
   @Param
    aucun
   @Returns
    aucun
   @Description
    Envoi la commande pour eteindre l'�cran
   @Example
    Ecran_Eteint();
 */

void CurseurPosition(int position);
/**
   @Param
    position
    
   @Description
    Envoi la commande pour determiner la position du cursor
   @Example
    CurseurPosition(0x45);
 */
void VideEcran(void);
/**
   @Param
    aucun
   @Returns
    aucun
   @Description
    Envoi la commande pour vider l'ecran
   @Example
    VideEcran();
 */
 
void EcrireCaractere(const char* caractere);
/**
   @Param
    caractere 
   @Returns
    aucun
   @Description
    Envoi la commande pour ecrire un charactere
   @Example
    EcrireCaractere('x');
 */
void MoveCaracter_Right(void);
/**
   @Param
    aucun
   @Returns
    aucun
   @Description
    Envoi la commande pour deplacer le curseur de 1 espace vers la droite
   @Example
    MoveCaracter_Right();  
 
 
 */
void DeleteChar(void);
/**
   @Param
    aucun
   @Returns
    aucun
   @Description
    Envoi la commande pour supprimer un caractere
   @Example
    DeleteChar();
 */

#endif