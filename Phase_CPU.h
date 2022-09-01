void Phase_CPU() {
	step6502();
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
}
