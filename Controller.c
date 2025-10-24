#include <stdio.h>
#include "pico/stdlib.h"
#include "mfrc522.h"
#include "Button.h"
volatile bool hasBalance = false;
volatile bool sendHIDReport = true;
MIFARE_Key key = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
bool repeating_timer_callback(__unused struct repeating_timer *t){

}
int64_t alarm_callback(alarm_id_t id, __unused void *user_data){
    //This will be used to disable user input
    hasBalance = false;
    return 0;
}
int main()
{
    stdio_init_all();
    struct repeating_timer timer;
    //We can either have a pulling HIDtask in the while loop or have an alarm trigger it. Either way we need one for the count for the limited fun.
    add_repeating_timer_ms(10,repeating_timer_callback,NULL,&timer);
    uint8_t uid[] = {0x93,0xE3,0x9A,0x92}; //Dummy UID most likely.
    MFRC522Ptr_t mfrc522 = MFRC522_Init();
    PCD_Init(mfrc522,spi0);
    char *message = "Hi,There";
    while(1){
        if(!hasBalance){
            while(!PICC_IsNewCardPresent(mfrc522));//This will need to be changed to something else later on
            printf("Card detected!\n\r");
            PICC_ReadCardSerial(mfrc522);
            PICC_DumpToSerial(mfrc522,&(mfrc522->uid)); //This says uid, type of card and such. 
            PCD_Authenticate(mfrc522,PICC_CMD_MF_AUTH_KEY_A,0x06,&key,&(mfrc522->uid));
            MIFARE_Write(mfrc522,0x06,message,sizeof(message));
            PCD_StopCrypto1(mfrc522);
        }
        /* This should how the setup should go for the timer
        Read the actual balance on the RFID card read the flag whether it should remove the balance or not, 
        implement something with the UID and or format. After dealing with the RFID 
        Set the duration of the timer to how much balance is on the card and set a flag to TRUE. Once time is up the alarm sets 
        the boolean statement to false and continues to try and read the card. 
        
        */

    }
    return 0;
}
