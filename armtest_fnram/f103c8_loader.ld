ENTRY(I_Reset)

MEMORY
{
    FLASH(rx): ORIGIN = 0x08000000, LENGTH = 128K
    SRAM(rwx): ORIGIN = 0x20000000, LENGTH = 4k
    CRAM(rwx): ORIGIN = 0x20001000, LENGTH = 16k
}

SECTIONS
{
    .text : {
        _stext = .;
        *(.isr)
        . = ALIGN(4);
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
        _etext = .;
    }> FLASH
    
    .data : {
        _sdata = .;
        *(.data .data.* .gnu.linkonce.d.*)
        *(.igot.plt)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH

    .bss : {
        _sbss = .;
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    }> SRAM

    .ctext : {
        _sctext = .;
        . = ALIGN(4);
        *(.ctext*)
        _ectext = .;
    }> CRAM AT> FLASH
}