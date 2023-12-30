#include "system.h"
#include "i2c1.h"

void I2C1_Init(uint16_t fscl)
{
    float delay  = 0.00000012;  //120ns delay
    float i2cbrg = (((1/fscl)-delay)*FCY)-2;
    I2C1BRG = i2cbrg;
    I2C1CONbits.I2CEN = 1; 
    
    //interrupciones
    IPC4bits.MI2C1IP = 1; //interruption priority control
    IFS1bits.MI2C1IF = 1; //interruption flag status
    IEC1bits.MI2C1IE = 1;//interruption enable control
}

void I2C1_Start(void)
{
    I2C1CONbits.SEN = 1;
    while(I2C1CONbits.SEN == 1);  //espera a que finalice la condicion de start
}
void I2C1_Restart(void)
{
    I2C1CONbits.RSEN = 1;
    while(I2C1CONbits.RSEN == 1);
}
void I2C1_Stop(void)
{
    I2C1CONbits.PEN = 1;
    while(I2C1CONbits.PEN == 1);
}
void I2C1_Write_Addr_Slave(uint8_t addr, uint8_t dir)
{
    I2C1TRN = (addr & 0b11111110) | (dir & 0b00000001);
    while(I2C1STATbits.TRSTAT);  //esperamos a que finalice la transmision del master
}
void I2C1_write(uint8_t data)
{
    I2C1TRN = data;
    while(I2C1STATbits.TRSTAT);  //esperamos a que finalice la transmision del master
}

void I2CIdle() {
    while (I2C1STATbits.TRSTAT); //esperar a recibir  ACK
}

uint8_t ACKStatus() {
    return (!I2C1STATbits.ACKSTAT); //retornar  ACK
}

uint8_t I2C_rx() {

    I2C1CONbits.RCEN = 1; //habilita rx
    //Nop();
    while (!I2C1STATbits.RBF); // esperar se envie dato
    return (I2C1RCV);

}

void NotACKi2c() {
    I2C1CONbits.ACKDT = 1; //1 = Send NACK during Acknowledge
    I2C1CONbits.ACKEN = 1;
    while (I2C1CONbits.ACKEN);
}
