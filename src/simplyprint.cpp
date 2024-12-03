#include <Arduino.h>
#include <simplyprint.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <arduino_secrets.h>
#include <board_mapping.h>


String pause_impression(void) {
    HTTPClient http;
    const size_t capacity = 10 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 1024;
    DynamicJsonDocument doc(capacity);

    // Specify the URL for pausing the printer, including the printer ID in the path and pid as a query parameter
    String url = "https://api.simplyprint.io/12305/printers/actions/Pause?pid=18491"; 

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
    String url = "https://api.simplyprint.io/12305/printers/actions/Resume?pid=18491";  

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
    if (get_printer_state() == "paused") {
        return true;
    }
    else
    {
        return false;
    }
}

