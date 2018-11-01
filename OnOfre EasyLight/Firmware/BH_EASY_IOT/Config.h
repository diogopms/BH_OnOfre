#define BHONOFRE
#include <JustWifi.h> //https://github.com/xoseperez/justwifi
#include <ESP8266mDNS.h>
#include <DallasTemperature.h> // https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <Timing.h> //https://github.com/scargill/Timing
#include <AsyncMqttClient.h> //https://github.com/marvinroger/async-mqtt-client
#include <ArduinoJson.h> ////Install from Arduino IDE Library Manager
#include <FS.h> 
#include <Ticker.h>
#include <ESPAsyncTCP.h> //https://github.com/me-no-dev/ESPAsyncTCP
#include <ESPAsyncWebServer.h> //https://github.com/me-no-dev/ESPAsyncWebServer
#include <AsyncJson.h> //https://github.com/me-no-dev/ESPAsyncWebServer
#define ENABLE false
#define DISABLE true
#ifdef BHPZEM
#define HARDWARE "bhpzem" 
#define MODEL "004T"
#endif
#ifdef BHONOFRE
#define HARDWARE "bhonofre" 
#define MODEL "Easy-Light"
#endif
#define FIRMWARE_VERSION 2
#define CONFIG_FILENAME  "/config_"+String(HARDWARE)+".json"
#define CONFIG_BUFFER_SIZE 512
#define WIFI_SSID "VOID SOFTWARE"
#define WIFI_SECRET "blackiscool"  
#define RELAY_ONE 4
#define RELAY_TWO 5 
#define SWITCH_ONE 12
#define SWITCH_TWO 13
//MQTT  
#define MQTT_BROKER_IP ""
#define MQTT_BROKER_PORT 1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define PAYLOAD_ON "ON"
#define PAYLOAD_OFF "OFF"
#define PAYLOAD_PULSE_OFF_ON "PULSE_OFF"
#define PAYLOAD_PULSE_ON_OFF "PULSE_ON"
#define HOME_ASSISTANT_AUTO_DISCOVERY_PREFIX  "homeassistant"
#define DELAY_NOTIFICATION 5000 //5 seconds
//CONTROL FLAGS
bool shouldReboot = false;
bool reloadMqttConfiguration = false;
bool wifiUpdated = false;
bool laodDefaults = false;
DynamicJsonBuffer jsonBuffer(CONFIG_BUFFER_SIZE);
JsonArray& getJsonArray(){
  return jsonBuffer.createArray();
  }
JsonArray& getJsonArray(File file){
  return jsonBuffer.parseArray(file);
  }

  JsonObject& getJsonObject(){
  return jsonBuffer.createObject();
  }
JsonObject& getJsonObject(File file){
  return jsonBuffer.parseObject(file);
  }
  JsonObject& getJsonObject(const char* data){
  return jsonBuffer.parseObject(data);
  }