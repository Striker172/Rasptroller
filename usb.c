#include "Button.h"
#include "usb_descriptors.h"
#include "tusb.h"
static void send_hid_report(uint8_t report_id,uint32_t btn){
    if(!tud_hid_ready()){
        return;
    }
    switch(report_id){
         case REPORT_ID_GAMEPAD:
             hid_gamepad_report_t report = {
                .hat = 0, .buttons = 0
             }; 
            if(btn){
                
            }
    }
}