#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "<login>";
const char* password = "<pw>";

// Define the DHT11 sensor and the pin it's connected to
#define DHTPIN D7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Create an instance of the server on port 80
ESP8266WebServer server(80);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // Start the DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Define the route for serving sensor data
  server.on("/data", []() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    
    // Check if any reads failed and exit early
    if (isnan(humidity) || isnan(temperature)) {
      server.send(500, "text/plain", "Failed to read from DHT sensor");
      return;
    }

    // Create a JSON response with temperature and humidity data
    String json = "{";
    json += "\"temperature\": " + String(temperature) + ",";
    json += "\"humidity\": " + String(humidity);
    json += "}";

    server.send(200, "application/json", json);
  });

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}
