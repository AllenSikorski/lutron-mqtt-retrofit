# 🏡 Home Assistant Integration: MQTT and Zigbee2MQTT Setup

This guide covers the MQTT broker and Zigbee2MQTT setup required for your ESP32-controlled Lutron retrofit to work with Home Assistant.

---

## ⚙️ Assumptions

This guide assumes the following are already in place:

- A fully functional Home Assistant instance (e.g., on a Raspberry Pi, Proxmox, ESXi, etc.)
- The ESP32 device has been flashed and is powered on and connected to WiFi
- A Zigbee Coordinator has already been set up and added to Home Assistant (e.g., SLZB-06p7 or equivalent)

---

## 🔌 Step 1: Install Mosquitto MQTT Broker

From the **Home Assistant Add-on Store**:

1. Search for **Mosquitto broker**
2. Install the add-on
3. Start the add-on
4. Set a username and password (this must match your `.ino` firmware)

### Recommended Network Configuration:

| Port | Purpose                        |
|------|--------------------------------|
| 1883 | MQTT (unencrypted)            |
| 1884 | MQTT over WebSocket           |
| 8883 | MQTT with SSL                 |
| 8884 | MQTT over WebSocket with SSL  |

---

## 📡 Step 2: Install Zigbee2MQTT

From the **Add-on Store**:

1. Install **Zigbee2MQTT**
2. Navigate to **Configuration**
3. Use the following config block (adapt as needed):

```yaml
data_path: /config/zigbee2mqtt
socat:
  enabled: false
  master: pty,raw,echo=0,link=/tmp/ttyZ2M,mode=777
  slave: tcp-listen:8485,keepalive,nodelay,reuseaddr,keepidle=1,keepintvl=1,keepcnt=5
  options: "-d -d"
  log: false
mqtt:
  base_topic: zigbee2mqtt
  server: mqtt://core-mosquitto
  user: your_mqtt_username
  password: your_mqtt_password
serial:
  port: tcp://192.168.X.X:6638  # IP and port of your Zigbee Coordinator
  baudrate: 115200
  adapter: zstack
  disable_led: false
advanced:
  transmit_power: 20
```
⚠️ The MQTT user and password must match what's in the Arduino .ino file that you flashed to the ESP32.

---
## ✅ Next Steps

- Confirm your ESP32 is publishing to MQTT
- Proceed to set up **Node-RED logic** for relay toggle and state feedback
- Configure the **Home Assistant Dashboard** to control and monitor the relay

---

## 🛠 Troubleshooting

| Symptom                              | Solution                                                       |
|--------------------------------------|----------------------------------------------------------------|
| ESP32 not showing up in MQTT topics | Check Wi-Fi connection and MQTT credentials                    |
| Zigbee2MQTT not starting            | Verify correct IP/port of Zigbee Coordinator in `serial.port`  |
| No communication with relay         | Confirm wiring and pin assignments on the ESP32                |




