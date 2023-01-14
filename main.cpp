// Sample main.cpp file. Blinks the built-in LED, sends a message out
// USART2, and turns on PWM on pin 2.

#include <wirish/wirish.h>
#include <libmaple/gpio.h>
#include <libmaple/delay.h>
#include <libmaple/usart.h>

void setup() {
    usart_init(USART1);
    usart_set_baud_rate(USART1,48000000,9600);
    usart_enable(USART1); 
    gpio_set_mode(GPIOA, 10, GPIO_INPUT_FLOATING);
    gpio_set_mode(GPIOA, 9, GPIO_AF_OUTPUT_PP);
	gpio_set_mode(GPIOA, 0, GPIO_OUTPUT_PP);
    
}

void loop() {
    delay_us(500000);
    usart_putstr(USART1,"Yo\r\n");
    gpio_toggle_bit(GPIOA,0);
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
