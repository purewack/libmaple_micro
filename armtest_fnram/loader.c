#include "libnumcalcium.h"

void post_libstatus(const char* msg){
    USART_str("lib status: loaded\n");
    USART_str(msg);
    USART_char('\n');
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

extern uint32_t _sctext;

int main(void){


    USART_force_init();
    USART_str("\n[libnumcalcium cart loader]\n");
    USART_str("\n[using cart start @");
    USART_hex((uint32_t)&_sctext);
    USART_str("]\nWaiting for cart size... :");
    
    uint32_t cart_size = 0;
    cart_size =  (uint32_t)USART_get_char();
    cart_size |= (uint32_t)USART_get_char()<<8;
    cart_size |= (uint32_t)USART_get_char()<<16;
    cart_size |= (uint32_t)USART_get_char()<<24;
    USART_hex(cart_size);

    char* data = (char*)&_sctext;
    USART_start_dma_rx(cart_size+1,(uint32_t)data);
    USART_str("\nWaiting on data... :");
    while(USART_dma_head(cart_size+1) != cart_size) usleep(1);
    USART_end_dma_rx();

    // USART_str("OK...Data dump:\n");
    // for(int i=0; i<cart_size; i++){
    //     USART_hex(data[i]);
    //     USART_char('\n');
    // }

    USART_str("\n Waiting on start byte (any)\n");
    USART_get_char();
    
    // USART_str("Exec. C_Reset @");
    // USART_hex((uint32_t)C_Reset_Loader);
    // USART_str("\n");
    // C_Reset_Loader();

    void(*cloader)(void) = (void*)((uint32_t)&_sctext | 1);
    (*cloader)();
    

    while(1);

	return 0;
}
