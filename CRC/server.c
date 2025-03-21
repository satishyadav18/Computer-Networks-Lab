#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <stdlib.h>
int main(){
    int sd,cd,cadl,oneCount=0,choice;
    struct sockaddr_in sad,cad;
    char str[50],div[50];
    sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd,10);
    cadl=sizeof(cad);
    cd=accept(sd, (struct sockaddr *)&cad, &cadl);
    recv(cd,str,sizeof(str),0);
    recv(cd,div,sizeof(div),0);
   // recv(cd,&choice,sizeof(int),0);

    if(choice == 1){
        if(str[0] == '1'){
            str[0] = '0';
        }
        else{
            str[0] = '1';
        }
    }

    for(int i=0;i<=strlen(str)-strlen(div);i++){
        if(str[i]=='1'){
            for(int j=0;j<strlen(div);j++){
                str[i+j]=((div[j]-'0' ^ str[i+j]-'0'))+'0';
            }
        }
    }

    for(int i=0;i<strlen(str);i++){
        if(str[i] != '0'){
            printf("Error in receiving");
            exit(1);
        }
    }
    printf("No error in receiving");

    close(cd);
    close(sd);
    return 0;
}