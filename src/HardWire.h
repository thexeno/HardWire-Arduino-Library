/*
  TwoWire.h - TWI/I2C library for Arduino & Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
  Modified 2016 by Enrico Sanino to derive the Hard Wire 1.0 (https://github.com/thexeno/HardWire-Arduino-Library)
*/

#ifndef TwoWire_h
#define TwoWire_h

#include <inttypes.h>
#include "Stream.h"

#define BUFFER_LENGTH 32
#define HARD_WIRE_MODE 1
#define NORMAL_MODE 1

// WIRE_HAS_END means Wire has end()
#define WIRE_HAS_END 1

class TwoWire : public Stream
{
  private:
    static uint8_t rxBuffer[];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;

    static uint8_t txAddress;
    static uint8_t txBuffer[];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;
	  static uint8_t modality;
	
    static uint8_t transmitting;
    static void (*user_onRequest)(void);
    static void (*user_onReceive)(int);
    static void (*user_onReceiveAdx)(void);
    static void (*user_onReceiveDataNack)(void);
    static void (*user_onReceiveData)(int);
    static uint8_t (*user_onRequestData)(void);
    static void (*user_onRequestDataNack)(void);

    static void onRequestService(void);
    static void onReceiveService(uint8_t*, int);
	  static void onReceiveDataService(uint8_t data);
    static void onReceiveDataNackService(void);
    static void onReceiveAdxService(void);
    static uint8_t onRequestDataService(void);
    static void onRequestDataNackService(void);

  public:
    TwoWire();
    void begin();
    void begin(uint8_t);
    void begin(int);
    void begin(uint8_t address, uint8_t mode);
    void begin(int address, int mode);
    void addressBitMask(uint8_t mask);
    void addressBitMask(int mask);
    void end();
    void setClock(uint32_t);
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission(void);
    uint8_t endTransmission(uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    uint8_t requestFrom(int, int, int);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    void onReceive( void (*)(int) );
    void onRequest( void (*)(void) );
    void onReceiveData( void (*function)(int) );
    void onReceiveDataNack( void (*function)(void) );
    void onReceiveAdx( void (*function)(void) );
    void onRequestData( uint8_t (*function)(void) );
    void onRequestDataNack( void (*function)(void) );

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;
};

extern TwoWire Wire;

#endif

