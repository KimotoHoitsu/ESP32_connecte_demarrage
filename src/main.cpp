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
  String test = get_printer_state();
  Serial.println(test);
  pause_impression();
  Serial.println(test);
  //afficher_message_accueil();
  while(1){
    delay(200);
  }
}
