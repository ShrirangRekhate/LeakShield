# ⚡LeakShield-Voltage-Monitoring-and-Safety-System

An IoT-based voltage protection system that automatically cuts off power when dangerous voltage levels are detected, with real-time monitoring through a web dashboard.

---

## 📷 Demo Preview

> ✅ Live voltage monitoring via WebSocket  
> 🔌 Automatic relay cutoff at 15V threshold  
> 📱 Mobile & 💻 desktop friendly interface  

---

## 🛠️ Features

- **Real-time Voltage Tracking** - Continuous AC voltage measurement with ZMPT101B sensor
- **Overvoltage Protection** - Instant relay cutoff when voltage exceeds safe limits
- **Web Dashboard** - Beautiful real-time visualization of voltage data
- **Remote Control** - Enable/disable protection system from anywhere
- **Safety First** - Designed with fail-safe mechanisms for reliable operation

---

## 🧩 Hardware Components

| Component | Quantity |
|-----------|----------|
| ESP32 | 1 |
| ZMPT101B Voltage Sensor | 1 |
| 5V Relay Module | 1 |
| Jumper Wires | As needed |
| Breadboard | 1 (optional) |

---

## 🚀 Quick Start

1. **Wire the components**:
ZMPT101B → ESP32
VCC → 3.3V
GND → GND
OUT → A7

Relay → ESP32
VCC → 5V
GND → GND
IN → GPIO2


2. **Upload the code**:
```bash
git clone https://github.com/ShrirangRekhate/VoltGuard.git
```
## ⚙️ Configuration
# Customize in code:
#define SENSITIVITY 500.0f    // Sensor calibration
#define VOLTAGE_THRESHOLD 15  // Cutoff voltage (in volts)
const char* ssid = "YourWiFi"; // WiFi credentials
const char* password = "YourPassword";

## 🛡️ Safety Notice
# ⚠️ Warning: This project involves mains voltage.

Always disconnect power before working on the circuit

Double-check all connections

Use proper insulation

Never touch exposed wires when powered

##📜 License
MIT License © 2023 

## Author
#Shrirang Rekhate

