
//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
//#include <DHT.h>
//#include <DHT_U.h>
#define FIREBASE_HOST "https://dex-bot-ab149.firebaseio.com/"
#define FIREBASE_AUTH "xDwkdBaJtCSix7grHXDBvREWK0nAPxMmVC89JZpQ"
#define WIFI_SSID "saif"
#define WIFI_PASSWORD "asdf1234"
String path = "/SensorValue/T";
String pathG = "/SensorValue/G";
String pathL = "/location";

FirebaseData Data;
    const int tempPin = 0;  //GPIO5 or D1 for Switch
    const int gasPin = A0;//GPIO5 or D1 for Switch
    const int gpsPin = 1;
  
void setup() {
  // put your setup code here, to run once:
  
    Serial.begin(115200);
     pinMode(tempPin, INPUT);
     pinMode(gasPin, INPUT);
     pinMode(gpsPin, INPUT);
    Serial.println();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
      Firebase.reconnectWiFi(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = analogRead(tempPin);
  float air = analogRead(gasPin);
  float loc = analogRead(gpsPin);
  //Sending Temperature Value To the Database
        if (Firebase.setFloat(Data, path , temp)))
        {
            Serial.print("Temperature: ");
            Serial.print(temp);
            Serial.println(" °C");
        }
        else
        {
            Serial.println("Data Sending Failed");
        }

        //Sending GAS VALUE to the database
         if (Firebase.setFloat(Data, pathG ,air))
        {

            Serial.print(air);
 
        }
        else
        {
            Serial.println("Data Sending Failed");
        }
        
        //Sending Location to the database
        if (Firebase.setFloat(Data, pathL ,air))
        {

            Serial.print(locPin);
 
        }
        else
        {
            Serial.println("Data Sending Failed");
        }


}
