#include "libnumcalcium.h"

void blink_one(){
    *((uint32_t*)(GPIOB + 0xc)) = (uint16_t)(1<<14);
    usleep_8MHz(100000);
    *((uint32_t*)(GPIOB + 0xc)) = 0;
    usleep_8MHz(100000);
}

CART_MAIN int C_Reset(){
    USART_str("\nHello from cart :)\n");

    void(*sys_dummy)(void) = LOAD_SFP(sys_dummy);
    if(sys_dummy) (*sys_dummy)();
    else return -1;

    while(1){
        blink_one();
        USART_str("blink :o\n");
        usleep_8MHz(500000);
    };
    return 0;
}
