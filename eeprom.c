#include <xc.h>
#include "configs.h"
#include "EmbeddedFunctions.h"

void show_trys(char count);

void main(void) {
    OSCCON = 0x72;
    configUART();
    char count;
    if(leeEE(200)==0x55){
        count = leeEE(201);
        show_trys(count);
        if(count != 0){
            count--;
            escribeEE(201,count);
        }
    }else{
        escribeEE(200,0x55);
        show_trys(5);
        escribeEE(201,4);
    }
    while(1){};
    return;
}

void show_trys(char count){
    if(count == 0){
       TXstringln(18,"Intentos agotados ");
       TXstringln(21,"Purchase FULL Version");
    }else{
        if(count != 1){
            TXstringln(23,"This is a DEMO Version ");
            TXsend('0'+count);
            TXstringln(11," trys left ");
        }else{
            TXstringln(23,"This is a DEMO Version ");
            TXsend('0'+count);
            TXstringln(11," try left ");
        }
    }
}
