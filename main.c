#include "system.h"
#include "i2c1.h"
#include "MCP23017x.h"
#include <libpic30.h>
#include <p33FJ32MC202.h>

uint8_t data[1] = {0x00}; //{SEQUENCE000=s 01000000B 0h 0d P},{SEQUENCE001=s 01000000B 12h 1d P}
uint8_t data1[1] = {0x80};
uint8_t all[1]={0xff};
uint8_t a;



int main()
{
    TRISBbits.TRISB15 = 0;
    
 
    I2C1_Init(100);
    ioexpander_writeByte(addr1,IODIRA,0x00,1);//Config para puerto A como salida
    __delay_ms(2);
    ioexpander_writeByte(addr1,IODIRB,all,1);//Config para puerto B como entradas
   __delay_ms(2);
   
    while(1)
    {

        ioexpander_writeByte(addr1,GPIOA,data1,1);//encendido de led en portA
        __delay_ms(1000);
        ioexpander_writeByte(addr1,GPIOA,data,1);//apagado de led en portA
        __delay_ms(1000);
        
        a = ioexpander_readByte(addr1);// leer todo el  puertoB 
        if (a>0)
            LATBbits.LATB15 = !LATBbits.LATB15;
       
        
        
    }
    return 0;
}
