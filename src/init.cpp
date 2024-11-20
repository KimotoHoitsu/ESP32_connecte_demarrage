#include <Arduino.h>
#include <init.h>

// Fonction d'initialisation des GPIO
int initialisationBroches(void)
{
    // Configuration des broches
    // pinMode(GPIO_B1, INPUT); // Exemple
  

  return 0;
}

// Fonction d'initialisation de l'UART
int initialisationSerie(void)
{
  Serial.setPins(GPIO_UART_TX, GPIO_UART_RX);
  Serial.begin(115200);
  printf("\r\n\r\nPort serie 115200\r\n");
  return 0;
}