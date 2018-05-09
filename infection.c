#include<stdio.h>

int printf2(const char *format){
    va_list ap;
    VACM();
    return printf(format,ap);
}

#define printf printf2


int main(){
    printf("Hello World\n");
    return 0;
}

