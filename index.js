const express = require("express");
const axios = require("axios");
const app = express();

// ✅ Replace with your ESP8266's IP address
const ESP8266_IP = "http://10.0.0.203"; // Change this to your ESP8266 IP

app.use(express.static("public"));

app.get("/data", async (req, res) => {
  try {
    const response = await axios.get(`${ESP8266_IP}/data`);
    console.log("Sensor data:", response.data);
    res.json(response.data);
  } catch (error) {
    console.error("Error fetching sensor data:", error.message);
    res.status(500).send("Failed to fetch sensor data.");
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
