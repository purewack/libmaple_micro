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

// void delay(uint32_t count)
// {
//   for(uint32_t i = 0 ; i < count ; i++);
// }
uint32_t v = 1;

__attribute__((section(".cart"))) 
void ramfn() {
    *((uint32_t*)(0x40010C00 + 0xc)) = 0;
} 


int main(void){
    
	// // init();
	// // while(1){
	// // 	toggle();
	// // 	delay_us(30000U);
	// // };

    //RCC->APB2ENR = enable GPIOA port
    *((uint32_t*)(RCC + 0x18)) = (uint32_t)(1<<3);
        
    //config gpioa 0 to be output PP
    *((uint32_t*)(GPIOB + 0x04)) = (uint32_t)(0x11000000);

    crashInit();
    USART_str("Hello\n");
    while(1){
        *((uint32_t*)(GPIOB + 0xc)) = (uint16_t)(1<<14);
        delay_us(200000);
        ramfn();
        delay_us(200000);
    }
	return 0;
}
