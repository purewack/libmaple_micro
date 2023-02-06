#include "libnumcalcium.h"
#include <string.h>


void post_hello(){
    USART_str("api: hello\n");
}
void post_hello2(){
    USART_str("api: hello2\n");
}
void post_libstatus(const char* msg){
    USART_str("lib status: loaded\n");
    USART_str(msg);
    USART_char('\n');
}
__attribute__((section(".api")))
void* api_getFunction(const char* fname){
    
    if(strcmp(fname,"post_hello") == 0)
        return (void*)post_hello;
    if(strcmp(fname,"post_hello2") == 0)
        return (void*)post_hello2;
    if(strcmp(fname,"post_libstatus") == 0)
        return (void*)post_libstatus;

    return (void*)0;
}

int main(void){

    USART_force_init();
    USART_str("\n[libnumcalcium cart loader]\n");
    USART_str("]\nWaiting for cart size... :");
    
    uint32_t cart_size = 0;
    cart_size =  (uint32_t)USART_get_char();
    cart_size |= (uint32_t)USART_get_char()<<8;
    cart_size |= (uint32_t)USART_get_char()<<16;
    cart_size |= (uint32_t)USART_get_char()<<24;
    USART_hex(cart_size);

    char* data = (char*)0x20001000;
    USART_start_dma_rx(cart_size+1,(uint32_t)data);
    USART_str("\nWaiting on data... :");
    while(USART_dma_head(cart_size+1) != cart_size) usleep_8MHz(1);
    USART_end_dma_rx();

    USART_str("\n Waiting on start byte (any)\n");
    USART_get_char();

    //start ram code
    ((void(*)(void))0x20001001)();

    while(1){}

	return 0;
}
