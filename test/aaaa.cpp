#include "server.h"
#include <wchar.h>
#include <ncurses.h>
#include <stdlib.h>

int main(void)
{
	char str[111]={0,};
	wchar_t s[111]={0,};
	int i;

	//setlocale(LC_ALL,"ko_KR.utf8");
	setlocale(LC_ALL,getenv("LANG"));

	initscr();

	getstr(str);

	printf("%s\n",str);

	for(i=0; i<111; i++)
		printf("%02x ",(unsigned char)str[i]);

	refresh();

	getch();

	endwin();
	
	return 0;
}
