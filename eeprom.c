#include <xc.h>
#include "eeprom.h"

void configUART(){
     //----Config UART (serial port) ----
     BAUDCONbits.BRG16 = 0; //8 bits mode
     TXSTAbits.BRGH = 0; //Low speed
     TXSTAbits.SYNC = 0; //Asynchronous mode
     //Baudrate = Fosc/(64(spbrg + 1))
     //9615 = 8MHz/(64(12+1))
     SPBRG = 12; //Config baud-rate at 9600
     BAUDCONbits.TXCKP = 0; //Polarity NON inverted
     BAUDCONbits.RXDTP = 0;
     TXSTAbits.TX9 = 0; //Transmit 8 bits
     RCSTAbits.RX9 = 0; //Reception 8 bits
     TXSTAbits.TXEN = 1; //Enable transmision
     RCSTAbits.CREN = 1; //Enable reception
     RCSTAbits.SPEN = 1; //Enable serial port
     //-------------------------
}

void TXsend(char dato){
    while(TXSTAbits.TRMT == 0){
        //Wait until transmit register is available
    }
    TXREG = dato;
}

void TXstring(int length, char s[]){
    for(int i = 0; i < length; i++){
        TXsend(s[i]);
    }
}

void TXstringln(int length, char s[]){
    for(int i = 0; i < length; i++){
        TXsend(s[i]);
    }
    TXsend(10); //Line Feed
    TXsend(13); //CR
}

void TXnumber(int number){
     char units=0;
     char decs=0;
     char cents=0;
     char mils=0;
     units = number%10;
     decs = (number%100-units)/10;
     cents = (number%1000 - decs*10 - units)/100;
     mils = (number%10000 - cents*100 - decs*10 - units)/1000;
     if(number > 999){
          TXsend('0'+mils);
     }
     if(number > 99){
         TXsend('0'+cents);
     }
     if(number > 9){
          TXsend('0'+decs);
     }
     TXsend('0'+units);
}

void configInterrupts(){
     INTCONbits.GIE = 1; //Habilita interrupciones globles
     INTCONbits.PEIE = 1; //Habilita interrupciones periféricas
     PIR1bits.RCIF = 0; //baja la bandera RC
     PIE1bits.RCIE = 1; //Habilia la interrupción RC
     RCONbits.IPEN = 0; //No priorities
}

void readSerial(int size){
     contador = 0;
     while(contador < size){

     }
}

char leeEE(char direc){
   char lectura;
   EEADR = direc;
   EECON1bits.EEPGD = 0;
   EECON1bits.CFGS = 0;
   EECON1bits.RD = 1;
   lectura = EEDATA;
   return lectura;
}

int escribeEE(char direc, char escritura){
  int error = 0;
  EEADR = direc;
  EEDATA = escritura;
  EECON1bits.EEPGD = 0;
  EECON1bits.CFGS = 0;
  EECON1bits.WREN = 1;
  //<-- disable interrupts here
   EECON2 = 0x55;
   EECON2 = 0xAA;
   EECON1bits.WR = 1;
   //Enable Interrupts here
   while(PIR2bits.EEIF != 1){

   }
   PIR2bits.EEIF = 0;
   EECON1bits.WREN = 0;
   if(EECON1bits.WRERR==1){
      error = 1;
   }
   return error;
}
