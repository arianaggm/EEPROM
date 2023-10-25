#ifndef eeprom_h
#define	eeprom_h

int contador;

char leeEE(char direc);
int escribeEE(char direc, char escritura);
void configUART(void);
void TXsend(char dato);
void TXstringln(int length, char s[]);
void TXnumber(int number);
void TXln(void);
void configInterrupts(void);
void readSerial(int size);

#endif	/* XC_HEADER_TEMPLATE_H */
