/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

// add library IRremote.zip to Arduino IDE (this library includes the RCMM protocol).
// Arduino A0 is connected to SCART pin 19 (composite video out) on the YouView STB.
// 0.1uF capacitor between pin 17 and pin 19.
// Arduino GND connected to SCART pin 17.
// Arduino LED (pin 13) reflects if STB is on or off.

#include <IRremote.h>

IRsend irsend;

void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  delay(2000);
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x00FE02FD, 32); // Tokai TV power code
    delay(40);
}

void loop() { 
  
  char code;
  int STB_Status = isTVOn();
  digitalWrite(13, STB_Status);
  
  if(STB_Status) {  
    for (int i = 0; i < 1; i++) {
      irsend.sendNEC(0x000800FF, 32); // YouView STB power code (Turn off)
      delay(50);
    }
  delay(1000);
  }

  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x000800FF, 32); // YouView STB power code (Turn on)
    delay(50);
  }  

  if(!STB_Status) { 
    delay(4000);  
  }  
  
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x0008827D, 32); // YouView Back code
    delay(50);
  }    
  
  delay(100);
  
  for (int i = 0; i < 1; i++) {
    irsend.sendNEC(0x0008C03F, 32); // YouView CH1 code
    delay(50);
  }

  while(1) {  // repeat forever
  
    digitalWrite(13, isTVOn());
      
    if (Serial.available()) {
      code = Serial.read();
      switch (code) {
        case 'M':
        case 'm':
          for (int i = 0; i < 3; i++) {
            irsend.sendSony(0x290, 12); // Sony Mute (on and off)
            delay(100);
          }
          break;
        case 'P':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x000846B9, 32); // YouView pause on
            delay(50);
            irsend.sendNEC(0x574332CD, 32); // Sky pause on
          }
          break;
        case 'p':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x000806F9, 32); // YouView pause off (it's actually Play)
            delay(50);
            irsend.sendNEC(0x574332CD, 32); // Sky pause off
          }
          break;  
        case 'S':
        case 's':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x000800FF, 32); // YouView standby code
            delay(50);
          }
          break;          
        case '1':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x0008C03F, 32); // YouView CH1 code
            delay(50);
          }
          break;
        case '2':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x000820DF, 32); // YouView CH2 code
            delay(50);
          }
          break; 
        case '3':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x0008A05F, 32); // YouView CH3 code
            delay(50);
          }
          break;
        case '4':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x0008609F, 32); // YouView CH4 code
            delay(50);
          }
          break;
        case '5':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x0008E01F, 32); // YouView CH5 code
            delay(50);
          }
          break;
        case '6':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x000810EF, 32); // YouView CH6 code
            delay(50);
          }
          break;
        case '7':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x0008906F, 32); // YouView CH7 code
            delay(50);
          }
          break;
        case '8':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x000850AF, 32); // YouView CH8 code
            delay(50);
          }
          break;
        case '9':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x0008D02F, 32); // YouView CH9 code
            delay(50);
          }
          break;
        case '0':
          for (int i = 0; i < 1; i++) {
            irsend.sendNEC(0x000830CF, 32); // YouView CH0 code
            delay(50);
          }
          break;           
      }
      delay(100);
    }
  }
}

boolean isTVOn() {
  if(analogRead(A0) > 100) {
    return true;
  }
  return false;
}
