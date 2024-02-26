#include "io.h"
#include "tty.h"



#include "kbd.h"
#include "../libc/include/string.h"

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0" : "=a" (ret) : "Nd" (port));
    return ret;
}

void outb(uint16_t port, uint8_t val)
{
    __asm__ __volatile__("outb %0, %1" : : "a" (val), "Nd" (port));
}

uint8_t scan(void)
{
    unsigned char brk;
    static uint8_t key = 0;
    uint8_t scan = inb(0x60);
    brk = scan & 0x80;
    scan = scan & 0x7f;
    if (brk)
	return key = 0;
    else if (scan != key)
	return key = scan;
    else
	return 0;
}

void move_cursor(int row, int col)
{
    unsigned short pos = (row * 80) + col;
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, (unsigned char)(pos & 0xFF));
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (unsigned char)((pos >> 8) & 0xFF));
}

void printprompt(void)
{
    printf("\n$> ");
    move_cursor(get_terminal_row(), get_terminal_col());
}

void printprompt_interface(void)
{
     printf("\n$(interface)> ");
    move_cursor(get_terminal_row(), get_terminal_col());
}

void cinput()
{
  	char *buff;
	strcpy(&buff[strlen(buff)], "");
	printprompt();
	while (1) {
		uint8_t byte;
		while (byte = scan()) {
			if (byte == 0x1c) {
				if (strlen(buff) > 0 && strcmp(buff, "exit") == 0)
					printf("\nGoodbye!");
                    printprompt();
				if (strlen(buff) > 0 && strcmp(buff , "login") == 0)
					printf("\n DATA:");
                    printprompt();
                if (strlen(buff) > 0 && strcmp(buff , "help") == 0)
                    printf("\n login     : to login to the FireWall");
                    printf("\n telnet    : to open a telnet conection");
                    printf("\n interface : to get info of the TCP / interface");
                    printf("\n config    : to enter configration mode");
                    printprompt();
                if (strlen(buff) > 0 && strcmp(buff, "interface") == 0 );
                    printprompt_interface();
				
				memset(&buff[0], 0, sizeof(buff));
				break;
			} else {
				char c = normalmap[byte];
				char *s;
				s = ctos(s, c);
				printf("%s", s);
				strcpy(&buff[strlen(buff)], s);
			}
			move_cursor(get_terminal_row(), get_terminal_col());
		}
	}


}