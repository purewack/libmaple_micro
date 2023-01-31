#include "libnumcalcium.h"

void post_libstatus(){
    USART_str("lib status: loaded\n");
}

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

volatile unsigned char read[256];
volatile unsigned char r = 0;
volatile unsigned char ch = 0;

int main(void){
    
    USART_force_init();
    USART_str("\nlibnumcalcium loader echo:\n");
    r = 0;
    while(1){
        ch = (int)USART_get();
        read[r] = ch;
        r++;
        if(ch == '\n'){
            USART_str("[\n");
            for(int i=0; i<r; i++){
                USART_hex(read[i]);
                USART_str("\n");
                read[i] = 0;
            }
            USART_str("]\n");
            r = 0;
        }
    }
    // //load prog from usart into ram
    
    // for(int i=0; i<prog_bytes; i++){
    //     USART_hex(prog[i]);
    // }
    // while(1);
	return 0;
}
