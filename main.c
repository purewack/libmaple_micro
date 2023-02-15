#include <libnumcalcium.h>
#include <libmaple/gpio.h>
#include <libmaple/usart.h>
#include <libmaple/i2c.h>

void ni2c_send(uint8 addr, uint8 data){
    i2c_start_condition(I2C1);
        usleep_8MHz(1);
        while((I2C1->regs->SR1 & I2C_SR1_SB) == 0){}
        i2c_write(I2C1, addr<<1);
        while((I2C1->regs->SR1 & I2C_SR1_ADDR) == 0){}
        int er = I2C1->regs->SR2;
        er = 0;
        while((I2C1->regs->SR1 & I2C_SR1_TXE) == 0){}
        i2c_write(I2C1, data);
        while((I2C1->regs->SR1 & I2C_SR1_BTF) == 0){}
    i2c_stop_condition(I2C1);
}

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
    //scl
    gpio_set_mode(GPIOB,6,GPIO_AF_OUTPUT_PP);
    //sda
    gpio_set_mode(GPIOB,7,GPIO_AF_OUTPUT_PP);

    usart_putstr(USART1,"[i2c]\n");
    i2c_init(I2C1);
    i2c_set_clk_control(I2C1,40);
    i2c_set_input_clk(I2C1,8);
    i2c_set_trise(I2C1,9);
    i2c_peripheral_enable(I2C1);

    uint8_t a = 1;

    while(1){
        usart_putstr(USART1,"[data]\n");
        ni2c_send(0x20,~a);
        usleep_8MHz(500000);
        a++;
    }

	return 0;
}
