//Set command  like f+number where f mean fan and number mean speed;
// same thing for peltier p+number
//Same senarion for vibrate motor
//Verified these pin befor deploy .these pins must  be PWM(pulse with modulation) groups to perfon analogWrite function
//This code is only for  our application test

#include <Arduino.h>
#include<SoftwareSerial.h>
#define RX 2
#define TX 3
String command_voice;
static const int peltier_pin=6;
static const int vibration_pin=8;
static const int fan_pin=9;
static const int switch_button=5;
int setfanspeed=255,
setpeltierheat=255,
setvibrate_motor=255;
SoftwareSerial blue(RX,TX);

void setup() {
  Serial.begin(9600);
  blue.begin(9600);
  pinMode(peltier_pin,OUTPUT);
  pinMode(fan_pin,OUTPUT);
  pinMode(vibration_pin,OUTPUT);
  pinMode(switch_button,INPUT);
  analogWrite(fan_pin,setfanspeed);
  analogWrite(peltier_pin,setpeltierheat);
  analogWrite(vibration_pin,setvibrate_motor);
  while(!blue.available());
}


void loop() {
 if(blue.available()>0){
   String learnSerial=blue.readString();
   if(learnSerial.startsWith("f")){
     String fanspeed=learnSerial.substring(learnSerial.indexOf("f")+1,learnSerial.length());
     setfanspeed=fanspeed.toInt();
     Serial.print("Now fand speed is:");
     Serial.print(setfanspeed);//This is just to debug 
     analogWrite(fan_pin,setfanspeed);
     
   }
   else if(learnSerial.startsWith("p")){
     String peltier_heat=learnSerial.substring(learnSerial.indexOf("p")+1,learnSerial.length());
     setpeltierheat=peltier_heat.toInt();
     Serial.print("the number of bit send to petltier now is:");
     Serial.print(setpeltierheat);//This is just to debug 
     analogWrite(peltier_pin,setpeltierheat);
   }
   else if(learnSerial.startsWith("v")){
     String vibration_motor=learnSerial.substring(learnSerial.indexOf("v")+1,learnSerial.length());
     setvibrate_motor=vibration_motor.toInt();
     Serial.print("the number of bit send to vibtration now is:");
     Serial.print(setvibrate_motor);//This is just to debug 
     analogWrite(vibration_pin,setvibrate_motor);
   }
   else if(learnSerial=="Increment fan speed"  || learnSerial=="fan speed" || learnSerial=="Increment fan "){
     if(setfanspeed>255){
       setfanspeed=255;
     }
     else{
       setfanspeed +=50;// This is random value a choose
     }
      analogWrite(fan_pin,setfanspeed);
   }
   else if(learnSerial=="decrement fan speed"  || learnSerial=="fan speed" || learnSerial=="decrement fan "){
     if(setfanspeed<0){
       setfanspeed=0;
     }
     else{
       setfanspeed -=50;// This is random value a choose
     }
     analogWrite(fan_pin,setfanspeed);
   }
   else if(learnSerial=="decrement peltier  heating"  || learnSerial=="decrement heating " || learnSerial=="decrement peltier "){
     if(setpeltierheat<0){
       setpeltierheat=0;
     }
     else{
       setpeltierheat -=50;// This is random value a choose
     }
     analogWrite(peltier_pin,setpeltierheat);
   }
   else if(learnSerial=="ıncrement peltier  heating"  || learnSerial=="ıncrement heating " || learnSerial=="ıncrement peltier "){
     if(setpeltierheat>255){
       setpeltierheat=255;
     }
     else{
       setpeltierheat +=50;// This is random value a choose
     }
     analogWrite(peltier_pin,setpeltierheat);
   }
   else if(learnSerial=="ıncrement massage"  || learnSerial=="ıncrement head" || learnSerial=="ıncrement head massage"){
     if(setvibrate_motor>255){
       setvibrate_motor=255;
     }
     else{
       setvibrate_motor+=50;// This is random value a choose
     }
     analogWrite(vibration_pin,setvibrate_motor);
   }
   else if(learnSerial=="decrement massage"  || learnSerial=="decrement head" || learnSerial=="decrement head massage"){
     if(setvibrate_motor<0){
       setvibrate_motor=0;
     }
     else{
       setvibrate_motor-=50;// This is random value a choose
     }
     analogWrite(vibration_pin,setvibrate_motor);
   }

   learnSerial=" ";
 }
}