# ⚡ LeakShield: Current Leakage Detection and Monitoring System

An IoT-based safety system that automatically disconnects power in case of short circuit, with real-time web monitoring and manual override capability.

---

## 🛡️ Safety-Critical Operation

> 🔌 **Relay Behavior**:  
> - Normally CLOSED circuit (allows current flow)  
> - Opens circuit (STOPS current) when:  
>   - Voltage > 15V threshold  
>   - System is manually disabled  
> - Uses GPIO33 for relay control  

---

## 🛠️ Key Features

- **Real-time Voltage Monitoring** - ZMPT101B sensor on pin 32
- **Safety Cutoff** - Relay on GPIO33 opens circuit at 15V
- **Web Dashboard** - Live data visualization
- **Dual Control** - Automatic protection + manual override
- **Fail-Safe Design** - Defaults to safe state (circuit open)

---

## 🔌 Hardware Configuration

| Component | ESP32 Connection |
|-----------|------------------|
| ZMPT101B VCC | 3.3V |
| ZMPT101B GND | GND |
| ZMPT101B OUT | GPIO32 |
| Relay VCC | 5V |
| Relay GND | GND |
| Relay IN | GPIO33 |

```cpp
// Critical Configuration (in code)
#define RELAY_PIN 33       // Safety cutoff control
#define VOLTAGE_SENSOR 32  // Analog input
#define VOLTAGE_THRESHOLD 15.0  // Cutoff threshold
```
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
git clone https://github.com/ShrirangRekhate/LeakShield-Voltage-Monitoring-and-Safety-System.git
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

# 📜 License
MIT License © 2023 

# Author
## Shrirang Rekhate

