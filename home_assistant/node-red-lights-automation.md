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
