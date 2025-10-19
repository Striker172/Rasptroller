#include "Button.h"
Button buttons[ButCount] = {0};
void gpio_callback(uint gpio, uint32_t events){
    
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