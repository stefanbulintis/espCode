#include "ESP8266WiFi.h"
#include "ThingSpeak.h"

const unsigned int MAX_MESSAGE_LENGTH = 12;
const char* ssid = "gjbh"; 
const char* password = "camerabetivilor"; 

const char * apiKey = "JT80L540KZQP3XG5";
unsigned long Channel_ID = 2135238;

const char* server = "api.thingspeak.com";
const int Field_Number_1 = 1;
//const int Field_Number_2 = 2;

char msg;
WiFiClient client;
int sendToTs;
int safeSend = 0;

void setup() {
  ThingSpeak.begin(client);
  Serial.begin(115200);
  while (!Serial) {
    ; 
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

}
void loop() {
  if (Serial.available() > 0) {
    char incomingData = Serial.read();
    if (incomingData == '1' || incomingData == '2' || incomingData == '0') {  //am pus condiția ca incomingData sa fie 1 sau 2 sau 0
      sendToTs = incomingData - '0';  //am convertit char in int
      safeSend = 1;
    }
  }

  if (safeSend == 1) {
    Serial.println(sendToTs);
    ThingSpeak.writeField(Channel_ID, 1, sendToTs, apiKey);
    safeSend = 0;
  }

  delay(15000);
}

