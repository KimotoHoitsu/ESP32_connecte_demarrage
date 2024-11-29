// Hassan
// Charles-Olivier
#include <Arduino.h>

#include <board_mapping.h>
#include <init.h>

#include <WiFi.h>
#include "esp_wpa2.h"        // pour les réseaux wifi sécurisés
#include "arduino_secrets.h" // fichier contenant les informations de connexion

#include <display.h>
#include <simplyprint.h>



void setup() {
  
  initialisationSerie();
  initialize_screen();
  initialisationWifi();

}

void loop() {

    
    Serial.printf("allo");
    
    CurseurPosition(0x01);     // Indicateur de commande pour la position du curseur
    afficher_message_accueil();
   // Déplacer le curseur au début de la deuxième ligne
    //afficher_message_accueil();
  while(1){

    delay(200);
  }
}
