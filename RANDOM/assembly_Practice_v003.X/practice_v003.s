.include "xc.inc"          ; required "boiler-plate" (BP)

;the next two lines set up the actual chip for operation - required
config __CONFIG2, POSCMOD_EC & I2C1SEL_SEC & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSECME & FNOSC_FRCPLL & SOSCSEL_LPSOSC & WUTSEL_FST & IESO_OFF
config __CONFIG1, WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & BKBUG_ON & GWRP_ON & GCP_ON & JTAGEN_OFF

    .bss        ; put the following labels in RAM
counter:
    .space 2    ; a variable that takes two bytes (we won?t use
                ; it for now, but put here to make this a generic
                ; template to be used later).
stack:
    .space  32  ; this will be our stack area, needed for func calls

.text           ; BP (put the following data in ROM(program memory))

;because we are using the C compiler to assemble our code, we need a "_main" label
;somewhere. (There's a link step that looks for it.)
.global _main               ;BP
;your functions go here

_main:

    bclr    CLKDIV,#8                 ;BP
    nop
    ;; --- Begin your main program below here ---

    mov #0x0000, W4 ; initialize w4 to 0
    mov #0x001A, W3 ; send n to W3
    mov #0x0000, W5 ; initialize W5 to 0 (this is F(n-2))
    mov #0x0001, W6 ; initialize W6 to 1 (this is F(n-1))
    dec W3, W3 ; decrement value at W3 before loop is entered
    
    Loop:
    
	add W6, W5, W4 ; add F(n-2) and F(n-1) to W4
	mov W6, W5 ; mov F(n-1) to F(n-2)
	mov W4, W6 ; move 
	dec W3, W3 ; decrement value at W3
	bra NZ, Loop ; if not zero, loop again
    
.end
