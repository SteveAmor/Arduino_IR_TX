/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;

void setup()
{
  pinMode(4,INPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  int STB_Status = digitalRead(4);
  digitalWrite(13, STB_Status);

  if(STB_Status) {  
    for (int i = 0; i < 3; i++) {
      irsend.sendRCMM(0x2420260C, 32); // BT Vision STB power code (Turn off)
      delay(91);
    }
  delay(2000);
  }
  
  for (int i = 0; i < 3; i++) {
    irsend.sendRCMM(0x2420260C, 32); // BT Vision STB power code (Turn on)
    delay(91);
  }  

  if(!STB_Status) { 
    delay(2000);  
  }  

  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x00FE02FD, 32); // Lounge TV power code (Turn on)
    delay(40);
  }
    
  delay(1000);
  for (int i = 0; i < 3; i++) {
    irsend.sendRCMM(0x2420A601, 32); // BT Vision CH1 code
    delay(91);
  }
  delay(1000);
  for (int i = 0; i < 3; i++) {
    irsend.sendRCMM(0x2420A65C, 32); // BT Vision Select code
    delay(91);
  }
  delay(1000);
  for (int i = 0; i < 3; i++) {
    irsend.sendRCMM(0x2420A65C, 32); // BT Vision Select code
    delay(91);
  }
 
  while(1) digitalWrite(13, digitalRead(4)) ; // repeat forever
}
