#include<ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include<Servo.h>
Servo s1,s2;
WiFiClient client;
#define AIO_USERNAME  "SDINDUSTRIES"
Adafruit_MQTT_Client mqtt(&client,"io.adafruit.com", 1883, "name", "key");

Adafruit_MQTT_Subscribe fan = Adafruit_MQTT_Subscribe(&mqtt,AIO_USERNAME"/feeds/fan");
Adafruit_MQTT_Subscribe light = Adafruit_MQTT_Subscribe(&mqtt,AIO_USERNAME"/feeds/lights");
void mttconnect();
void setup() {
 // pinMode(2,OUTPUT);
  s1.attach(2);
  s1.write(90);
  s2.attach(4);
  s2.write(90);
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("ssid","pass");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println(".");
    }
 Serial.println("CONNECTED");
 Serial.println(WiFi.localIP());
mqtt.subscribe(&fan);
mqtt.subscribe(&light);
}

void loop() {
  
 mttconnect();
 Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &light) {
      Serial.print(F("Got: "));
    Serial.println((char *)light.lastread);
//    String k = "";
//    strcpy((char *)led.lastread,k);
 int n = atoi((char *)light.lastread);

if(n==1)
{     
    s1.write(60);
    }
    else s1.write(130);
  }
     else if (subscription == &fan) {
      Serial.print(F("Got: "));
    Serial.println((char *)fan.lastread);
//    String k = "";
//    strcpy((char *)led.lastread,k);
 int m = atoi((char *)fan.lastread);

if(m==1)
{     
    s2.write(40);
    }
    else s2.write(140);
  }
  }
}




  void  mttconnect(){
     int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
  





    
