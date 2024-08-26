#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "your_SSID";       // Replace with your Wi-Fi SSID
const char* password = "your_PASSWORD"; // Replace with your Wi-Fi password

ESP8266WebServer server(80);  // Create a web server on port 80
const int ledPin = D1;        // LED connected to digital pin D1

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());  // Print the IP address assigned to the ESP8266

  // Define routes for turning the LED on and off
  server.on("/on", []() {
    digitalWrite(ledPin, HIGH);    // Turn LED on
    server.send(200, "text/plain", "LED is ON");
  });

  server.on("/off", []() {
    digitalWrite(ledPin, LOW);    // Turn LED off
    server.send(200, "text/plain", "LED is OFF");
  });

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();  // Handle incoming client requests
}
