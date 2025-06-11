#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <stdlib.h>
int main(){
    int sd,cd,cadl,datalen,seglen,sum[100],carry,tempsum,k;
    struct sockaddr_in sad,cad;
    sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd,10);
    cadl=sizeof(cad);
    cd=accept(sd, (struct sockaddr *)&cad, &cadl);
    char data[100];
    recv(cd,data,sizeof(data),0);
    recv(cd,&seglen,sizeof(int),0);
    printf("Received data: %s\n",data);

    datalen = strlen(data);

    for(int i=0;i<seglen;i++){
        sum[i] = 0;
    }

    for(int i=datalen;i>0;i=i-seglen){
        k = seglen - 1;
        carry = 0;
        for(int j=i-1;j>=(i-seglen);j--){
            tempsum = sum[k] + (data[j]-48) + carry;
            sum[k] = tempsum%2;
            carry = tempsum/2;
            k--;
        }
        if(carry == 1){
            for(int j=(seglen-1);j>=0;j--){
                tempsum = sum[j] + carry;
                sum[j] = tempsum%2;
                carry = tempsum/2;
            }
        }
    }

    for(int i=0;i<seglen;i++){ 
        if(sum[i] != 1){
            printf("Error detected\n");
            exit(0);
        }
    }
    printf("No error detected\n");

    close(cd);
    close(sd);
}