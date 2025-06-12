#include<stdio.h>
#include<string.h>
// #include<arpa/inet.h>
#include<unistd.h>
#include <stdlib.h>
int main(){
    int sd,cadl,datalen,seglen,sum[100],carry,tempsum,k;
   
   
    char data[100],tempdata[100];
    printf("Enter binary string : ");
    scanf("%s",data);
    datalen = strlen(data);
    printf("Enter segment length : ");
    scanf("%d",&seglen);
    if(seglen>datalen){
        printf("Segment length cannot be greater than data length");
        exit(0);
    }
    int rem = datalen%seglen;
    if(rem != 0){
        int j = seglen-rem;
        for(int i=0;i<j;i++){
            tempdata[i] = '0';
        }
        tempdata[j] = '\0';
        strcat(tempdata,data);
        strcpy(data,tempdata);
        datalen = strlen(data);
    }

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
        if(sum[i] == 0){
            sum[i] = 1;
        }
        else{
            sum[i] = 0;
        }
        data[datalen+i] = sum[i]+48;
    }
    datalen = strlen(data);
    data[datalen] = '\0';

    printf("Checksum = ");
    for(int i=0;i<seglen;i++){
        printf("%d",sum[i]);
    }
    printf("\n");

    printf("Sent data = %s",data);

    printf("\n");


    return 0;
}