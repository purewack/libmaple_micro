#include <libnumcalcium.h>
#include <libmaple/gpio.h>
#include <libmaple/usart.h>
#include <libmaple/adc.h>
#include <libmaple/i2c.h>

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
    gpio_set_mode(GPIOB,6,GPIO_OUTPUT_PP);
    gpio_set_mode(GPIOB,7,GPIO_OUTPUT_PP);

    
    adc_init(ADC1);
    adc_enable(ADC1);
    adc_enable_single_swstart(ADC1);
    gpio_set_mode(GPIOA,13,GPIO_INPUT_ANALOG);

    while(1){
        int adcr = adc_read(ADC1,0);
        usart_putstr(USART1,"[adc 0] ");
        usart_putudec(USART1, adcr);
        usart_putstr(USART1,"\n");
        gpio_toggle_bit(GPIOB,6);
        gpio_toggle_bit(GPIOB,7);
        usleep_8MHz(500000);
    }

	return 0;
}
