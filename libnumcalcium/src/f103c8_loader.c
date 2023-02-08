#include "libnumcalcium.h"
#include <string.h>

void sys_dummy(){
    USART_str("[system] hello\n");
}

__attribute__((section(".system")))
void* sys_getFunction(const char* fname){
    
    if(strcmp(fname,"sys_dummy") == 0)
        return (void*)sys_dummy;

    return (void*)0;
}

__attribute__((section(".loader")))
int sideload_cart_USART(){
    const uint8_t ack_byte = 0xAC;
    USART_force_init();

    //Little endian
    uint16_t cart_size = 0;
    cart_size = (uint16_t)USART_get_char();
    cart_size = ((uint16_t)USART_get_char()<<8) | cart_size;
    USART_char(ack_byte);

    char* dest = (char*)0x20001000;
    USART_start_dma_rx(cart_size+1,(uint32_t)dest);
    while(USART_dma_head(cart_size+1) != cart_size) usleep_8MHz(1);
    USART_end_dma_rx();
    USART_char(ack_byte);
    usleep_8MHz(100000);
    
    dest = (char*)0x20001000;
    for(int i=0; i<cart_size; i++){
        USART_char(*dest++);
    }
    usleep_8MHz(100000);
    return 0;
}
