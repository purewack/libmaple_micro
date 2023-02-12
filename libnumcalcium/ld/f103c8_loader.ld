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
        KEEP(*(.isr))
        . = ALIGN(4);
        KEEP(*(.system .system*))
        KEEP(*(.loader .loader*))
        *(.init .init.* .fini .fini*)
        . = ALIGN(4);
        *(.text .text.* .gnu.linkonce.t.*)
        . = ALIGN(4);
        *(.rodata .rodata*)
        . = ALIGN(4);
        *(.glue_7t) 
        . = ALIGN(4);
        *(.glue_7) 
        . = ALIGN(4);
        *(.vfp11_veneer) 
        . = ALIGN(4);
        *(.v4_bx) 
        . = ALIGN(4);
        *(.iplt)
        . = ALIGN(4);
        *(.rel.dyn)
        . = ALIGN(4);
        _etext = .;
    }> FLASH
    
    .data : {
        _sdata = .;
        *(.data .data.* .gnu.linkonce.d.*)
        . = ALIGN(4);
        *(.igot.plt)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH

    .bss : {
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    }> SRAM
}