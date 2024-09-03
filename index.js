const express = require("express");
const axios = require("axios");
const app = express();

// Replace with the IP address of your ESP8266
const ESP8266_IP = "<ip-address>";

app.use(express.static("public"));

// Route to get sensor data
app.get("/sensor/data", async (req, res) => {
  try {
    const response = await axios.get(`${ESP8266_IP}/data`);
    console.log("Sensor data:", response.data);
    res.json(response.data); // Send the sensor data as JSON to the client
  } catch (error) {
    console.error("Error fetching sensor data:", error.message);
    res.status(500).send("Failed to fetch sensor data.");
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
