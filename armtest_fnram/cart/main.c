#include "../libnumcalcium.h"

void C_Reset(){

    USART_str("\nHello from cart :)\n");

    while(1){
        *((uint32_t*)(GPIOB + 0xc)) = (uint16_t)(1<<14);
        for(int i=0; i<200000; i++){}
        *((uint32_t*)(GPIOB + 0xc)) = 0;
        for(int i=0; i<200000; i++){}
    };
}
