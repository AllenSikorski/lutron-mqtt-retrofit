# Lobby Lights Automation (Node-RED)

This flow controls the lobby lights using MQTT, Home Assistant input_booleans, Zigbee buttons, and motion sensors. It also includes scheduled automations and state feedback.

## 🧠 Features

- Motion-activated lighting (with smart delay and override)
- Scheduled on/off for weekdays and nights
- Zigbee button support for manual control
- State publishing for sync across UI/automations
- Home Assistant `input_boolean.hq_lobby_motion_detection` control
- Time-based disable/re-enable of motion logic

## 🧩 MQTT Topics Used

| Topic | Purpose |
|-------|---------|
| `hq/lobby_lights/set` | Accepts `"on"` or `"off"` |
| `hq/lobby_lights/on` / `off` | Sends control commands |
| `hq/lobby_lights/state` | Reports current state |

## 📥 Import This Flow

Import the flow from [`lobby-lights.flow.json`](./node-red-lights-flow.json) into your Node-RED instance via:

1. Top-right menu → **Import**
2. Paste the JSON or upload the file
3. Deploy!

---

# 🧠 Zigbee-Controlled Lobby Lights via MQTT and Node-RED

This flow allows **any Zigbee device**, such as motion sensors or buttons, to control lutron lighting via MQTT. Designed to integrate with Home Assistant, it enables clean, reliable smart lighting control using your existing MQTT broker and automation setup.

---

## 📦 Overview

This Node-RED logic listens for `on` or `off` commands on an MQTT topic (`hq/lobby_lights/set`) and routes those commands to:

- A relay output topic (`hq/lobby_lights/on` or `.../off`)
- A state update topic (`hq/lobby_lights/state`) to reflect current status

### ✅ Benefits:
- Fully Zigbee-agnostic: works with **any** device in Zigbee2MQTT
- Compatible with Home Assistant for real-time control and monitoring
- Easily extendable with motion sensors, buttons, or automation rules

---

## 🔁 Node-RED Flow Logic

### ➡️ Incoming Command

The flow begins by subscribing to the MQTT topic `home/lobby/lights/set`.


This topic expects a payload of either `"on"` or `"off"`.

Once a message is received, it passes through an **On/Off Switch** node. This node checks the payload and routes the message accordingly:

- `"on"` → triggers the lobby lights ON path
- `"off"` → triggers the lobby lights OFF path

Each path handles the appropriate relay logic and state publishing actions (shown in the image below).

---


