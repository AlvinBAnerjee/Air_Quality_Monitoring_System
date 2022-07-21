
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
ESP8266WiFiMulti WiFiMulti;
float lpg1=0;
float lpg2=0;
float dust1=0;
float dust2=0;
void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Alvin2", "loveumummum");

}

void loop() {
   WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Alvin2", "loveumummum");
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://192.168.0.3/getdata.php")) {  // HTTP
  

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
          split(payload+" ");
         Serial.println("yo");
         Serial.println(lpg1);
         Serial.println(dust1);
         Serial.println(lpg2);
         Serial.println(dust2);
        }
      } else {
        ;
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      ;
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
  else
  {
    Serial.println("We are doomed");
  }

  delay(1000);
}
void split(String str)
{
  String str1,str2,str3,str4="";
  int count=0;
  int n=str.length();
  String s="";
  for(int i=0;i<n;i++)
  {
    char ch=str.charAt(i);
    if(ch==' '||ch=='\n')
    {
      count++;
      if(count==1)
      {
        str1=s;
      }
      else if(count==2)
      {
        str2=s;
      }
      else if(count==3)
      {
        str3=s;
      }
      else if (count==4)
      {
        str4=s;
      }
      s="";
    }
    else
    {
      s=s+ch;
    }
    lpg1=str1.toFloat();
    dust1=str2.toFloat();
    lpg2=str.toFloat();
    dust2=str.toFloat();
  }
}
