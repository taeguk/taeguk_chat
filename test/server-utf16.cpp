#include "server.h"
#include <wchar.h>

int main(void)
{
	wchar_t s[111]={0,};
	int i;

	setlocale(LC_ALL,"ko_KR.utf8");

	printf("%s\n","你好世界");
	printf("%d\n",strlen("你好世界"));
	printf("%d\n",sizeof("안녕안녕안녕"));
	printf("%d\n",sizeof("aaaaaa"));

	wscanf(L"%S",s);
	for(i=0;i<111;i++)
		printf("%08x ",s[i]);


	return 0;
}
