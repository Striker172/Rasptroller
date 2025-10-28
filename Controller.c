#include <stdio.h>
#include "pico/stdlib.h"
#include "mfrc522.h"
#include "Button.h"
volatile bool hasBalance = false;
volatile bool sendHIDReport = true;
MIFARE_Key key = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//This must have values whenever we scan the correct card on first try or something.
static Uid OwnersUID = {
    .uidByte = {},
    .sak = 1,
    .size =1 
}; 
/*
* A repeating timer interrupt that will be used to have the controller stop sending inputs 
* to the computer
*/
bool repeating_timer_callback(__unused struct repeating_timer *t){

}
int64_t alarm_callback(alarm_id_t id, __unused void *user_data){
    //This will be used to disable user input
    hasBalance = false;
    return 0;
}
/*
    * Makes the RFID card an owner card meaning the balance will be erased on the card.
    * @return True if the card was able to be made a owner, false if any errors accorded or the card
    * is already a owner
*/
bool makeOwnerCard(MFRC522Ptr_t mfrc522){
    //bool MIFARE_SetUid, 
    bool Errors = 0;
    // while(!PICC_IsNewCardPresent(mfrc522)); Assuming this has already been called before the command
    PICC_Select(mfrc522,&(mfrc522->uid),0);
    if(memcmp(&mfrc522->uid,&OwnersUID,sizeof(OwnersUID)) != 0){
        MIFARE_SetUid(mfrc522,OwnersUID.uidByte,OwnersUID.size,Errors);
    }
    return Errors;
}
/*
* Writes to the RFID card with a specific sector in mind, Assumes card is already selected when calling the function
* @return STATUS_OK if it was successful, if any other error accorded refer to the StatusCode enum within 
* the library's header file
*/
StatusCode writeToCard(MFRC522Ptr_t mfrc522,
    uint8_t blockAddr, ///<Block address equation = (Sector Num *4) +Block Offset
    char *message ///<Messsage to write to the sector
    ){
    if(blockAddr > 3 && blockAddr%4 != 3){
        StatusCode code = PCD_Authenticate(mfrc522,PICC_CMD_MF_AUTH_KEY_A,blockAddr,&key,&(mfrc522->uid));
        if(code == 0){
            code = MIFARE_Write(mfrc522,blockAddr,message,sizeof(message));
            if(code == 0){
                PCD_StopCrypto1(mfrc522);
            } 
        }
        return code;
    }
    return STATUS_SECT_OFF_LIMITS;
}
int main()
{
    stdio_init_all();
    struct repeating_timer timer;
    //We can either have a pulling HIDtask in the while loop or have an alarm trigger it. Either way we need one for the count for the limited fun.
    // add_repeating_timer_ms(10,repeating_timer_callback,NULL,&timer);
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
            //Block address equation = (Sector Num *4) +Block Offset
            writeToCard(mfrc522,0x04,message);
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
