#include <stdint.h>

#include "crash.h"

extern uint32_t _stext;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _scart;
extern uint32_t _ecart;

int main(void);

void I_Reset(void);
void I_MNI(void) __attribute__ ((weak, alias("I_Default")));
void I_HardFault(void) __attribute__ ((weak, alias("I_CrashHardFault")));
void I_Mem(void) __attribute__ ((weak, alias("I_CrashMem")));
void I_Bus(void) __attribute__ ((weak, alias("I_CrashBus")));
void I_Usage(void) __attribute__ ((weak, alias("I_CrashUsage")));

void I_SVCall(void) __attribute__ ((weak, alias("I_Default")));
void I_DebugMonitor(void) __attribute__ ((weak, alias("I_Default")));

void I_PendSV(void) __attribute__ ((weak, alias("I_Default")));
void I_SysTick(void) __attribute__ ((weak, alias("I_Default")));
void I_WWDG(void) __attribute__ ((weak, alias("I_Default")));
void I_PVD(void) __attribute__ ((weak, alias("I_Default")));
void I_TAMPER(void) __attribute__ ((weak, alias("I_Default")));
void I_RTC(void) __attribute__ ((weak, alias("I_Default")));
void I_FLASH(void) __attribute__ ((weak, alias("I_Default")));
void I_RCC(void) __attribute__ ((weak, alias("I_Default")));
void I_EXTI0(void) __attribute__ ((weak, alias("I_Default")));
void I_EXTI1(void) __attribute__ ((weak, alias("I_Default")));
void I_EXTI2(void) __attribute__ ((weak, alias("I_Default")));
void I_EXTI3(void) __attribute__ ((weak, alias("I_Default")));
void I_EXTI4(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA1_1(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA1_2(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA1_3(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA1_4(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA1_5(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA1_6(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA1_7(void) __attribute__ ((weak, alias("I_Default")));
void I_ADC1_2(void) __attribute__ ((weak, alias("I_Default")));
void I_USB_HP_CAN_TX(void) __attribute__ ((weak, alias("I_Default")));
void I_USB_LP_CAN_RX0(void) __attribute__ ((weak, alias("I_Default")));
void I_CAN_RX1(void) __attribute__ ((weak, alias("I_Default")));
void I_CAN_SCE(void) __attribute__ ((weak, alias("I_Default")));
void I_EXTI9_5(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM1_BRK(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM1_UP(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM1_TRG_COM(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM1_CC(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM2(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM3(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM4(void) __attribute__ ((weak, alias("I_Default")));
void I_I2C1_EV(void) __attribute__ ((weak, alias("I_Default")));
void I_I2C1_ER(void) __attribute__ ((weak, alias("I_Default")));
void I_I2C2_EV(void) __attribute__ ((weak, alias("I_Default")));
void I_I2C2_ER(void) __attribute__ ((weak, alias("I_Default")));
void I_SPI1(void) __attribute__ ((weak, alias("I_Default")));
void I_SPI2(void) __attribute__ ((weak, alias("I_Default")));
void I_USART1(void) __attribute__ ((weak, alias("I_Default")));
void I_USART2(void) __attribute__ ((weak, alias("I_Default")));
void I_USART3(void) __attribute__ ((weak, alias("I_Default")));
void I_EXTI15_10(void) __attribute__ ((weak, alias("I_Default")));
void I_RTCAlarm(void) __attribute__ ((weak, alias("I_Default")));
void I_USBWakeup(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM8_BRK(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM8_UP(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM8_TRG_COM(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM8_CC(void) __attribute__ ((weak, alias("I_Default")));
void I_ADC3(void) __attribute__ ((weak, alias("I_Default")));
void I_FSMC(void) __attribute__ ((weak, alias("I_Default")));
void I_SDIO(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM5(void) __attribute__ ((weak, alias("I_Default")));
void I_SPI3(void) __attribute__ ((weak, alias("I_Default")));
void I_USART4(void) __attribute__ ((weak, alias("I_Default")));
void I_USART5(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM6(void) __attribute__ ((weak, alias("I_Default")));
void I_TIM7(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA2_1(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA2_2(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA2_3(void) __attribute__ ((weak, alias("I_Default")));
void I_DMA2_4_5(void) __attribute__ ((weak, alias("I_Default")));

#define SRAM_START 0x20000000U
#define SRAM_SIZE  (20U * 1024U) //20kb
#define SRAM_END   ((SRAM_START) + (SRAM_SIZE))
#define SSTART     SRAM_END

uint32_t vectors[] __attribute__((section(".isr"))) = {
    SSTART,
    (uint32_t)&I_Reset,
    (uint32_t)&I_MNI,
    (uint32_t)&I_HardFault,
    (uint32_t)&I_Mem,
    (uint32_t)&I_Bus,
    (uint32_t)&I_Usage, 
    (uint32_t)0,
    (uint32_t)&I_SVCall,
    (uint32_t)&I_DebugMonitor,
    (uint32_t)0, 
    (uint32_t)&I_PendSV,
    (uint32_t)&I_SysTick,
    (uint32_t)&I_WWDG,
    (uint32_t)&I_PVD,
    (uint32_t)&I_TAMPER,
    (uint32_t)&I_RTC,
    (uint32_t)&I_FLASH,
    (uint32_t)&I_RCC,
    (uint32_t)&I_EXTI0,
    (uint32_t)&I_EXTI1,
    (uint32_t)&I_EXTI2,
    (uint32_t)&I_EXTI3,
    (uint32_t)&I_EXTI4,
    (uint32_t)&I_DMA1_1,
    (uint32_t)&I_DMA1_2,
    (uint32_t)&I_DMA1_3,
    (uint32_t)&I_DMA1_4,
    (uint32_t)&I_DMA1_5,
    (uint32_t)&I_DMA1_6,
    (uint32_t)&I_DMA1_7,
    (uint32_t)&I_ADC1_2,
    (uint32_t)&I_USB_HP_CAN_TX,
    (uint32_t)&I_USB_LP_CAN_RX0,
    (uint32_t)&I_CAN_RX1,
    (uint32_t)&I_CAN_SCE,
    (uint32_t)&I_EXTI9_5,
    (uint32_t)&I_TIM1_BRK,
    (uint32_t)&I_TIM1_UP,
    (uint32_t)&I_TIM1_TRG_COM,
    (uint32_t)&I_TIM1_CC,
    (uint32_t)&I_TIM2,
    (uint32_t)&I_TIM3,
    (uint32_t)&I_TIM4,
    (uint32_t)&I_I2C1_EV,
    (uint32_t)&I_I2C1_ER,
    (uint32_t)&I_I2C2_EV,
    (uint32_t)&I_I2C2_ER,
    (uint32_t)&I_SPI1,
    (uint32_t)&I_SPI2,
    (uint32_t)&I_USART1,
    (uint32_t)&I_USART2,
    (uint32_t)&I_USART3,
    (uint32_t)&I_EXTI15_10,
    (uint32_t)&I_RTCAlarm,
    (uint32_t)&I_USBWakeup,
    (uint32_t)&I_TIM8_BRK,
    (uint32_t)&I_TIM8_UP,
    (uint32_t)&I_TIM8_TRG_COM,
    (uint32_t)&I_TIM8_CC,
    (uint32_t)&I_ADC3,
    (uint32_t)&I_FSMC,
    (uint32_t)&I_SDIO,
    (uint32_t)&I_TIM5,
    (uint32_t)&I_SPI3,
    (uint32_t)&I_USART4,
    (uint32_t)&I_USART5,
    (uint32_t)&I_TIM6,
    (uint32_t)&I_TIM7,
    (uint32_t)&I_DMA2_1,
    (uint32_t)&I_DMA2_2,
    (uint32_t)&I_DMA2_3,
    (uint32_t)&I_DMA2_4_5
};

void I_Default(void){
    while(1){};
}

void I_Reset(void){
    uint32_t tstart = (uint32_t)&_stext;
    uint32_t tend = (uint32_t)&_etext;
    uint32_t dstart = (uint32_t)&_sdata;
    uint32_t dend = (uint32_t)&_edata;
    uint32_t bstart = (uint32_t)&_sbss;
    uint32_t bend = (uint32_t)&_ebss;
    uint32_t cstart = (uint32_t)&_scart;
    uint32_t cend = (uint32_t)&_ecart;
    uint32_t sz_data = &_edata - &_sdata;
    uint32_t sz_text = &_etext - &_stext;
    uint32_t sz_bss = &_ebss - &_sbss;
    uint32_t sz_cart = &_ecart - &_scart;

    uint32_t* bssDest = (uint32_t*)&_sbss;
    uint32_t* dataDest = (uint32_t*)&_sdata;
    uint32_t* dataSrc = (uint32_t*)&_ecart;
    uint32_t* cartDest = (uint32_t*)&_scart;
    uint32_t* cartSrc = (uint32_t*)&_etext;

    for(uint32_t i=0; i< sz_data; i++){
        *dataDest++ = *dataSrc++;
    }
    for(uint32_t i=0; i< sz_bss; i++){
        *bssDest++ = 0;
    }
    for(uint32_t i=0; i< sz_cart; i++){
        *cartDest++ = *cartSrc++;
    }

    crashInit(); 
    USART_str("\n.text :");
    USART_hex(tstart);
    USART_str(" :: ");
    USART_hex(tend);
    USART_str(" #");
    USART_hex(sz_text);

    USART_str("\n.data :");
    USART_hex(dstart);
    USART_str(" :: ");
    USART_hex(dend);
    USART_str(" #");
    USART_hex(sz_data);

    USART_str("\n.bss  :");
    USART_hex(bstart);
    USART_str(" :: ");
    USART_hex(bend);
    USART_str(" #");
    USART_hex(sz_bss);
    
    USART_str("\n.cart :");
    USART_hex(cstart);
    USART_str(" :: ");
    USART_hex(cend);
    USART_str(" #");
    USART_hex(sz_cart);
    USART_str("\n#\n");
    
    for(uint32_t i=0; i< 32; i+=4){
        USART_hex(0x20000000 + i);
        USART_str(" :: ");
        USART_hex(*((uint32_t*)(0x20000000+i)));
        USART_str("\n");
    }
    
    USART_str("\nram dump :\n");
    for(uint32_t i=0; i< 32; i+=4){
        USART_hex(0x20000800 + i);
        USART_str(" :: ");
        USART_hex(*((uint32_t*)(0x20000800+i)));
        USART_str("\n");
    }


    main();
}

void I_CrashHardFault(void){
    crashInit();
    USART_str("Crash: HardFault\n");

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
    crashBlink(1);
}

void I_CrashMem(void){
    crashInit();
    USART_str("Crash: MemFault\n");
    crashBlink(2); 
}

void I_CrashBus(void){
    crashInit();
    USART_str("Crash: BusFault\n");
    crashBlink(3);
}

void I_CrashUsage(void){
    crashInit();
    USART_str("Crash: UsageFault\n");
    crashBlink(4);
}
