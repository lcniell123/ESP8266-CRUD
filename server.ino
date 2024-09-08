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

// Define the soil moisture sensor pin (Analog pin A0)
#define SOIL_PIN A0

// Create an instance of the server on port 80
ESP8266WebServer server(80);

// Function to classify soil moisture based on analog value
String classifySoilMoisture(int value) {
  if (value < 200) {
    return "Very Dry";  // Lowest range, very dry soil
  } else if (value >= 200 && value < 400) {
    return "Dry";  // Dry soil
  } else if (value >= 400 && value < 600) {
    return "Moderate";  // Moderate soil moisture
  } else if (value >= 600 && value < 800) {
    return "Wet";  // Wet soil
  } else {
    return "Very Wet";  // Highest range, very wet soil
  }
}

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
    int soilMoisture = analogRead(SOIL_PIN);  // Read soil moisture sensor on analog pin A0

    // Check if any DHT reads failed and exit early
    if (isnan(humidity) || isnan(temperature)) {
      server.send(500, "text/plain", "Failed to read from DHT sensor");
      return;
    }

    // Classify soil moisture level
    String soilMoistureLevel = classifySoilMoisture(soilMoisture);

    // Create a JSON response with temperature, humidity, and soil moisture classification
    String json = "{";
    json += "\"temperature\": " + String(temperature) + ",";
    json += "\"humidity\": " + String(humidity) + ",";
    json += "\"soil_moisture\": \"" + soilMoistureLevel + "\"";
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