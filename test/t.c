#include <stdio.h>

int main(void)
{
	char str[111]={0,};
	int i;

	scanf("%s",str);

	for(i=0; i<111;i++)
		printf("%02x ",(unsigned char)str[i]);

	return 0;
}
