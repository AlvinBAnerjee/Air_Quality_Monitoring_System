#include<SoftwareSerial.h>
SoftwareSerial mySerial(2,3);//RX,TX
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySerial.available()>0)
    {
      Serial.print(mySerial.readString());
    }
    delay(500);
    Serial.print("hi");
}
