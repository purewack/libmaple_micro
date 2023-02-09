#include "libnumcalcium.h"

int main(void){
    USART_force_init();
    usleep_8MHz(10000);
    USART_str("[libnumcalcium]\n");
    
    sideload_cart_USART();
    int rcart = BEGIN_CART();

    while(1){}

	return 0;
}
