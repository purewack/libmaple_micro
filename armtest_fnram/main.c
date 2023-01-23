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
uint32_t vv = 0xbeef;
uint32_t bb;

void ramfn() __attribute__ ((section (".cart")));
void ramfn2() __attribute__ ((section (".cart")));

uint8_t ramvv __attribute__ ((section (".cbss"))) ; 
uint8_t ramvdata __attribute__ ((section (".cdata"))) = 42; 

void ramfn() {
    USART_str(" ramfn() \n");
        *((uint32_t*)(GPIOB + 0xc)) = 0;
    bb = vv;
    ramvv = bb;
}

void ramfn2() {
    USART_str(" ramfn2() {\n");
    USART_hex(vv);
    USART_str("\n ramvv: ");
    USART_hex(ramvv);
    USART_str("\n");
    vv++;
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
        ramfn();
        ramfn2();
        delay_us(200000);
    }
	return 0;
}
