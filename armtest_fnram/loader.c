#include "libnumcalcium.h"

void post_libstatus(){
    USART_str("lib status: loaded\n");
}

void usleep(uint32_t us) {
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

unsigned char read[256];
volatile unsigned char tail = 0;
volatile unsigned char echo_start = 0;
unsigned char read2[256];

int main(void){

    USART_force_init();
    USART_str("\nlibnumcalcium loader echo DMA:\n");
    
    // for(int i=0; i<8; i++){
    //     read[i] = USART_get_char();
    // }
    USART_str("\nfrom [");
    USART_hex((uint32_t)read2);
    USART_str("]\n");
    USART_start_dma_rx(256,(uint32_t)read2);
    while(USART_dma_head(256) < 8) usleep(1000);
    USART_end_dma_rx();

    usleep(10000);

    USART_str("\nresults [");
    USART_hex(USART_dma_head(256));
    USART_str("] :\n");
    for(int i=0; i<USART_dma_head(256); i++){
        USART_hex(read2[i]);
        USART_str("\n");
    }
    USART_str("===\n");

    while(1){}    
    
    
    // while(1){
    //     int head = USART_dma_head(256);
    //     while(head != tail){
    //         if(read[tail] == '\n'){
    //             for(int i=echo_start; i<tail; i++){
    //                 USART_hex(read[i]);
    //                 USART_str("\n");
    //             }
    //             USART_str("]\n");
    //             echo_start = tail;
    //         }
    //         tail++;
    //     }
    // }
	return 0;
}
