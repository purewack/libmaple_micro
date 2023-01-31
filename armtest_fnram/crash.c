#include "libnumcalcium.h"


void crashBlink(int blink_count){
    while(1){
        for(int j=0; j<blink_count; j++){
            *((uint32_t*)(GPIOB + 0xc)) = (uint16_t)(1<<15);
            for(int i=0; i<20000; i++){}
            *((uint32_t*)(GPIOB + 0xc)) = 0;
            for(int i=0; i<20000; i++){}
        }
        for(int i=0; i<1000000; i++){}
    }
}

void USART_crash_registers(){
    USART_str("\nSYSHND_CTRL\n");
    USART_hex(SYSHND_CTRL);

    USART_str("\nNVIC_MFSR\n");
    USART_hex(NVIC_MFSR);

    USART_str("\nNVIC_BFSR\n");
    USART_hex(NVIC_BFSR);

    USART_str("\nNVIC_UFSR\n");
    USART_hex(NVIC_UFSR);
    
    USART_str("\nNVIC_HFSR\n");
    USART_hex(NVIC_HFSR);

    USART_str("\nNVIC_DFSR\n");
    USART_hex(NVIC_DFSR);

    USART_str("\nNVIC_BFAR\n");
    USART_hex(NVIC_BFAR);

    USART_str("\nNVIC_AFSR\n");
    USART_hex(NVIC_AFSR);
}


void USART_force_init(){
    //RCC->APB2ENR = enable GPIOA + GPIOB ports + AFIO + USART1
    *((uint32_t*)(RCC + 0x18)) = (uint32_t)(1<<14) | (uint32_t)(0b1101);
    
    //GPIOA:10 RX INPUT
    //GPIOA:9 TX ALT_OUTPUT_PP
    *((uint32_t*)(GPIOA + 0x04)) = (uint32_t)(0x444444b4);
    //GPIOB:15 output PP
    *((uint32_t*)(GPIOB + 0x04)) = (uint32_t)(0x11444444);

    //usart1 config
    //tx rx enable, 8n1, enable usart
    *((uint32_t*)(USART1 + 0x0C)) = (uint16_t)((1<<1) | (1<<2) | (1<<3));
    *((uint32_t*)(USART1 + 0x0C)) |= (uint16_t)(1<<13);

    /* Convert desired baud rate to baud rate register setting. */
    uint32_t baud = 112500;
    uint32_t clock_speed = 8000000;
    uint32_t integer_part = (25 * clock_speed) / (4 * baud);
    uint32_t tmp = (integer_part / 100) << 4;
    uint32_t fractional_part = integer_part - (100 * (tmp >> 4));
    tmp |= (((fractional_part * 16) + 50) / 100) & ((uint8_t)0x0F);
    *((uint32_t*)(USART1 + 0x08)) = (uint16_t)tmp;
}

void USART_char(char c){
    //put char to tx buf
    *((uint32_t*)(USART1 + 0x04)) = (uint8_t)(c);
    //wait until transferred
    while( ! (*((uint32_t*)(USART1 + 0x00)) &= (1<<7)) ){}
}
void USART_str(const char* str){
    while(*str != 0){
        USART_char(*str++);
    }
}
void USART_bin(uint32_t val, uint8_t bits){
    USART_str("0b");
    for(uint8_t i=0; i<bits; i++){
        char c = ( val & (1<<(bits-i-1)) ? '1' : '0');
        USART_char(c);
    }
}
void USART_hex(uint32_t val){
    int nibs = 32/4;
    USART_str("0x");
    for(int i=0; i<nibs; i++){
        int sh = 4*(8-1-i);
        int nib = (val & (0xf<<sh)) >> sh;
        char c = (nib < 0xa) ? '0'+nib : 'A'+nib-0xa;
        USART_char(c);
    }
}

uint32_t USART_rx(){
    return (*((uint32_t*)(USART1 + 0x00)) & (1<<5));
}
unsigned char USART_read(){
    return (uint8_t)*((uint32_t*)(USART1 + 0x04));
}
unsigned char USART_get(){
    while(USART_rx() == 0){}
    return USART_read();
}