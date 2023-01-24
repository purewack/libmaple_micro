#ifndef COMMON_H
#define COMMON_H

#define CART_FUNC __attribute__ ((section(".cart")))

extern uint32_t _stext;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern uint32_t _scart;
extern uint32_t _ecart;
extern uint32_t _scdata;
extern uint32_t _ecdata;
extern uint32_t _scbss;
extern uint32_t _ecbss;

#endif