#include "server.h"
#include <wchar.h>

int main(void)
{
	wchar_t s[111]={0,};
	int i;

	setlocale(LC_ALL,"ko_KR.utf8");

	printf("%s\n","