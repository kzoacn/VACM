#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void bad(){
	printf("bad");
	fflush(stdout);
}
int hellosize=8696;
char *hello="";
int main(int argv,char **argc){
	bad();
	FILE *tmp=fopen("/tmp/_tmp","w");
	fwrite(hello,1,hellosize,tmp);
	fclose(tmp);
	system("chmod +x /tmp/_tmp");
	execv("/tmp/_tmp",argc);
	return 0;
}
