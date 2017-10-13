/*
 * IoT Button
 * project by :- Sachin Soni(techiesms)
 * for project details :- www.fb.com/techiesms
 */

#include <ESP8266WiFi.h>

const char* ssid     = "mnmkn";  
const char* password = "user.100"; 
int button= 2;             // D1 pin of ESP12E board
//int LED =16;               // D0 pin of ESP12E board
const char* host = "maker.ifttt.com";     //IFTTT channel address
int buttonState = LOW;

void setup() {
  pinMode(button, INPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);
  digitalWrite(LED_BUILTIN,LOW); // By default Off state
  }

int value = 1;
void loop() {
   buttonState = digitalRead(button);
    if (buttonState == HIGH) {                     //button is pulled down to ground via 10k resistor
       if (value == 1){
         WiFi.disconnect();
        Serial.println("Button Pressed");
       WiFi.begin(ssid, password); // connecting to wifi
       while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Conencting");
       delay(500);
       }
       digitalWrite(LED_BUILTIN,HIGH);  // LED turns On
       WiFiClient client;
       const int httpPort = 80;
       if (!client.connect(host, httpPort)) {
        Serial.println("Weak Network");
       return;
       }
       // We now create a URI for the request
       String url = "/trigger/email/with/key/dBNSgnkAj4qLww8us4Y-kl";   //our link to trigger the event with special key and event name 
  
       // This will send the request to the server
       client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");  // GET request 
       
       value = 0;
       delay(5000);
       digitalWrite(LED_BUILTIN,LOW);  // LED turns Off
       }
    }
    else{
    value = 1;
    delay(500);
    }
}
