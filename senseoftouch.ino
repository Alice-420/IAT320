#include <CapacitiveSensor.h>

 
#define speaker 11


// Set the Send Pin & Receive Pin.
CapacitiveSensor   cs_2_3 = CapacitiveSensor(2,3);        
CapacitiveSensor   cs_2_4 = CapacitiveSensor(2,4);         
CapacitiveSensor   cs_2_5 = CapacitiveSensor(2,5);     
CapacitiveSensor   cs_2_6 = CapacitiveSensor(2,6);     
CapacitiveSensor   cs_2_7 = CapacitiveSensor(2,7);       


void setup() {
  cs_2_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
}

void loop() {
  long start = millis();
  
  long soundDo =  cs_2_3.capacitiveSensor(3000);
  long soundRe =  cs_2_4.capacitiveSensor(3000);
  long soundMi =  cs_2_5.capacitiveSensor(3000);
  long soundFa =  cs_2_6.capacitiveSensor(3000);
  long soundSol =  cs_2_7.capacitiveSensor(3000);
  
  if (soundDo > 500) {
    tone(speaker,100);
  }
  if (soundRe > 500) {
    tone(speaker,200);   
  }
  if (soundMi > 500) {
    tone(speaker,300);
  }
  if (soundFa > 500) {
    tone(speaker,400);
  }
  if (soundSol > 500) {
    tone(speaker,500);

  
  if (soundDo<=500  &  soundRe<=500  &  soundMi<=500 & soundFa<=500  &  soundSol<=500){
    noTone(speaker);
  }
  
  delay(10);                             
}
