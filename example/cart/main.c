#include "libnumcalcium.h"

int C_Reset(){
    USART_str("\nHello from cart :)\n");

    void(*sys_dummy)(void) = LOAD_SFP(sys_dummy);
    if(sys_dummy) (*sys_dummy)();
    else return -1;

    while(1){
        *((uint32_t*)(GPIOB + 0xc)) = (uint16_t)(1<<14);
        for(int i=0; i<200000; i++){}
        *((uint32_t*)(GPIOB + 0xc)) = 0;
        for(int i=0; i<200000; i++){}
    };
    return 0;
}
