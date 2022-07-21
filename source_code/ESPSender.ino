#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
void setup() {
  Serial.begin(115200);
  delay(20000);
  Serial.println("HELLO WORLD");
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Alvin2", "loveumummum");
}
String num1,num2="";
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    String str=Serial.readString();
    extract_num(str);
    //Serial.print(str);
    //Serial.print("Calc");
    //Serial.print(num1);
    //Serial.print(",");
    //Serial.println(num2);
    float lpg=num1.toFloat();
    float density=num2.toFloat();
   // Serial.println("Converted");
   // Serial.print(lpg);
    //Serial.print(",");
    //Serial.println(density);
    if(lpg!=0&&density!=0)
    {
       if ((WiFiMulti.run() == WL_CONNECTED))
       {

        WiFiClient client;
        HTTPClient http;
        Serial.print("[HTTP] begin...\n");
        String url="http://192.168.0.3/sendValue.php?sensor_id=1&lpg="+num1+"&density="+String(density);
        Serial.println(url);
        if (http.begin(client, url))
        {
           Serial.print("[HTTP] GET...\n");
           int httpCode = http.GET();
           if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
        }
        else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
        
    }
    }
  }
  delay(5000);
}
int extract_num(String str)
{
 // Serial.print("String=");
  //Serial.print(str);
  int space=0;
  num1="";
  num2="";
 // Serial.print("length=");
  //Serial.println(str.length());
  for(int i=0;i<str.length();i++)
  {
    char ch=str.charAt(i);
    //Serial.print(space);
    //Serial.print(ch);
    //Serial.print(":");
    if(ch==' '||ch=='\n')
    {
      space++;
      if(space==2)
      return 0;
    }
    if(space==0)
    {
      num1=num1+ch;
    }
    if(space==1)
    {

      num2=num2+ch;
    }
      
  }
}
