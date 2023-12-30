
#include "MCP23017x.h"
#include "i2c1.h"
#include <stdint.h>
#include <stdio.h>

/*
 * 
 I2C como master
 * 
 */
void ioexpander_writeByte(uint8_t address, uint8_t reg, uint8_t *data, uint8_t length) {
    I2C1_Start();
    I2C1_Write_Addr_Slave(address, I2C_Write); //addr
    I2CIdle();
    I2C1_write(reg);
    I2CIdle();

    for (uint8_t i = 0; i < length; i++) {
        I2C1_write(data[i]);
        I2CIdle();
    }

    I2C1_Stop();
}

uint8_t ioexpander_readByte(uint8_t address) {
    uint8_t data_rx;

    I2C1_Start();
    I2C1_Write_Addr_Slave(address, I2C_Read); //addr
    I2CIdle();
    //    I2C1_write(port);
    //    I2CIdle();
    data_rx = I2C_rx();
    NotACKi2c();
    I2C1_Stop();

    return data_rx;
}

void ioexpander_configPort(uint8_t address, uint8_t port, uint8_t Low_High) {
    I2C1_Start();
    I2C1_Write_Addr_Slave(address, I2C_Write); //addr
    I2CIdle();
    if (port == GPIOA) {
        I2C1_write(GPIOA); //puerto A pull up resistor
        I2CIdle();
    } else {
        I2C1_write(GPIOB); //puerto B pull up resistor
        I2CIdle();
    }
    I2C1_write(Low_High); //salida o entrada
    I2CIdle();
    I2C1_Stop();
}

void ioexpander_pullup(uint8_t address, uint8_t pin, uint8_t port) {
    I2C1_Start();
    I2C1_Write_Addr_Slave(address, I2C_Write); //addr
    I2CIdle();
    if (port == GPIOA) {
        I2C1_write(GPPUA); //puerto A pull up resistor
        I2CIdle();
    } else {
        I2C1_write(GPPUB); //puerto B pull up resistor
        I2CIdle();
    }
    I2C1_write(pin); //salida digital
    I2CIdle();
    I2C1_Stop();
}

void ioexpander_Seq(uint8_t address, uint8_t on_off) {
    I2C1_Start();
    I2C1_Write_Addr_Slave(address, I2C_Write); //addr
    I2CIdle();
    I2C1_write(IOCON_); //salida digital
    I2CIdle();
        I2CIdle();
    if (on_off == 1) {
        I2C1_write(SEQOP); //bit5 set
        I2CIdle();
    }
    else
    {
        I2C1_write(0x00); //bit5 clear
        I2CIdle();
    }

    I2C1_Stop();
}

