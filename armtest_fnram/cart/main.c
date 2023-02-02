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

    while(1){
        *((uint32_t*)(GPIOB + 0xc)) = (uint16_t)(1<<14);
        usleep(100000);
        *((uint32_t*)(GPIOB + 0xc)) = 0;
        usleep(100000);
    };
}
