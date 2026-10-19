#include <stdio.h>
int main(int argc,char*argv[])
{
	printf("argc的值是：%d\n",argc);
	for(int i=0;i<argc;i++)
	{
		printf("argv[%d]指向的字符串是：%s\n",i,argv[i]);
	}
	return 0;
}
