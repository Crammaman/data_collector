#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson-v6.19.4.h>

#define AOUT_PIN      PIN_A0
#define SSID          "MoDeans2"
#define PASSWORD      "I was born this way Stuart"
#define DATA_SEND_URL "http://192.168.0.112/recordings.json"

StaticJsonDocument<200> config;


WiFiClient wifi_client;
HTTPClient http;

int value = 0;


void connect_to_wifi() {

  // Connect to WiFi
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
}

void ensure_config(){
  config["device_id"] = 1;
  // sprintf(str, "{\"data\": %d, \"device_id: \"%s\"}", value, config['device_id']);
  // http.begin(wifi_client,DATA_SEND_URL);
  // http.addHeader("Content-Type","application/json");
  // int httpCode = http.POST(str);
  // Serial.print("Post Result: ");
  // Serial.println(httpCode);
  // http.end();
}

void setup() {
  Serial.begin(9600);  
  
  connect_to_wifi();

  ensure_config();

  delay(2000);
}

void loop() {
  value = analogRead(AOUT_PIN); // read the analog value from sensor

  Serial.print("Moisture value: ");
  Serial.println(value);

  StaticJsonDocument<200> request_payload;
  request_payload["data"] = value;
  request_payload["device_id"] = config["device_id"];
  http.begin(wifi_client,DATA_SEND_URL);
  http.addHeader("Content-Type","application/json");
  int httpCode = http.POST(request_payload.as<String>());
  Serial.print("Post Result: ");
  Serial.println(httpCode);
  http.end();
  delay(5000);
}