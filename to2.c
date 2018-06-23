#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argv,char **argc){
	if(argv!=2){
		puts("error");
		return -1;
	}
	
	FILE *fp=fopen(argc[1],"r");
	static char buff[1<<20];
	int size=fread(buff,1,1<<20,fp);
	printf("size=%d\n",size);
	for(int i=0;i<size;i++)
		printf("\\x%02x",((int)buff[i])&255);
	puts("");
	fclose(fp);
	return 0;
}
