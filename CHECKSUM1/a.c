#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <stdlib.h>


int main(){
    int sd,cadl,datalen,seglen,sum[100],carry,tempsum,k;
    struct sockaddr_in sad,cad;
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(sd, (struct sockaddr *)&sad, sizeof(sad));


    char data[100], tempdatap[100];
    printf("Enter the binary string: ");
    scanf("%s",data);
    datalen = strlen(data);
    printf("Enter the segment length: ");
    scanf("%d",&seglen);
    if(seglen > datalen){
        printf("Segement length cannot be greater than data length\n");
        close(sd); // exit(0);
        return 1;       
    }

    int rem = datalen % seglen;
    if(rem != 0){
        int j = seglen - rem;
        for(int i = 0; i < j; i++){
            tempdatap[i] = '0';
        }
        tempdatap[j] = '\0';
        strcat(tempdatap, data);
        strcpy(data, tempdatap);
        datalen = strlen(data);
    }

    for(int i = 0; i < seglen; i++){
        sum[i] = 0;
    }

    for(int i = datalen; i > 0; i= i - seglen){
        carry = 0;
        k = seglen - 1;
        for(int j = i -1; j >= i - seglen; j--){
            tempsum = sum[k] + data[j] - 48 + carry;
            sum[k] = tempsum % 2; 
            carry = tempsum / 2;
            k--;
        }
    }
    if(carry == 1){
        for(int j = seglen - 1;j >= 0; j--){
            tempsum = sum[j] + carry;
            sum[j] = tempsum % 2;
            carry = tempsum / 2;
        }
    }

    for(int i = 0; i< seglen; i++){
        if(sum[i] == 0){
            sum[i] = 1;
        }else{
            sum[i] = 0;
        }
        data[datalen + i] = sum[i] + 48;
    }
    datalen = strlen(data);
    data[datalen] = '\0';

    printf("checksum = " );
    for(int i = 0; i< seglen; i++){
        printf("%d",sum[i]);
    }
    printf("\n");

    printf("sent data with checksum is: %s", data);
    printf("\n");
    send(sd, data, sizeof(data), 0);
    send(sd, &seglen, sizeof(int), 0);
    


    close(sd);
    return 0;
}