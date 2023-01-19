#ifndef CRASH_HEADER
#define CRASH_HEADER

#include <stdint.h>

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

void USART_char(char c);
void USART_str(const char* str);
void USART_bin(uint32_t val, uint8_t bits);
void USART_hex(uint32_t val);

void crashBlink(int iter);
void crashInit();

#endif