#include "libnumcalcium.h"

int main(void){
    USART_force_init();
    USART_str("[libnumcalcium]\n");
    
    sideload_cart_USART();
    int rcart = BEGIN_CART();

    while(1){}

	return 0;
}
