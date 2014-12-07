#include "server.h"
#include <wchar.h>

int main(void)
{
	wchar_t s[111]={0,};
	int i;

	setlocale(LC_ALL,"ko_KR.euckr");

	wprintf(L"%S\n",L"테스트테스트");
	printf("%s\n","你好世界");
	printf("%d\n",strlen("你好世界"));
	printf("%d\n",sizeof("안녕안녕안녕"));
	printf("%d\n",sizeof("aaaaaa"));

	char str[111]={0,};

			        scanf("%s",str);

					        for(i=0; i<111;i++)
								                printf("%02x ",(unsigned char)str[i]);

/*	
	wscanf(L"%ls",s);
	for(i=0;i<111;i++)
		printf("%08x ",s[i]);
*/
	return 0;
}
