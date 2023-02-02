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

int main(void){

    USART_force_init();
    USART_str("\n[libnumcalcium cart loader]\n");
    USART_str("Waiting for cart size... :");
    
    uint32_t cart_size = 0;
    cart_size =  (uint32_t)USART_get_char();
    cart_size |= (uint32_t)USART_get_char()<<8;
    cart_size |= (uint32_t)USART_get_char()<<16;
    cart_size |= (uint32_t)USART_get_char()<<24;
    USART_hex(cart_size);

    char* data = (char*)0x20000000 + 4*1024;
    USART_start_dma_rx(cart_size+1,(uint32_t)data);
    USART_str("\nWaiting on data... :");
    while(USART_dma_head(cart_size+1) != cart_size) usleep(1);
    USART_end_dma_rx();

    USART_str("OK\n");
    USART_str("RX dump ::\n");
    for(int i=0; i<cart_size; i++){
        USART_hex(data[i]);
        USART_char('\n');
    }
    while(1);

	return 0;
}
