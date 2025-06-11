#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int sd,cd,cadl,r;
    struct sockaddr_in sad,cad;
    char data[100];
    sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd,10);
    cadl=sizeof(cad);
    cd=accept(sd, (struct sockaddr *)&cad, &cadl);
    recv(cd,data,sizeof(data),0);
    recv(cd,&r,sizeof(int),0);
    printf("Received data: %s\n",data+1);
    int length = strlen(data+1);
    int checker[r];
    for(int i=1;i<=length;i++){
        data[i] = data[i] - 48;
    }
    int left = 1,right = length;
    while(left < right){
        int t = data[left];
        data[left] = data[right];
        data[right] = t;
        left++;
        right--;
    }
    for(int i=0;i<r;i++){
        int rem = (int)pow(2,i);
        int sum=0;
        for(int j=rem;j<=length;j++){
            int res = rem & j;
            if(res != 0){
                sum += data[j];
            }
        }
        checker[i] = sum%2;
    }
    int sum = 0;
    for(int i=0;i<r;i++){
        if(checker[i] == 1){
            sum += (int)pow(2,i);
        }
    }
    if(sum == 0){
        printf("No error in transmission");
    }
    else{
        printf("There is error in bit %d",sum);
    }


    close(cd);
    close(sd);
}