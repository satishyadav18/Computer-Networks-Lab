#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){

    char store[100],data[100];
    int sd,cadl,r=0,temp;
    struct sockaddr_in sad,cad;
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(sd, (struct sockaddr *)&sad, sizeof(sad));
    printf("Enter the data : ");
    scanf("%s",store);

    int m = strlen(store);

    while(1){
        int res = (int)pow(2,r);
        if(res >= (m+r+1)){
            break;
        }
        r++;
    }

    int total = m+r;
    int j = 0;

    for(int i=total;i>=1;i--){
        if((i & (i - 1)) == 0){
            data[i] = 'p';
        }
        else{
            data[i] = store[j++];
        }
    }
    data[total+1] = '\0';

    for(int i=0;i<r;i++){
        int pos = (int)pow(2,i);
        int sum = 0;
        for(int j=pos;j<=total;j++){
            if(data[j]!='p'){
                temp = pos & j;
                if(temp != 0 && data[j] == '1'){
                    sum++;
                }
            }
        }
        data[pos] = (sum%2) + 48;
    }
    int left = 1,right = strlen(data)-1;
    while(left < right){
        int t = data[left];
        data[left] = data[right];
        data[right] = t;
        left++;
        right--;
    }
    printf("%s\n",data+1);
    // printf("%d",strlen(data));

    send(sd, data, sizeof(data),0);
    send(sd, &r, sizeof(int),0);
    close(sd);

    return 0;
}
