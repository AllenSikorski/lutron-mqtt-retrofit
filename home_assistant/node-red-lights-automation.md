# lutron Lights Automation (Node-RED)

This flow controls the lutron lights using MQTT, Home Assistant input_booleans, Zigbee buttons, and motion sensors. It also includes scheduled automations and state feedback.

## 🧠 Features

- Motion-activated lighting (with smart delay and override)
- Scheduled on/off for weekdays and nights
- Zigbee button support for manual control
- State publishing for sync across UI/automations
- Home Assistant `input_boolean.hq_lutron_motion_detection` control
- Time-based disable/re-enable of motion logic

## 🧩 MQTT Topics Used

| Topic | Purpose |
|-------|---------|
| `hq/lutron_lights/set` | Accepts `"on"` or `"off"` |
| `hq/lutron_lights/on` / `off` | Sends control commands |
| `hq/lutron_lights/state` | Reports current state |

## 📥 Import This Flow

Import the flow from [`lutron-lights.flow.json`](./node-red-lights-flow.json) into your Node-RED instance via:

1. Top-right menu → **Import**
2. Paste the JSON or upload the file
3. Deploy!

---

# 🧠 Zigbee-Controlled lutron Lights via MQTT and Node-RED

This flow allows **any Zigbee device**, such as motion sensors or buttons, to control lutron lighting via MQTT. Designed to integrate with Home Assistant, it enables clean, reliable smart lighting control using your existing MQTT broker and automation setup.

---

## 📦 Overview

This Node-RED logic listens for `on` or `off` commands on an MQTT topic (`hq/lutron_lights/set`) and routes those commands to:

- A relay output topic (`hq/lutron_lights/on` or `.../off`)
- A state update topic (`hq/lutron_lights/state`) to reflect current status

### ✅ Benefits:
- Fully Zigbee-agnostic: works with **any** device in Zigbee2MQTT
- Compatible with Home Assistant for real-time control and monitoring
- Easily extendable with motion sensors, buttons, or automation rules

---

# 🔁 Node-RED Flow Logic

## ➡️ Incoming Command

The flow begins by subscribing to the MQTT topic `home/lutron/lights/set`.

<img width="965" height="421" alt="image" src="https://github.com/user-attachments/assets/52d48d57-c408-472e-ac45-03f9753d6922" />

This topic expects a payload of either `"on"` or `"off"`.

Once a message is received, it passes through an **On/Off Switch** node. This node checks the payload and routes the message accordingly:

- `"on"` → triggers the lutron lights ON path
- `"off"` → triggers the lutron lights OFF path

Each path handles the appropriate relay logic and state publishing actions (shown in the image below).

---

## 🕒 Scheduled lutron Lights Control (Node-RED)

This flow automatically turns the **lutron lights ON at 7:00 AM** and **OFF at 5:00 PM** using MQTT.

<img width="881" height="510" alt="image" src="https://github.com/user-attachments/assets/708a2c57-d3d1-4489-a8e2-fb018a084d27" />

It's designed to be generic and works with any system listening on your MQTT topics—whether that's Home Assistant, a custom ESP32 setup, or another integration.

### 🔧 Flow Structure

- **Inject Nodes**: 
  - `Turn On lutron Lights at 7am` (daily trigger)
  - `Turn Off lutron Lights 5pm` (daily trigger)

- **Function Nodes**: 
  - `Payload On` sets payload to `"on"`
  - `Payload Off` sets payload to `"off"`

- **MQTT Publish**:
  - Sends `"on"` to topic `hq/lutron_lights/on`
  - Sends `"off"` to topic `hq/lutron_lights/off`
  - Publishes current state (`"on"` or `"off"`) to `hq/lutron_lights/state`

> 💡 You can connect your own sensors, dashboards, or automation tools to these MQTT topics to trigger additional actions or reflect the current state of the lights.

---

## Lutron Motion Light Control – Node-RED Motion Flow

This flow listens for motion events and turns on the lutron lights if automation is enabled. It uses a toggle to easily turn the automation on or off from Home Assistant or any other source.

<img width="911" height="176" alt="image" src="https://github.com/user-attachments/assets/2d8b375c-5cc4-4034-bf58-bd4656320bdd" />


### 🔄 Flow Logic

- **Trigger**: Any motion sensor publishes a motion detection event.
- **Toggle Check**: The flow checks if motion-based lighting is enabled via a boolean control (such as `input_boolean.motion_enabled`).
- **Action**:
  - If enabled, the flow sends a message to turn the lights **on**.
  - It also updates the light’s **state topic** for tracking in Home Assistant.
 
---

## 🔘 Lutron Lights Button Toggle Flow (Node-RED)

This flow provides a basic **on/off toggle logic** for lutron lights using **Node-RED** and **MQTT**.

<img width="850" height="313" alt="image" src="https://github.com/user-attachments/assets/e1c87fd0-1f39-4bcc-807f-e40a0cd25684" />

It starts with a trigger: this could be a physical button, motion sensor, or any input that sends a message to the `On/Off Switch` node.

Based on the current state, the switch routes the message to either:
- **Turn lights ON** (and publish the new state as "on")
- **Turn lights OFF** (and publish the new state as "off")

This structure can be reused with any sensor or condition you want. The actual device logic can be substituted as needed. This just handles toggling and broadcasting the result to MQTT topics for use in **Home Assistant** or other systems.

You can easily replace the input or customize the MQTT topics to match your environment.

---

##💡 Scheduled Interval Light Shutoff Flow

This Node-RED flow handles multiple scheduled **interval-based shutdowns** of lutron lights via MQTT. It ensures lights turn off during specific time blocks every day and weekends.

<img width="805" height="197" alt="image" src="https://github.com/user-attachments/assets/70249942-7da3-4774-8c2a-592aaf9570bb" />

---

### 🧠 Overview

The flow is made up of three scheduled Inject nodes:

- `Everyday Interval Lights Shutoff 5pm–11pm`
- `Everyday Interval Lights Shutoff 1am–7am`
- `Weekend Interval Lights Shutoff 8am–4pm`

Each of these triggers:

- A **direct MQTT message** to turn off the lights (`lutron Lights Off`).
- A **function node** called `Payload Off` to set the MQTT state payload to `"OFF"`.
- An MQTT publish node (`Publish OFF state`) to update the current known state in the system.

---

### 📨 MQTT Topics

You should configure your ESP32-based relay system to **subscribe** to the appropriate topic (e.g.): `home/lutron/lights/set`


When this topic receives the payload `"OFF"`, your device should deactivate the connected light or relay.

Optionally, publish the current state to:

With payload:

```json
{
  "state": "OFF"
}
```
---

# ✅ Wrapping Up

This lighting control system provides **reliable automation** for energy savings and operational efficiency. Whether controlled by manual push-button, scheduled timers, or external motion sensors, the Node-RED flow ensures:

- **Consistent light control** across defined schedules
- **Real-time state publishing** to MQTT for UI dashboards or third-party integrations
- **Modular logic** that can be extended for holidays, occupancy triggers, or overrides

This setup gives a solid foundation for **smart building automation**, and can easily scale as your needs evolve.
