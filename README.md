# garden-project

Get Garden Sensor data

# ESP8266 Temperature & Humidity Monitor

## About

This project uses an **ESP8266** with a **DHT11 sensor** to measure **temperature and humidity** and serves the data over Wi-Fi. A **Node.js server** fetches and displays the sensor readings.

## Features

- ESP8266 hosts a web server to provide real-time sensor data.
- Node.js server fetches data and serves it at `http://localhost:3000/data`.
- Optional frontend displays live temperature and humidity updates.

## Current Status Feb25

![Circuit Diagram](https://github.com/lcniell123/garden-project/img/4-connect-battery/ardbat1.jpg)

✅ ESP8266 successfully serves **temperature & humidity** data.  
✅ Node.js server fetches data correctly.  
✅ Data updates every **5 seconds** in the frontend.
✅ Connect ESP to battery.

## Architecture Overview

### ** How It Works**

1- **DHT11 Sensor** is connected to the **ESP8266**, which reads temperature & humidity.  
2- **ESP8266 hosts a web server** and provides sensor data at `http://ESP_IP/data`.  
3️- **Node.js server** (running on a PC) fetches the data from ESP8266.  
4️- The **frontend** (a simple web page) requests data from Node.js every **5 seconds** and displays it.
5- Connects ESP8266 to **ESP battery handler**

## Features

- **ESP8266 as a Web Server** → Hosts sensor data at `/data`.
- **Node.js Server** → Fetches ESP8266 data and serves it at `http://localhost:3000/data`.
- **Frontend (Web Page)** → Displays real-time temperature & humidity updates.

## Current Status

✅ ESP8266 successfully serves **temperature & humidity** data.  
✅ Node.js server fetches data correctly.  
✅ Data updates every **5 seconds** in the frontend.

## Hardware Components

### **1. ESP8266 (Microcontroller)**

- Acts as the **main processor** and **web server**.
- Connects to Wi-Fi to serve sensor data.
- Receives **temperature & humidity** readings from the DHT11 sensor.

### **2. DHT11 (Temperature & Humidity Sensor)**

- Measures **temperature** (in Celsius) and **humidity** (as a percentage).
- Sends data to the ESP8266 through a single digital pin.

### **3. Power Supply**

- The ESP8266 is powered via **a 3.7V 18650 battery** connected through a **battery shield**.
- The battery shield provides a **3V output**, which is connected to the **ESP8266's 3V3 pin**.

### **4. Battery Shield (DIYMORE Li-ion V3)**

- Holds the **18650 Li-ion battery**.
- Provides regulated **3V output** to power the ESP8266.
- Features a **charging circuit** to recharge the battery via USB.

## Wiring Connections

| **Component**          | **ESP8266 Pin** |
| ---------------------- | --------------- |
| **DHT11 VCC**          | 3V3             |
| **DHT11 GND**          | GND             |
| **DHT11 Data**         | D7 (GPIO13)     |
| **Battery Shield 3V**  | 3V3             |
| **Battery Shield GND** | GND             |

## Architecture Overview

1. **DHT11 sensor** measures temperature and humidity.
2. **ESP8266 reads data** and serves it at `/data`.
3. **A computer running Node.js** fetches the data.
4. **A web page** displays the sensor data in real time.
