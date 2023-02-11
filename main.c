#include "libnumcalcium.h"
// #include "libmaple/gpio.h"

int main(void){
    USART_force_init();
    usleep_8MHz(10000);
    USART_str("[libnumcalcium]\n");

    while(1){
        usleep_8MHz(200000);
        USART_str("[yo]\n");
    }
    
    // sideload_cart_USART();
    // int rcart = BEGIN_CART();
    // gpio_init(GPIOB);
    // gpio_set_mode(GPIOB,13,GPIO_OUTPUT_PP);

    // while(1){
    //     gpio_toggle_bit(GPIOB,13);
    //     usleep_8MHz(500000);
    // }

	return 0;
}
