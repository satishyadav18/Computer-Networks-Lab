#include <stdio.h>
#include <string.h>
#include<unistd.h> // providestringclose()
#include <arpa/inet.h> // providestringinet_addr() and htons


int main(){
    int sd, cd;
    struct sockaddr_in sad, cad;
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family = AF_INET;
    sad.sin_port = htons(9995);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sd, (struct sockaddr*)&sad, sizeof(sad));
    listen(sd, 10); 

    int cadl = sizeof(cad);
    cd = accept(sd, (struct sockaddr*)&cad, &cadl); 

    char string[100];     
    
    recv(cd, string, sizeof(string) - 1, 0);

   //s[bytes_received] = '\0';  // Null-terminate the received string

    printf("Received binary string: %s\n", string);

    // --- Parity checking logic ---
    int count = 0;
    int len = strlen(string);
    char parity_bit = string[len - 1];
    string[len - 1] = '\0'; // Remove the parity bit for checking

    for (int i = 0; string[i] != '\0'; i++) {  // i < strlen(string)-2
        if (string[i] == '1') count++;
    }

    printf("Number of 1string(excluding parity bit): %d\n", count);
    printf("Parity bit received: %c\n", parity_bit);

    if ((count % 2 == 0 && parity_bit == '0') || (count % 2 == 1 && parity_bit == '1')) {
        printf("Even Parity Check: SUCCESS\n");
    } else if ((count % 2 == 0 && parity_bit == '1') || (count % 2 == 1 && parity_bit == '0')) {
        printf("Odd Parity Check: SUCCESS\n");
    } else {
        printf("Parity Check: FAILED\n");
    }

    close(cd);
    close(sd);          

    return 0;   


}