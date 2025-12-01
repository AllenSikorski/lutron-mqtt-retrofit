# 🧰 Soldering Guide: ESP32-Controlled Retrofit for Lutron RMJ-16R-DV-B

This guide walks you through the full process of modifying a Lutron RMJ-16R-DV-B relay module to integrate with an ESP32 for Home Assistant control via MQTT. You'll bypass the battery, solder directly to the button pads, and use optocouplers to safely trigger the device.

---

## 📸 1. Hardware Overview

We'll be working with the following parts:

- **Lutron RMJ-16R-DV-B** relay module
- **ESP32 Board**
- **Icstation EL817 optocoupler module**
- Jumper wires
- Soldering iron + thin rosin-core solder
- Enclosure box for mounting


<img width="291" height="384" alt="image" src="https://github.com/user-attachments/assets/04529156-9967-4746-ac83-bd0d15f6701b" />


<img width="451" height="718" alt="image" src="https://github.com/user-attachments/assets/4bc69c06-4f20-4cf2-857f-96b335153ebb" />


---

## 🔧 2. Disassemble the Lutron Relay

Carefully open the enclosure and extract the internal PCB. Be gentle with the battery terminals — you’ll be soldering to them later.

<img width="1195" height="648" alt="image" src="https://github.com/user-attachments/assets/a4088c7e-ff2e-4252-bb26-383b91e80108" />


---

## 🪛 3. Identify Button Pads

Flip the board to locate the three metal button pads at the bottom. These pads are tied to manual toggling of the lighting relay.

<img width="1229" height="499" alt="image" src="https://github.com/user-attachments/assets/35085a31-7150-46e7-8e4c-969636e4f28d" />


---

## 🧪 4. Test Button Functionality (Optional)

Before soldering, test that shorting each button pad to the nearby GND briefly activates a relay click. This confirms you're tapping the correct pads for toggling.

---

## 🔌 5. Soldering Power to the Board (ESP32 → Sensor)

The Lutron board is designed for a CR123A battery (3.0V), but in practice, it tolerates 3.3V well.

- Solder 3.3V from the ESP32 to the **positive** battery terminal.
- Solder GND from the ESP32 to the **negative** battery terminal.

<img width="1240" height="516" alt="image" src="https://github.com/user-attachments/assets/dcfe7661-368a-4074-9541-5769cf022af7" />

---

## 🔧 6. Solder Wires to Button Pads

Now solder thin wires to each of the three button pads.

📷 **Insert:**  
`20251201_180927631_iOS.heic` — _Wires soldered to button pads_  

> 💡 Tip: Tin the wire tips first. Use tweezers to hold the wire while tapping solder quickly to avoid pad damage.

---

## 🔁 7. Connect Button Wires to Optocoupler Inputs

Each wire will go into the input side of an **EL817 optocoupler module**. The ESP32 will trigger the optos, and the optos will act like "virtual fingers" pressing the Lutron buttons.

<img width="695" height="908" alt="image" src="https://github.com/user-attachments/assets/1f8c01ee-4f53-4ef5-9198-95cc69ac3b46" />

---

## 🧠 8. ESP32 Wiring Notes

- Each optocoupler’s input side is connected to an ESP32 GPIO and GND.
- The output side (phototransistor) connects across the button pad wire and the Lutron board's GND.

<img width="865" height="664" alt="image" src="https://github.com/user-attachments/assets/2a5ac5ea-5109-4bc4-9cf8-2547e3cc189e" />

---

## 📦 9. Final Enclosure Mount

Mount all components (ESP32, optos, sensor board) into a weatherproof enclosure if needed. Route all wiring securely.


<img width="1156" height="856" alt="image" src="https://github.com/user-attachments/assets/339db338-2a37-4957-a7be-7ff0fe04746e" />


---

## ✅ Done!

Now you can control high-voltage commercial lighting relays via Home Assistant — all powered by your ESP32, optocouplers, and clever soldering.

<img width="1089" height="688" alt="image" src="https://github.com/user-attachments/assets/a8572ec7-63e6-4158-aabd-d1164252c6b1" />

Next step: [View firmware setup ➜](../firmware/README.md)

---
