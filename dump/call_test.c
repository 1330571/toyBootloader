void main(){
	int * addr = (int *)0x100000;
	__asm__("call %%eax"::"a"(*addr));
}
