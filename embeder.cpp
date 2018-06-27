#include<bits/stdc++.h>
using namespace std;
vector<char>content;
string fix(char c){
    if(c==10)return "%c";
    if(c==9)return "%c";
    if(c==34)return "%c";
    if(c==39)return "%c";
    if(c==37)return "%c";
    if(c==92)return "%c";
    return string(1,c);
}
int main(){
    char ch;
    while((ch=cin.get())!=EOF){
        content.push_back(ch);
        cout<<ch;
    }
    cout<<"int main()\n";
    cout<<"{\n";
    cout<<"function1();FILE *file=fopen(\"myself.c\",\"w\");\n";
    cout<<"char *s=\"";
    //cout << fixed C.in
    for(auto c:content)
        cout<<fix(c);
    cout<<"int main()%c{%cfunction1();FILE *file=fopen(%cmyself.c%c,%cw%c);%cchar *s=%c%s%c;%cfprintf(file,s,";
    //cout << ASCII \t \n \"
    for(auto c:content)if(c==10 || c==9 || c==34 || c==39|| c==37|| c==92)
        cout<<int(c)<<",";
    cout<<"10,10,34,34,34,34,10,34,s,34,10,10,10);fclose(file);function2();%c}%c\";\n";
    cout<<"fprintf(file,s,";
    //cout << ASCII \t \n \"
    for(auto c:content)if(c==10 || c==9 || c==34 || c==39|| c==37|| c==92)
        cout<<int(c)<<",";
    cout<<"10,10,34,34,34,34,10,34,s,34,10,10,10);fclose(file);function2();\n";
    cout<<"}\n";
}
