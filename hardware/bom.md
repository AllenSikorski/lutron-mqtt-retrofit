# 🧾 Bill of Materials (BOM)

This project retrofits a commercial 277V Lutron lighting system to be MQTT-controllable using an ESP32, optocouplers, and custom Node-RED logic.

## 🔌 Core Hardware Components

| Component | Description | Notes |
|----------|-------------|-------|------|
| **ESP32 DevKitC (38-pin)** | Wi-Fi microcontroller | Powers the Lutron relay directly using 3.3V 
| **Icstation EL817 Optocoupler Module** | 1-channel 12V optocoupler | 2 required: one for ON, one for OFF
| **Lutron RMJ-16R-DV-B** | 277V relay module with SoftSwitch | Existing proprietary commercial lighting relay
| **Custom Wires** | Female-to-female jumpers | For connecting optocouplers to ESP32 GPIO |

---

## ⚡ Power & Wiring

| Component | Description | Notes |
|----------|-------------|-------|------|
| **CR123A Battery Socket** (optional) | Replaced by direct ESP32 power
| **3.3V Output** | From ESP32 3.3V pin | Powers the Lutron relay logic board |
| **GND** | Shared GND from ESP32 | Tied to Lutron board GND and optocoupler module GND |

---

## 📶 Networking & Integration

| Component | Description | Notes | Link |
|----------|-------------|-------|------|
| **Wi-Fi Network** | ESP32 connects to LAN | Used for MQTT communication | — |
| **Mosquitto MQTT Broker** | Self-hosted at `192.168.0.2` | Requires username & password auth |  [Home Assistant Mosquitto Addon]([https://www.home-assistant.io/](https://www.home-assistant.io/integrations/mqtt/))  |
| **Home Assistant** (optional) | Receives MQTT state | Optional integration layer | [Home Assistant](https://www.home-assistant.io/) |
| **Node-RED** | Automation logic | Controls ON/OFF events, schedules, time blocks |  [Home Assistant Mosquitto Addon]([https://www.home-assistant.io/](https://github.com/hassio-addons/addon-node-red))  |

---

## 🧠 Software/Dependencies

| Tool | Description | Notes | Link |
|------|-------------|-------|------|
| **Arduino IDE** | For uploading ESP32 firmware | Required to flash `.ino` file | [Arduino](https://www.arduino.cc/en/software) |
| **ESP32 Arduino Board Support** | Needed for compiling ESP32 sketch | Install via Arduino board manager | [Espressif GitHub](https://github.com/espressif/arduino-esp32) |
| **PubSubClient** | MQTT library used in firmware | Install via Arduino Library Manager | [PubSubClient](https://github.com/knolleary/pubsubclient) |

---

## 🖼️ Diagrams & Visuals

- 📌 `hardware/wiring_diagram.png` — Wiring of optocoupler to ESP32 and relay contacts
- 📌 `automation/schedules.md` — (coming soon) Node-RED logic and behavior description

---

## 📌 GPIO Configuration (as used in firmware)

| GPIO | Purpose |
|------|---------|
| GPIO 5  | Triggers “ON” optocoupler |
| GPIO 18 | Triggers “OFF” optocoupler |

> ⚠️ Make sure to adjust `#define` values in the firmware if your wiring differs.

---

## ✅ Recap of System Behavior

- When the MQTT topic `hq/lobby_lights/on` receives a payload, the ESP32 pulses GPIO 5 → triggers ON via optocoupler.
- When the MQTT topic `hq/lobby_lights/off` receives a payload, ESP32 pulses GPIO 18 → triggers OFF.
- Node-RED manages logic: time blocks, auto-off rules, and dashboard UI.
- Entire system runs without Lutron’s proprietary sensors or Cloud.

---

