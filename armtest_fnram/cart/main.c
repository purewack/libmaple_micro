#include "../libnumcalcium.h"

void C_Reset(){

    USART_str("\nHello from cart :)\n");

    void*(*getFunc)(const char*, int) = (void*)((uint32_t)0x08000124 | 1);
    
    USART_str("getting fpointer from api\n");
    void(*f_post_hello)(void) = (*getFunc)("post_hello3", 0);
    USART_str("fpointer\n");
    USART_hex((uint32_t)f_post_hello);
    USART_str("\n");
    
    if(f_post_hello){
        USART_str("calling fpointer from api\n");
        (*f_post_hello)();
    }
    else
        USART_str("no api function found for name :(\n");

    while(1){
        *((uint32_t*)(GPIOB + 0xc)) = (uint16_t)(1<<14);
        for(int i=0; i<200000; i++){}
        *((uint32_t*)(GPIOB + 0xc)) = 0;
        for(int i=0; i<200000; i++){}
    };
}
