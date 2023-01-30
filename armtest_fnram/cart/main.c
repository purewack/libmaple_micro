#include "../libnumcalcium.h"

void C_Reset(){
    uint32_t sz_text = &_etext - &_stext;
    uint32_t sz_data = &_edata - &_sdata;
    uint32_t sz_bss  = &_ebss  - &_sbss;
    uint32_t* dataSrc   = (uint32_t*)sz_text;
    uint32_t* dataDest  = (uint32_t*)&_sdata;
    uint32_t* bssDest   = (uint32_t*)&_sbss;

    for(uint32_t i=0; i< sz_data; i++){
        *dataDest++ = *dataSrc++;
    }
    for(uint32_t i=0; i< sz_bss; i++){
        *bssDest++ = 0;
    }

    USART_force_init();
    USART_str("hello from cart\n");
    while(1){};
}
