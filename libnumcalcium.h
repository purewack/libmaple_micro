#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>


#define S_BIT(n,b) n |= (1<<(b))
#define C_BIT(n,b) n &= ~(1<<(b))

/*********************************************************************
*
* Defines
*
**********************************************************************
*/
// System Handler Control and State Register
#define SYSHND_CTRL (*(volatile unsigned int*) (0xE000ED24u))
// Memory Management Fault Status Register
#define NVIC_MFSR (*(volatile unsigned char*) (0xE000ED28u))
// Bus Fault Status Register
#define NVIC_BFSR (*(volatile unsigned char*) (0xE000ED29u))
// Usage Fault Status Register
#define NVIC_UFSR (*(volatile unsigned short*)(0xE000ED2Au))
// Hard Fault Status Register
#define NVIC_HFSR (*(volatile unsigned int*) (0xE000ED2Cu))
// Debug Fault Status Register
#define NVIC_DFSR (*(volatile unsigned int*) (0xE000ED30u))
// Bus Fault Manage Address Register
#define NVIC_BFAR (*(volatile unsigned int*) (0xE000ED38u))
// Auxiliary Fault Status Register
#define NVIC_AFSR (*(volatile unsigned int*) (0xE000ED3Cu))

#define RCC     0x40021000
#define GPIOA   0x40010800
#define GPIOB   0x40010C00
#define USART1  0x40013800
#define DMA1    0x40020000

//blocking blink function triggered on fault
void crashBlink(int blink_count);
//init usart for posting error messages on fault
void crashInit();
//post register contents relating to crash
void USART_crash_registers();

void USART_force_init();
void USART_char(char c);
void USART_str(const char* str);
void USART_bin(uint32_t val, uint8_t bits);
void USART_hex(uint32_t val);
unsigned char USART_read();
unsigned char USART_get_char();
void USART_start_dma_rx(unsigned int len, unsigned int dest);
void USART_end_dma_rx();
int USART_dma_head(int size);

void usleep_8MHz(uint32_t us);

#define F_NM_API_GETTER (0x08000124 | 1)
#define GET_API_FUNC_POINTER(X) ((void* (*)(const char*))F_NM_API_GETTER)(#X)

#endif