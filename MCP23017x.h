/* 
 * File:   MCP23017x.h
 * Author: alany
 *
 * Created on November 8, 2023, 5:55 PM
 * 16-Bit I/O Expander with Serial Interface
 * High-Speed I2C Interface (MCP23017):
    - 100 kHz
    - 400 kHz
    - 1.7 MHz
 *  High-Speed SPI Interface (MCP23S17):
    - 10 MHz (maximum)
 * x
 */

#ifndef MCP23017X_H
#define	MCP23017X_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "i2c1.h"
   
//Registros del IC
/*iocon.bank = 0 */
#define addr1 0x40 //0b01000000
#define IODIRA 0x0   //Controls the direction of data I/O <
#define IODIRB 0x01
#define IPOLA 0x02   // Controls the polarity inversion of the input pins
#define IPOLB 0x03
#define GPINTENA 0x04 // General purpose I/O interrupt-on-change bits
#define GPINTENB 0x05
#define DEFVELA 0x06 // Sets the compare value for pins configured for interrupt-on-change from defaults
#define DEFVELB 0x07
#define INTCONA 0x08 // Controls how the associated pin value is compared for interrupt-on-change
#define INTCONB 0x09
#define IOCON   0x0A
#define IOCON_  0x0B
#define GPPUA 0x0C
#define GPPUB 0x0D
#define INTFA 0x0E
#define INTFB 0x0F
#define INTCAPA 0x10
#define INTCAPB 0x11
#define GPIOA 0x12
#define GPIOB 0x13
#define OLATA 0x14
#define OLATB 0x15
#define SEQOP 0x20 //bit set. // Sequential Operation mode bit
//Puertos
#define portA 0
#define portB 1
//Utilidades
#define all_input  0xFF;
#define all_output 0x00;
#define on 1
#define off 0


    void ioexpander_writeByte(uint8_t address, uint8_t reg,  uint8_t *data , uint8_t length);
    
    uint8_t ioexpander_readByte(uint8_t address);
    
    void ioexpander_pullup(uint8_t address, uint8_t pin, uint8_t port);
    
    void ioexpander_configPort(uint8_t address, uint8_t port, uint8_t Low_High);
    
    void ioexpander_Seq(uint8_t address, uint8_t on_off);

#ifdef	__cplusplus

#endif

#endif	/* MCP23017_H */

