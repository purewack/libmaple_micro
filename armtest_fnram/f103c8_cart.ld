ENTRY(C_Reset)

MEMORY
{
    CRAM(rwx): ORIGIN = 0x20000400, LENGTH = 16k
}

SECTIONS
{
    .text : {
        _stext = .;
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
    }> CRAM
    
    .data : {
        _sdata = .;
        *(.data .data.* .gnu.linkonce.d.*)
        *(.igot.plt)
        . = ALIGN(4);
        _edata = .;
    }> CRAM

    .bss : {
        _sbss = .;
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    }> CRAM

}