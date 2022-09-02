.org $C000
   nop
   nop
   nop
   lda #$01
   sta $0201
   lda #$01
   sta $0200
   nop
   nop
   nop
   lda #$03
   sta $0201
   lda #$01
   sta $0200
   nop
   nop
   nop
   lda #$02
   sta $0201
   lda #$01
   sta $0200
loop:
   nop
   jmp loop


