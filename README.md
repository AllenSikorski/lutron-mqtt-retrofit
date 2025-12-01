# 🏷️ Retrofitting 277V Lutron Lighting with ESP32, MQTT, and Home Assistant

## 📖 Introduction

In our commercial building, we had Lutron-controlled 277V lighting that was locked into a proprietary ecosystem. Only Lutron sensors could control it, and only within their limited platform. We wanted more control: scheduled automation, Zigbee buttons, dashboard toggles, none of which Lutron offered out of the box.

This project documents how I reverse-engineered one of the working Lutron motion sensors, powered it via an ESP32, and used optocouplers to simulate button presses which effectively turned it into a **wireless relay bridge** we could now control with MQTT, Node-RED, and Home Assistant.

This project allowed us to modernize a legacy system using inexpensive, open-source hardware and opened the door for full smart lighting control with no dependence on vendor limitations.

---

## 🧠 Goals

- Retrofit proprietary Lutron lighting controls to be MQTT-controllable
- Remove reliance on Lutron's limited ecosystem (schedules, motion-only control)
- Integrate with Home Assistant dashboards and Zigbee buttons
- Add Node-RED logic and schedules for better automation
- Build a clean, documented setup others can replicate and adapt

---

## 🛠️ Hardware & Software Used

| Component                                  | Purpose                                                             |
|-------------------------------------------|----------------------------------------------------------------------|
| **ESP32 Dev Board** (HiLetgo ESP-32D)     | Wi-Fi + GPIO control of relays; powers the Lutron board             |
| **2x Optocoupler Modules** (Icstation EL817 12V) | Simulate button presses on Lutron PCB with electrical isolation |
| **Lutron LRF2-OKLB-P**                    | Repurposed as a wireless lighting controller (original motion sensor)|
| **WAGO Connectors**                       | Ground distribution and clean low-voltage wiring                    |
| **SMLIGHT SLZB-06p7 Zigbee Coordinator**  | Enables control via Zigbee buttons (Zigbee2MQTT / Home Assistant)   |
| **Node-RED + MQTT**                       | Handles control logic, timing, and device communication             |
| **Home Assistant**                        | UI control, automation, and system state tracking                   |

---

## 🔌 Wiring & Electrical

The CR123A battery was replaced with a regulated 3.3V directly from the ESP32, soldered to the Lutron device’s positive and negative terminals. 

Then, two optocoupler modules were connected to simulate pressing the ON and OFF buttons on the Lutron PCB. These were wired as follows:

- **ESP32 GPIO ➝ Optocoupler Input ➝ Optocoupler Output ➝ Button pad**
- A shared ground connection was distributed via WAGO connectors
- ESP32 powered via USB 5V, stepping down internally to 3.3V

📎 *Full schematic and wiring diagram available in* [`/hardware`](hardware)

---

## 📟 Firmware (ESP32)

- Written in Arduino/C++
- Connects to Wi-Fi with static IP
- Uses `PubSubClient` for MQTT communication
- Subscribes to:
  - `hq/lobby_lights/on`
  - `hq/lobby_lights/off`
- Simulates momentary button press (200ms) via GPIO HIGH → LOW

🔗 *See firmware:* [`/firmware/esp32_lutron_mqtt.ino`](firmware/esp32_lutron_mqtt.ino)

---

## 🔁 Node-RED Flow

- Listens to MQTT topic `hq/lobby_lights/set`
- Switch node splits ON vs OFF logic
- Publishes:
  - `hq/lobby_lights/on` or `off` to trigger the ESP32
  - `hq/lobby_lights/state` to update HA switch status

🔗 *See flow export:* [`/nodered/flow.json`](nodered/flow.json)

---

## 🏠 Home Assistant Integration

An MQTT switch is used to represent the lobby lights in Home Assistant:

```yaml
mqtt:
  switch:
    - name: "HQ Lobby Lights"
      state_topic: "hq/lobby_lights/state"
      command_topic: "hq/lobby_lights/set"
      payload_on: "on"
      payload_off: "off"
      state_on: "on"
      state_off: "off"
```

