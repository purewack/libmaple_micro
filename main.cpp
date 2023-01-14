// Sample main.cpp file. Blinks the built-in LED, sends a message out
// USART2, and turns on PWM on pin 2.
#include <libmaple/libmaple.h>
#include <libmaple/stm32.h>
#include <libmaple/libmaple_types.h>
#include <libmaple/flash.h>
#include <libmaple/nvic.h>
#include <libmaple/systick.h>
#include <libmaple/gpio.h>
#include <libmaple/delay.h>
#include <libmaple/usart.h>

int main(void) {
      // Turn on as many Flash "go faster" features as
    // possible. flash_enable_features() just ignores any flags it
    // can't support.
    flash_enable_features(FLASH_PREFETCH | FLASH_ICACHE | FLASH_DCACHE);
    // FLASH_SAFE_WAIT_STATES is a hack that needs to go away.
    flash_set_latency(FLASH_SAFE_WAIT_STATES);

     // Turn on HSI. We'll switch to and run off of this while we're
    // setting up the main PLL.
    rcc_turn_on_clk(RCC_CLK_HSI);

    // Turn off and reset the clock subsystems we'll be using, as well
    // as the clock security subsystem (CSS). Note that resetting CFGR
    // to its default value of 0 implies a switch to HSI for SYSCLK.
    RCC_BASE->CFGR = 0x00000000;
    rcc_disable_css();
    rcc_turn_off_clk(RCC_CLK_PLL);
    rcc_turn_off_clk(RCC_CLK_HSE);
    // Clear clock readiness interrupt flags and turn off clock
    // readiness interrupts.
    RCC_BASE->CIR = 0x00000000;

    // Enable the PLL input clock, and wait until it's ready.
    rcc_turn_on_clk(RCC_CLK_HSI);
    while (!rcc_is_clk_ready(RCC_CLK_HSI)){};

    rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1);
    rcc_set_prescaler(RCC_PRESCALER_APB1, RCC_APB1_HCLK_DIV_2);
    rcc_set_prescaler(RCC_PRESCALER_APB2, RCC_APB2_HCLK_DIV_1);

    static stm32f1_rcc_pll_data pll_data = {RCC_PLLMUL_12};
    rcc_pll_cfg w_board_pll_cfg = {RCC_PLLSRC_HSI_DIV_2, &pll_data};
    rcc_configure_pll(&w_board_pll_cfg);

    // Enable the PLL, and wait until it's ready.
    rcc_turn_on_clk(RCC_CLK_PLL);
    while(!rcc_is_clk_ready(RCC_CLK_PLL)){}

    // Finally, switch to the now-ready PLL as the main clock source.
    rcc_switch_sysclk(RCC_CLKSRC_PLL);
    nvic_init((uint32)0x08000000, 0);

    usart_init(USART1);
    usart_set_baud_rate(USART1,48000000,9600);
    usart_enable(USART1); 
    gpio_set_mode(GPIOA, 10, GPIO_INPUT_FLOATING);
    gpio_set_mode(GPIOA, 9, GPIO_AF_OUTPUT_PP);
	gpio_set_mode(GPIOA, 0, GPIO_OUTPUT_PP);

    while (true) {
        delay_us(500000);
        usart_putstr(USART1,"Yo\r\n");
        gpio_toggle_bit(GPIOA,0);
    }

    return 0;
}
