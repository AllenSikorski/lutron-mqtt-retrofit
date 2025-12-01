# 🔧 ESP32 Firmware: MQTT-Controlled Lutron Relay

This firmware powers the ESP32 used in the [277V Lutron Retrofitting Project](../README.md), allowing it to receive MQTT messages and simulate button presses on a Lutron lighting module via optocouplers.

It listens for MQTT topics like `hq/lobby_lights/on` and `hq/lobby_lights/off` and briefly sets the appropriate GPIO pin HIGH to simulate a momentary press (200ms).

---

## 📋 Features

- Static IP configuration
- MQTT authentication support
- Momentary button press simulation (200ms)
- Reconnect loop for Wi-Fi and MQTT stability
- Fully compatible with Home Assistant and Node-RED

---

## ⚙️ Pinout

| Action         | GPIO Pin |
|----------------|----------|
| Turn ON Light  | `GPIO 5` |
| Turn OFF Light | `GPIO 18` |

---

## 📡 MQTT Topics

| Topic                  | Behavior                |
|------------------------|-------------------------|
| `hq/lobby_lights/on`   | Simulates ON press      |
| `hq/lobby_lights/off`  | Simulates OFF press     |

---

## 🧠 How It Works

- The ESP32 connects to Wi-Fi and establishes a static IP.
- It then connects to the MQTT broker using your credentials.
- On receiving a message for ON/OFF, it pulses the corresponding GPIO pin HIGH for 200ms.
- This triggers the optocoupler module, simulating a real button press on the Lutron board.

---

## 🪛 Setup Instructions

1. 🔌 **Wiring**: Ensure your ESP32 is connected to the optocoupler modules and the Lutron board. Refer to the [Wiring Diagram](../hardware/wiring_diagram.png).
2. 🖥 **Install Libraries** in Arduino IDE:
   - `WiFi.h` (included by default)
   - `PubSubClient` by Nick O'Leary
3. 🧠 **Flash the Code**:
   - Edit the `ssid`, `password`, `mqtt_server`, `mqtt_user`, and `mqtt_password` at the top of the file.
   - Upload to your ESP32 using Arduino IDE or PlatformIO.
4. ✅ Upon boot, the ESP32 should:
   - Connect to Wi-Fi
   - Connect to MQTT
   - Subscribe to the ON/OFF topics

---

## 📁 File Included

- [`esp32_lutron_mqtt.ino`](esp32_lutron_mqtt.ino) — main firmware source file

---


