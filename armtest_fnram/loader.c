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

volatile char read[256];
volatile int r = 0;

int main(void){
    
    USART_force_init();
    USART_str("\nlibnumcalcium loader echo:\n");
    while(1){
        if(read[r] == '\n'){
            USART_str(read);
            r = 0;
        }
        else
            read[r++] = USART_get();
    }
    // //load prog from usart into ram
    
    // for(int i=0; i<prog_bytes; i++){
    //     USART_hex(prog[i]);
    // }
    // while(1);
	return 0;
}
