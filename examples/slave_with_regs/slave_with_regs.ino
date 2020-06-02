// HardWire based Slave with Registers
// Copyright (c) 2020 Andrei Gramakov. All rights reserved.

// Demonstrates use of the HardWire library with VirtualRegisters

// Created 2 June 2020

// This example code is in the public domain.


#include <HardWire.h>
#include <VirtualRegs.h>

VirtualRegs registers;

void setup() {
  registers.Init(8);            // create registers
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  registers.SelectReg(Wire.read()); // set first byte is selecting the register
  while (Wire.available()) {        // if extra data
    registers.SetReg(Wire.read());  // write to the selected register
    registers.SelectNextReg();      // select next
  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(registers.GetRegAndNext()) // write a content of the register
                                        // and select next
}