// Sample main.cpp file. Blinks the built-in LED, sends a message out
// USART2, and turns on PWM on pin 2.

#include <wirish/wirish.h>
#include <libmaple/gpio.h>

void setup() {
    /* Set up the LED to blink  */
    pinMode(BOARD_LED_PIN, OUTPUT);

    /* Send a message out USART2  */
    Serial1.begin(9600);
    Serial1.println("Hello world!");
	
	gpio_set_mode(GPIOA,0,GPIO_OUTPUT_PP);
	gpio_set_mode(GPIOA,1,GPIO_OUTPUT_PP);
    gpio_toggle_bit(GPIOA,1);
}

void loop() {
    delay(500);
    Serial1.println("Yo");
    gpio_toggle_bit(GPIOA,0);
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
