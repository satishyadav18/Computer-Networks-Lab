#include<stdio.h>
#include <string.h>
#include<unistd.h> // provides close()
#include <arpa/inet.h> // provides inet_addr() and htons


int main(){
    int sd, cd;
    struct sockaddr_in sad, cad;
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family = AF_INET;
    sad.sin_port = htons(9995);
    sad.sin_addr.s_addr = inet_addr("127.0.01");

    connect(sd, (struct sockaddr*)&sad, sizeof(sad));
    char string[100], parity_bit[2] = "";
    char ch;
    int count = 0;
    printf("Enter a binary string (only 0s and 1s):\n");
    scanf(" %s", string); // read entire line including spaces
    for (int i = 0; string[i] != '\0'; i++) {  //i < strlen(string)
        if (string[i] == '1') {
            count++;
        }
        else if (string[i] != '0') {
            printf("Invalid character in input. Only 0s and 1s allowed.\n");
            close(sd);
            return 1;
        }
    }
    printf("Total number of 1s: %d\n", count);
    printf("Enter the mode of parity ('e' for Even, 'o' for Odd): ");
    scanf(" %c", &ch);
    if (ch == 'e') {
        strcat(string, (count % 2 == 0) ? "0" : "1");
    } else if (ch == 'o') {
        strcat(string, (count % 2 == 0) ? "1" : "0");
    } else {
        printf("Invalid parity mode\n");
        close(sd);
        return 1;
    }
    printf("String after adding parity bit: %s\n", string);
    // Send to server
    send(sd, string, strlen(string), 0);
    close(sd);          
    return 0;   
}