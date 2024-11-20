#include <Arduino.h>
#include <display.h>
#include <board_mapping.h>
#include <HardwareSerial.h>

HardwareSerial mySerial(1);  // Utilisation de l'UART1 (l'ESP32 dispose de plusieurs UARTs)


int initialize_screen(void){
 
  // Initialiser la connexion série vers l'écran LCD (9600 baud est courant pour les écrans UART)
  
  
  delay(50);  // Petit délai pour permettre à l'écran LCD de s'initialiser
  mySerial.begin(9600, SERIAL_8N1, GPIO_UART_TX, GPIO_UART_RX);  // TX : GPIO 16, RX : GPIO 17
  // Effacer l'écran LCD
  mySerial.write(0xFE);       // Indicateur de commande
  mySerial.write(0x01);       // Commande pour effacer l'écran
  delay(10);                  // Délai pour permettre l'effacement
}

int afficher_message_accueil(void) {
    
    // Afficher le texte en français sur la première ligne
    delay(1000);
    mySerial.begin(9600, SERIAL_8N1, GPIO_UART_TX, GPIO_UART_RX);  // TX : GPIO 16, RX : GPIO 17
    // Positionner le curseur au début de la deuxième ligne
    mySerial.write(0xFE);       // Indicateur de commande pour la position du curseur
    mySerial.write(0xC0);       // Déplacer le curseur au début de la deuxième ligne

    // Afficher un texte additionnel sur la deuxième ligne
    mySerial.write("Test ESP32 LCD"); // Afficher le texte sur l'écran LCD
    mySerial.write("Bonjour Jojo!"); // Afficher le texte sur l'écran LCD
    return 0;
}
