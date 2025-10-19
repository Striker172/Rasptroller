#include <stdio.h>
#include "pico/stdlib.h"
#include "mfrc522.h"
#include "Button.h"

int main()
{
    stdio_init_all();
    uint8_t uid[] = {0x93,0xE3,0x9A,0x92}; //Dummy UID most likely.
    MFRC522Ptr_t mfrc522 = MFRC522_Init();
    PCD_Init(mfrc522,spi0);
    while(1){
        
        while(!PICC_IsNewCardPresent(mfrc522));//This will need to be changed to something else later on
        printf("Card detected!\n\r");
        PICC_ReadCardSerial(mfrc522);
        PICC_DumpToSerial(mfrc522,&(mfrc522->uid)); //This says uid, type of card and such. 
        //Authorization with uid
        // printf("Uid is: ");
        // for(int i = 0; i < 4; i++) {
        //     printf("%x ", mfrc522->uid.uidByte[i]);
        // } printf("\n\r");
        

    }
    return 0;
}
