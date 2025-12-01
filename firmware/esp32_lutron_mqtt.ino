#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char* ssid = "your-ssid";
const char* password = "your-ssid-password";

// Static IP
IPAddress local_IP(192, 168, 0, 31);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(192, 168, 0, 7);
IPAddress secondaryDNS(1, 1, 1, 1);

// MQTT
const char* mqtt_server = "192.168.0.2";
const char* mqtt_user = "your-mqtt-username";
const char* mqtt_password = "your-mqtt-password";

// Topics
const char* topic_on = "hq/lobby_lights/on";
const char* topic_off = "hq/lobby_lights/off";

// GPIO pins
#define ON_PIN 5
#define OFF_PIN 18

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) message += (char)payload[i];

  if (strcmp(topic, topic_on) == 0) {
    digitalWrite(ON_PIN, HIGH);
    delay(200);
    digitalWrite(ON_PIN, LOW);
  } else if (strcmp(topic, topic_off) == 0) {
    digitalWrite(OFF_PIN, HIGH);
    delay(200);
    digitalWrite(OFF_PIN, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("lobby_lights_controller", mqtt_user, mqtt_password)) {
      client.subscribe(topic_on);
      client.subscribe(topic_off);
    } else {
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ON_PIN, OUTPUT);
  pinMode(OFF_PIN, OUTPUT);
  digitalWrite(ON_PIN, LOW);
  digitalWrite(OFF_PIN, LOW);

  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}
