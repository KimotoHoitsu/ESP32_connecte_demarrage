// Hassan
// Charles-Olivier
// Printer ID: 18491
#include <Arduino.h>

#include <board_mapping.h>
#include <init.h>

#include <WiFi.h>
#include "esp_wpa2.h"        // pour les réseaux wifi sécurisés
#include "arduino_secrets.h" // fichier contenant les informations de connexion

#include <display.h>
#include <simplyprint.h>


void setup() {
  
  // Initialize the LEDs as outputs
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistor

  initialisationSerie();
  initialize_screen();
  initialisationWifi();

}

void loop() {
  String test = get_printer_state();
  Serial.println(test);

  
  static bool lastButtonState = HIGH; // Last state of the button
  static bool printerPaused = false; // State of the printer (paused or not)
  
  bool buttonState = digitalRead(BUTTON_PIN); // Read the current state of the button
  
  // Check if the button has been pressed (assuming the button is LOW when pressed)
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Debounce delay
    delay(50);
    
    // Toggle the printer's state
    if (printerPaused) {
      // Resume the printer
      Serial.println("Resuming printer...");
      resume_impression();
      printerPaused = false;
    } else {
      // Pause the printer
      Serial.println("Pausing printer...");
      pause_impression();
      printerPaused = true;
    }
  }
  
  // Update the last button state
  lastButtonState = buttonState;
  
  
  delay(100); // Small delay to avoid reading the button too frequently
  }

