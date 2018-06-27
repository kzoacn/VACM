#include<stdio.h>
void function1(){
	puts("I am Quine.");
}
void function2(){
	
}
int main()
{
function1();FILE *file=fopen("myself.c","w");
char *s="#include<stdio.h>%cvoid function1(){%c%cputs(%cI am Quine.%c);%c}%cvoid function2(){%c%c%c}%cint main()%c{%cfunction1();FILE *file=fopen(%cmyself.c%c,%cw%c);%cchar *s=%c%s%c;%cfprintf(file,s,10,10,9,34,34,10,10,10,9,10,10,10,10,34,34,34,34,10,34,s,34,10,10,10);fclose(file);function2();%c}%c";
fprintf(file,s,10,10,9,34,34,10,10,10,9,10,10,10,10,34,34,34,34,10,34,s,34,10,10,10);fclose(file);function2();
}
