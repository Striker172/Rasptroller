#include "Button.h"
Button buttons[ButCount] = {0};
void gpio_callback(uint gpio, uint32_t events){
    uint64_t currTime = time_us_64();
    int index = gpio-PIN_GROUP_START;
    if(index < 0 || index >= ButCount) {
        return;
    }
    if((currTime-buttons[index].press_timestampprev) > ButDebounce*1000){
            buttons[index].press_timestampprev = currTime;
        switch(events){
            case GPIO_IRQ_EDGE_RISE:
                buttons[index].press_timestamp = currTime;
            break;
            case GPIO_IRQ_EDGE_FALL:
                if((currTime-buttons[index].press_timestamp) < timeAllowed*1000){
                    buttons[index].isPressed = true;
                }
            break;
            default: //This assumes error so idk change later
            return; 
            break;
        }
    } 
}
void resetButton(ButtonID button){
    if(button < ButCount){
        buttons[button].isPressed = false;
    }
}
int setup(){
    //Timers may need to be implemented for double click, and long.
    for(int gpio = 0; gpio < ButCount;gpio++){
        buttons[gpio].id = gpio+PIN_GROUP_START;
        buttons[gpio].isPressed = false;
        buttons[gpio].press_timestamp = 0;
        buttons[gpio].press_timestampprev = 0;
        gpio_init(buttons[gpio].id);
        gpio_set_dir(buttons[gpio].id,GPIO_IN);
        gpio_pull_down(buttons[gpio].id);
        gpio_set_irq_enabled_with_callback(buttons[gpio].id,GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,true,&gpio_callback);
    }
}