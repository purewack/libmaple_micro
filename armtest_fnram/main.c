#include <stdint.h>
#include "crash.h"
#include "common.h"

void cart_onbegin() CART_FUNC;
void cart_onbegin(){
    USART_str("[dummy cart_onbegin()]\n");
};

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

int main(void){
    
    USART_str("\n\t##########Hello\n");
    while(1){
        USART_str("Toggle led\n");
        *((uint32_t*)(GPIOB + 0xc)) = (uint16_t)(1<<14);
        delay_us(200000);
        cart_onbegin();
    }
	return 0;
}
