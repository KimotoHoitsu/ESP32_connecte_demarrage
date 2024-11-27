#include <Arduino.h>
#include <simplyprint.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <arduino_secrets.h>

int pause_impression(void) {
    HTTPClient http;

    // Spécification de l'URL
    http.begin("https://api.simplyprint.io/12305/printers/actions/Pause");

    // Ajout des headers
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    // Envoyer la requête POST
    int httpResponseCode = http.POST("{\"pid\": " + String(PRINTER_ID) + "}");

    return 0;
}

int resume_impression(void) {
    HTTPClient http;

    // Spécification de l'URL
    http.begin("https://api.simplyprint.io/12305/printers/actions/Resume");

    // Ajout des headers
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    // Envoyer la requête POST
    int httpResponseCode = http.POST("{\"pid\": " + String(PRINTER_ID) + "}");

    return 0;
}

int toogle_pause_resume_impression(void) {
    if (is_printer_paused()){
        resume_impression();
    }
    else { 
        pause_impression();
    }
}

String get_printer_state(void) {
    HTTPClient http;

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
      const size_t capacity = 10 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 1024;
      DynamicJsonDocument doc(capacity);
      deserializeJson(doc, response);

      // Vérifier le statut
      if (doc["status"] == true)
      {
        JsonArray data = doc["data"];
        
        // Parcourir les objets dans "data"
        for (JsonObject printerObj : data)
        {

          int id = printerObj["id"];
          if (id == PRINTER_ID)
          {

            const char *printerState = printerObj["printer"]["state"];

            return printerState;
          }
        }
      }
      else
      {
        Serial.println("Erreur lors de la requête POST: " + String(httpResponseCode));
      }

      // Terminer la connexion
  
      http.end();
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
    if (get_printer_state() == "paused") {
        return true;
    }
    else
    {
        return false;
    }
}