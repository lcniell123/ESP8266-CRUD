const express = require("express");
const axios = require("axios");
const app = express();

// Replace with the IP address of your ESP8266
const ESP8266_IP = "10.0.0.210";

app.use(express.static("public"));

// Route to turn LED on
app.get("/led/on", async (req, res) => {
  try {
    const response = await axios.get(`${ESP8266_IP}/on`);
    console.log("ESP8266 response:", response.data);
    res.send("LED turned on!");
  } catch (error) {
    console.error("Error turning on LED:", error.message);
    res.status(500).send("Failed to turn on LED.");
  }
});

// Route to turn LED off
app.get("/led/off", async (req, res) => {
  try {
    const response = await axios.get(`${ESP8266_IP}/off`);
    res.send("LED turned off!");
  } catch (error) {
    res.status(500).send("Failed to turn off LED.");
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
