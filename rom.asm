.org $C000
   nop
   nop
   nop
   lda #$01
   sta $0200
   lda #$00
   sta $0200
loop:
   nop
   jmp loop


