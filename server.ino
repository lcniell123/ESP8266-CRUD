

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTPIN D7       // DHT11 connected to D7 (GPIO13)
#define DHTTYPE DHT11   // Sensor type is DHT11


const char* ssid = "...";       // Replace with your Wi-Fi SSID
const char* password = "..."; 

// const char* ssid = "yourSSID";        // Your Wi-Fi Name
// const char* password = "yourPASSWORD"; // Your Wi-Fi Password

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80); // Start Web Server on Port 80

// Function to send sensor data
void handleSensorData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    server.send(500, "text/plain", "Failed to read sensor data");
    return;
  }

  String json = "{";
  json += "\"temperature\":" + String(temperature) + ",";
  json += "\"humidity\":" + String(humidity);
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connected.");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());

  // Define the API route
  server.on("/data", handleSensorData);
  server.begin();
}

void loop() {
  server.handleClient();
}


