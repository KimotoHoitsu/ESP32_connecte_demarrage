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
  //HardwareSerial mySerial(2);  // Utilisation de l'UART1 (l'ESP32 dispose de plusieurs UARTs)
  initialisationSerie();
 // delay(50);  // Petit délai pour permettre à l'écran LCD de s'initialiser
 //mySerial.begin(9600, SERIAL_8N1, GPIO_UART_RX, GPIO_UART_TX);  // RX : GPIO 16, TX : GPIO 17
 // Effacer l'écran LCD
  initialize_screen();
 // delay(10);                  // Délai pour permettre l'effacement
  initialisationWifi();
  Serial.printf("ayay");

}

void loop() {

    
    Serial.printf("allo");
    //mySerial.begin(9600, SERIAL_8N1, GPIO_UART_RX, GPIO_UART_TX);  // RX : GPIO 16, TX : GPIO 17
    // Positionner le curseur au début de la deuxième ligne
    VideEcran();
    CurseurPosition(0x00);     // Indicateur de commande pour la position du curseur
    afficher_message_accueil();
           // Déplacer le curseur au début de la deuxième ligne
    //afficher_message_accueil();


    delay(200);
    
}
