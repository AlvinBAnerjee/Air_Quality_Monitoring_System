#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 4); //RX,TX
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int mq_pin = A0;
const int sharpLEDPin = 11;   // Arduino digital pin 7 connect to sensor LED.
const int sharpVoPin = A1;   // Arduino analog pin 5 connect to sensor Vo.
static float Voc = 0.4;
const float K = 0.43;
int N=0;
void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(A0,INPUT);
  pinMode(sharpLEDPin,OUTPUT);
  digitalWrite(sharpLEDPin,HIGH);
  delay(2000);
   mySerial.begin(115200);
   
 lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  //lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("Ywrobot Arduino!");
   //lcd.setCursor(0,2);
  //lcd.print("Arduino LCM IIC 2004");
   //lcd.setCursor(2,3);
  //lcd.print("Power By Ec-yuan!");
  delay(2000);
  
}

void loop() {
  float density_avg=0;
  float lpg_avg=0;
  for(int i=1;i<=50;i++)
  {
  int lpg=analogRead(A0);
  digitalWrite(sharpLEDPin,LOW);
  delayMicroseconds(280);
  int VoRaw=analogRead(sharpVoPin);
  digitalWrite(sharpLEDPin,HIGH);
  delayMicroseconds(9680);
  float Vo=VoRaw;
  Vo=Vo*5.0/1024.0;
   Serial.print("VoRaw=");
  Serial.println(Vo);
  float dV=Vo-Voc;
  
  float dustDensity=dV/K*100;
  density_avg=density_avg+dustDensity;
  lpg_avg=lpg_avg+lpg;
  /*Serial.print("Vo=");
  Serial.print(Vo);
  
  Serial.print(",");
  Serial.print("lpg=");
  Serial.print(lpg);
  Serial.print(",");
  Serial.print("Density=");
  Serial.print(dustDensity);
  Serial.print("ug/m3");
  //Serial.print(Voc);
  Serial.println();
  */
  //Serial.print("Density=");
  //Serial.print(dustDensity);
  //Serial.print("ug/m3");
  //Serial.println();
  }
  density_avg=density_avg/50;;
  lpg_avg=lpg_avg/50;
  Serial.print("lpg=");
  Serial.print(lpg_avg);
  lcd.setCursor(0,0);
  lcd.print("LPG="+String(lpg_avg));
  Serial.print(",");
  Serial.print("Density=");
  Serial.print(density_avg);
  Serial.print("ug/m3");
  lcd.setCursor(0,1);
  lcd.print("PM2.5="+String(density_avg)+"ug/m3");
  Serial.println();

  //mySerial.print("lpg=");
  mySerial.print(lpg_avg);
  mySerial.print(" ");
  //mySerial.print("Density=");
  mySerial.print(density_avg);
  //mySerial.print("ug/m3");
  mySerial.println();
  
  
  
  
  delay(10000);
}




    
    
