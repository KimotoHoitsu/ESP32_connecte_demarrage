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

HardwareSerial yourSerial(1);  // Utilisation de l'UART1 (l'ESP32 dispose de plusieurs UARTs)

void setup() {
  initialisationSerie();
 // delay(50);  // Petit délai pour permettre à l'écran LCD de s'initialiser
  yourSerial.begin(9600, SERIAL_8N1, GPIO_UART_TX, GPIO_UART_RX);  // TX : GPIO 16, RX : GPIO 17
  // Effacer l'écran LCD
  yourSerial.write(0xFE);       // Indicateur de commande
  yourSerial.write(0x01);       // Commande pour effacer l'écran
 // delay(10);                  // Délai pour permettre l'effacement
  initialisationWifi();

}

void loop() {

    
    printf("allo");
    yourSerial.begin(9600, SERIAL_8N1, GPIO_UART_TX, GPIO_UART_RX);  // TX : GPIO 16, RX : GPIO 17
    // Positionner le curseur au début de la deuxième ligne
    yourSerial.write(0xFE);       // Indicateur de commande pour la position du curseur
    yourSerial.write(0xC0);       // Déplacer le curseur au début de la deuxième ligne

    // Afficher un texte additionnel sur la deuxième ligne
    yourSerial.write("Test ESP32 LCD"); // Afficher le texte sur l'écran LCD
    yourSerial.write("Bonjour Jojo!"); // Afficher le texte sur l'écran LCD
    
}
