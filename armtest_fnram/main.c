#include <stdint.h>
#include "crash.h"

const char* testString = "Hello";

void delay_us(uint32_t us) {
    us *= 3;

    /* fudge for function call overhead  */
    us--;
    asm volatile("   mov r0, %[us]          \n\t"
                 "1: subs r0, #1            \n\t"
                 "   bhi 1b                 \n\t"
                 :
                 : [us] "r" (us)
                 : "r0");
}


uint32_t v = 0x123abc;

__attribute__((section(".cart"))) 
void ramfn() {
    USART_str("[ Ramfs call() ]\n");
        *((uint32_t*)(GPIOB + 0xc)) = 0;
} 


int main(void){
    
    USART_str("\n\t##########Hello\n");
    USART_hex(v);
    USART_str("\n");
    USART_bin(v,32);
    USART_str("\n");
    while(1){
        USART_str("Toggle led\n");
        *((uint32_t*)(GPIOB + 0xc)) = (uint16_t)(1<<14);
        delay_us(200000);
        USART_str("Try call ramfs\n");
        ramfn();
        USART_str("Call ramfs done\n");
        delay_us(200000);
    }
	return 0;
}
