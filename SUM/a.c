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


    close(sd);
    return 0;
}