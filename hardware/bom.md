# 🧾 Bill of Materials (BOM)

This project retrofits a commercial 277V Lutron lighting system to be MQTT-controllable using an ESP32, optocouplers, and custom Node-RED logic.

---

## 🔌 Core Hardware Components

| Component                         | Description                     | Notes |
|----------------------------------|---------------------------------|-------|
| **ESP32 DevKitC (38-pin)**       | Wi-Fi microcontroller           | Powers the Lutron relay directly using 3.3V |
| **Icstation EL817 Optocoupler**  | 1-channel 12V optocoupler       | 2 required: one for ON, one for OFF |
| **Lutron RMJ-16R-DV-B**          | 277V relay module (SoftSwitch)  | Existing proprietary commercial lighting relay |
| **Custom Wires**                 | Female-to-female jumpers        | For connecting optocouplers to ESP32 GPIO |

---

## ⚡ Power & Wiring

| Component                  | Description                     | Notes |
|---------------------------|---------------------------------|-------|
| **CR123A Battery Socket** | Replaced by direct ESP32 power  | Not used in retrofit |
| **3.3V Output**           | From ESP32 3.3V pin             | Powers the Lutron relay logic board |
| **GND**                   | Shared ESP32 ground             | Tied to Lutron PCB & optocouplers |

---

## 📶 Networking & Integration

| Component                  | Description                | Notes                                       | Link |
|---------------------------|----------------------------|---------------------------------------------|------|
| **Wi-Fi Network**         | ESP32 connects to LAN      | Used for MQTT communication                 | — |
| **Mosquitto MQTT Broker** | Self-hosted at `192.168.0.2` | Requires username & password auth          | [Mosquitto Add-on](https://www.home-assistant.io/integrations/mqtt/) |
| **Home Assistant** *(optional)* | Receives MQTT state | Optional integration layer                  | [Home Assistant](https://www.home-assistant.io/) |
| **Node-RED**              | Automation logic           | Handles ON/OFF commands, schedules, logic   | [Node-RED Add-on](https://github.com/hassio-addons/addon-node-red) |

---

## 🧠 Software / Dependencies

| Tool                         | Description                     | Notes | Link |
|------------------------------|---------------------------------|-------|------|
| **Arduino IDE**              | Flashing ESP32 firmware         | Required to upload `.ino` | [Arduino](https://www.arduino.cc/en/software) |
| **ESP32 Board Support**      | Required for compiling firmware | Install via Board Manager | [Espressif](https://github.com/espressif/arduino-esp32) |
| **PubSubClient Library**     | MQTT library for Arduino        | Install via Library Manager | [PubSubClient](https://github.com/knolleary/pubsubclient) |

---

## 🖼️ Diagrams & Visuals

- 📌 `hardware/wiring_diagram.png` — High-level wiring overview  
- 📌 `automation/schedules.md` — *(coming soon)* Node-RED flow explanation  

---

## 📌 GPIO Configuration

| GPIO    | Purpose                    |
|---------|-----------------------------|
| GPIO 5  | Triggers “ON” optocoupler  |
| GPIO 18 | Triggers “OFF” optocoupler |

> ⚠️ Ensure your wiring matches the pin assignments defined in firmware.

---

## ✅ Recap of System Behavior

- `hq/lobby_lights/on` → ESP32 pulses GPIO 5 for 200ms → Optocoupler presses **ON** button  
- `hq/lobby_lights/off` → ESP32 pulses GPIO 18 for 200ms → Optocoupler presses **OFF** button  
- Node-RED automates schedules, business hours, and dashboard button behavior  
- System operates independently of Lutron’s proprietary hardware limitations

---
