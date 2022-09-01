what:
	@echo "make what?"
	@echo "   rom"
	@echo "   shoelace"

rom: 
	ca65 -t none --cpu 65c02 rom.asm
	ld65 -t none rom.o -o rom.bin

shoelace:
	gcc ShoeLace.c -o shoelace

clean_r:
	rm rom.bin
	rm rom.o

clean_s:
	rm shoelace

clean: clean_r clean_s
