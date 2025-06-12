#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <stdlib.h>
int main(){
    int sd,cd;
    struct sockaddr_in sad,cad;
    sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd,10);
    int cadl=sizeof(cad);
    cd=accept(sd, (struct sockaddr *)&cad, &cadl);
    int choice;
    char str[50],div[50];
    recv(cd,str,sizeof(str),0);
    recv(cd,div,sizeof(div),0);
    recv(cd,&choice,sizeof(int),0);
    printf("Received string: %s\n", str);
    int len = strlen(str);
    if(choice == 1){
        if(str[len-2] == '1'){
            str[len-2] = '0';
        }
        else{
            str[len-2] = '1';
        }
        printf("Error introduced in the received string: %s\n", str);
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
    printf("No error in receiving\n");
    close(cd);
    close(sd);
    return 0;
}