#include <stdint.h>

const char* testString = "Hello";

//#define RCC_BASE                        ((struct rcc_reg_map*)0x40021000)
/** GPIO port A register map base pointer */
//#define GPIOA_BASE                      ((struct gpio_reg_map*)0x40010800)

// /** STM32F1 RCC register map type */
// typedef struct rcc_reg_map {
//     volatile uint32_t CR;             /**< Clock control register */
//     volatile uint32_t CFGR;           /**< Clock configuration register */
//     volatile uint32_t CIR;            /**< Clock interrupt register */
//     volatile uint32_t APB2RSTR;       /**< APB2 peripheral reset register */
//     volatile uint32_t APB1RSTR;       /**< APB1 peripheral reset register */
//     volatile uint32_t AHBENR;         /**< AHB peripheral clock enable register */
//     volatile uint32_t APB2ENR;        /**< APB2 peripheral clock enable register */
//     volatile uint32_t APB1ENR;        /**< APB1 peripheral clock enable register */
//     volatile uint32_t BDCR;           /**< Backup domain control register */
//     volatile uint32_t CSR;            /**< Control/status register */
// } rcc_reg_map;

// /** GPIO register map type */
// typedef struct gpio_reg_map {
//     volatile uint32_t CRL;      /**< Port configuration register low */
//     volatile uint32_t CRH;      /**< Port configuration register high */
//     volatile uint32_t IDR;      /**< Port input data register */
//     volatile uint32_t ODR;      /**< Port output data register */
//     volatile uint32_t BSRR;     /**< Port bit set/reset register */
//     volatile uint32_t BRR;      /**< Port bit reset register */
//     volatile uint32_t LCKR;     /**< Port configuration lock register */
// } gpio_reg_map;


// /** GPIO port B register map base pointer */
// #define GPIOB_BASE                      ((struct gpio_reg_map*)0x40010C00)
// /** GPIO port C register map base pointer */
// #define GPIOC_BASE                      ((struct gpio_reg_map*)0x40011000)

// void init(){
//     //enable gpioA clock
// 	RCC_BASE->APB2ENR |= (uint32_t)(1<<2);
//     //reset gpioA device
// 	RCC_BASE->APB2RSTR |= (uint32_t)(1<<2);
//     //set gpioA:0 as PP output 10MHz
// 	GPIOA_BASE->CRL = (uint32_t)(0b0001);
// }

// void toggle(){
//     //toggle output bit 
// 	GPIOA_BASE->ODR ^= (uint16_t)(0x1);
// }

void delay_us(uint32_t us) {
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

// void delay(uint32_t count)
// {
//   for(uint32_t i = 0 ; i < count ; i++);
// }

uint32_t v = 0;

int main(void){
	// init();
	// while(1){
	// 	toggle();
	// 	delay_us(30000U);
	// };

    //RCC->APB2ENR = enable GPIOA port
    *((uint32_t*)(0x40021000 + 0x18)) = (uint32_t)(1<<3);
        
    //config gpioa 0 to be output PP
    *((uint32_t*)(0x40010C00 + 0x04)) = (uint32_t)(0x11000000);

    while(1){
        *((uint32_t*)(0x40010C00 + 0xc)) = v ? (uint16_t)(1<<15) : (uint16_t)(1<<14);
        delay_us(500000);
        v = !v;

        // for(uint32_t i=0; i<5; i++){ 
        //     delay_us(100000);
        //     *((uint32_t*)(0x40010800 + 0x10)) = i&0x3;
        // }
    }
	return 0;
}
