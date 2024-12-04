#include <Arduino.h>
#include <simplyprint.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <arduino_secrets.h>
#include <board_mapping.h>


// Timing for LED blink
unsigned long previousMillis = 0;
const long blinkInterval = 500; // Blink every 500ms for Green LED
bool greenState = false;  // Keeps track of the green LED blinking state

// Function to control the LEDs based on printer state
void controlLEDs(String printerState) {
    unsigned long currentMillis = millis();

    if (printerState == "printing") {
        // Printer is printing, turn on the red LED
        digitalWrite(RED_LED_PIN, HIGH);     // Red ON
        digitalWrite(GREEN_LED_PIN, LOW);    // Green OFF
        digitalWrite(YELLOW_LED_PIN, LOW);   // Yellow OFF
    }
    else if (printerState == "paused") {
        // Printer is paused, turn on the yellow LED
        digitalWrite(RED_LED_PIN, LOW);      // Red OFF
        digitalWrite(GREEN_LED_PIN, LOW);    // Green OFF
        digitalWrite(YELLOW_LED_PIN, HIGH);  // Yellow ON
    }
    else if (printerState == "finished") {
        // Printer is done printing but bed is still in use, green LED should blink
        if (currentMillis - previousMillis >= blinkInterval) {
            previousMillis = currentMillis;
            greenState = !greenState;  // Toggle Green LED blink state
            if (greenState) {
                digitalWrite(GREEN_LED_PIN, HIGH);  // Green ON
            } else {
                digitalWrite(GREEN_LED_PIN, LOW);   // Green OFF
            }
        }

        digitalWrite(RED_LED_PIN, LOW);      // Red OFF
        digitalWrite(YELLOW_LED_PIN, LOW);   // Yellow OFF
    }
    else {
        // Printer is available, turn on the green LED
        digitalWrite(RED_LED_PIN, LOW);      // Red OFF
        digitalWrite(GREEN_LED_PIN, HIGH);   // Green ON
        digitalWrite(YELLOW_LED_PIN, LOW);   // Yellow OFF
    }
}
 
String pause_impression(void) {
    HTTPClient http;
    const size_t capacity = 10 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 1024;
    DynamicJsonDocument doc(capacity);

    // Specify the URL for pausing the printer, including the printer ID in the path and pid as a query parameter
    String url = "https://api.simplyprint.io/12305/printers/actions/Pause?pid=21937"; 

    http.begin(url);

    // Add necessary headers
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    // Send POST request
    int httpResponseCode = http.POST("");

    // Check response code
    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Response: " + response);
        return response;  // Return response for debugging
    } else {
        Serial.println("Error: " + String(httpResponseCode));
        return "Error: " + String(httpResponseCode);  // Return error code
    }

    http.end();
}
String resume_impression(void) {
    HTTPClient http;
    const size_t capacity = 10 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 1024;
    DynamicJsonDocument doc(capacity);

    // Specify the URL for resuming the printer, including the printer ID in the path and pid as a query parameter
    String url = "https://api.simplyprint.io/12305/printers/actions/Resume?pid=21937";  

    http.begin(url);

    // Add necessary headers
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    // Send POST request
    int httpResponseCode = http.POST("");

    // Check response code
    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Response: " + response);
        return response;  // Return response for debugging
    } else {
        Serial.println("Error: " + String(httpResponseCode));
        return "Error: " + String(httpResponseCode);  // Return error code
    }

    http.end();
}



String get_printer_state(void) {
    
    HTTPClient http;
    const size_t capacity = 10 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 1024;
    DynamicJsonDocument doc(capacity);
    // Spécification de l'URL
    http.begin("https://api.simplyprint.io/12305/printers/Get");

    // Ajout des headers
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    // Envoyer la requête POST
    int httpResponseCode = http.POST("{}");
    
    // Vérifier la réponse
    if (httpResponseCode > 0)
    {
      String response = http.getString();
      // Serial.println("Réponse du serveur: " + response);

      // Parse de la réponse JSON
      
      deserializeJson(doc, response);
    }    
    
      // Vérifier le statut
      if (doc["status"] == true)
      {
        JsonArray data = doc["data"];
        // Parcourir les objets dans "data"
        for (JsonObject printerObj : data)
        {

          int id = printerObj["id"];
          if (id == 18491)
          {

            const char *printerState = printerObj["printer"]["state"];
            return String(printerState);
            
          }
          else
          {
             Serial.println("Erreur lors de la requête POST: " + String(httpResponseCode));
             return String(id);
          }
        }
      }
      else
      {
        Serial.println("Erreur lors de la requête POST: " + String(httpResponseCode));
      }
     
    
    http.end();
    
}
/*archived->*/
String get_printer_message(void){
    HTTPClient http;
    const size_t capacity = 10 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 1024;
    DynamicJsonDocument doc(capacity);
    // Spécification de l'URL
    http.begin("https://api.simplyprint.io/12305/printers/Get");

    // Ajout des headers
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    // Envoyer la requête POST
    int httpResponseCode = http.POST("{}");
    
    // Vérifier la réponse
    if (httpResponseCode > 0)
    {
      String response = http.getString();
      // Serial.println("Réponse du serveur: " + response);

      // Parse de la réponse JSON
      
      deserializeJson(doc, response);
    }    
    
      // Vérifier le statut
      if (doc["status"] == true)
      {
        JsonArray data = doc["data"];
        // Parcourir les objets dans "data"
        for (JsonObject printerObj : data)
        {

          int id = printerObj["id"];
          if (id == 18491)
          {

            const char *message = printerObj["message"];
            return String(message);
            
          }
          else
          {
             Serial.println("Erreur lors de la requête POST: " + String(httpResponseCode));
             return String(id);
          }
        }
      }
      else
      {
        Serial.println("Erreur lors de la requête POST: " + String(httpResponseCode));
      }
     
    
    http.end();

}
/*archived->*/
bool ToggleSuccess(void){
    if(get_printer_message() == "Failed to get printers"){
        return true;
    }
    else 
    {
        return false;
    }
}

bool is_printer_printing(void) {
    if (get_printer_state() == "printing") {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_printer_paused(void) {
    if (get_printer_state() == "pausing") {
        return true;
    }
    else
    {
        return false;
    }
}

