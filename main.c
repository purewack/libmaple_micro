#include <libnumcalcium.h>
#include <libmaple/gpio.h>
#include <libmaple/usart.h>

int main(void){
    usart_init(USART1);
    usart_set_baud_rate(USART1,8000000,115200);
    usart_enable(USART1);

    afio_init();
    //GPIOA:10 RX INPUT
    //GPIOA:9 TX ALT_OUTPUT_PP
    gpio_init(GPIOA);
    gpio_set_mode(GPIOA,9,GPIO_AF_OUTPUT_PP);
    gpio_set_mode(GPIOA,10,GPIO_INPUT_FLOATING);

    gpio_init(GPIOB);
    gpio_set_mode(GPIOB,13,GPIO_OUTPUT_PP);

    while(1){
        usart_putstr(USART1,"[maple]\n");
        gpio_toggle_bit(GPIOB,13);
        usleep_8MHz(500000);
    }

	return 0;
}
