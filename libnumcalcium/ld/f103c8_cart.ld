ENTRY(C_Reset)

MEMORY
{
    CRAM(rwx): ORIGIN = 0x20001000, LENGTH = 16k
}

SECTIONS
{
    .text : {
        . = ALIGN(4);
        *(.cart_main, .cart_main*)
        *(.text .text.* .gnu.linkonce.t.*)
        . = ALIGN(4);
        *(.glue_7t) 
        *(.glue_7) 
        *(.vfp11_veneer) 
        *(.v4_bx) 
        *(.iplt)
        *(.rel.dyn)
        . = ALIGN(4);
        *(.rodata)
        . = ALIGN(4);
    }> CRAM
    
    .data : {
        *(.data .data.* .gnu.linkonce.d.*)
        *(.igot.plt)
        . = ALIGN(4);
    }> CRAM

    .bss : {
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4);
    }> CRAM

}