#include "kernel/tty.h"
#include "kernel/io.h"
#include "kernel/kbd.h"
#include "libc/include/string.h"


void kernel_early(void) {
	
	terminal_initialize();
}

int main(void) {
	



	printf("RAM OS/UNIX\n");
	printf("IO/S LOADING  [######################]\n");
	printf("Copyright Nadir Van Thielen 2024 (C)\n");
	printf("GPLv2 Private licence FireWall CLASS 1\n");
	printf("Enter: help to se, the help commands protocols");

	cinput();

	
	return 0;
		
	 
			
	


}
