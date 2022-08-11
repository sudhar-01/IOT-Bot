#include<ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include<Servo.h>
WiFiClient client;
#define AIO_USERNAME  "SDINDUSTRIES"
Adafruit_MQTT_Client mqtt(&client,"io.adafruit.com", 1883, "SDINDUSTRIES", "aio_gWqo25YztyOqTcQ1nnRWEnxVUetm");


Adafruit_MQTT_Subscribe light = Adafruit_MQTT_Subscribe(&mqtt,AIO_USERNAME"/feeds/led");
void mttconnect();
void setup() {
  pinMode(2,OUTPUT);
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("realme 3 Pro","abcd1234");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println(".");
    }
 Serial.println("CONNECTED");
 Serial.println(WiFi.localIP());
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
{   digitalWrite(2,HIGH); 
   
    }
    else digitalWrite(2,LOW);
  }
  }
}




  void  mttconnect(){
     int8_t ret;
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
  
