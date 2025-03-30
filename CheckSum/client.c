// Checksum Client Side
#include <arpa/inet.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int bin_to_dec(const char *arr, int len) {
    int dec = 0;
    for (int i = 0; i < len; i++) dec = dec * 2 + (arr[i] - '0');
    return dec;
}

int main() {
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sad = {AF_INET, htons(9995), inet_addr("127.0.0.1")};
    connect(sd, (struct sockaddr *)&sad, sizeof(sad));

    char str[100];
    int sep;
    printf("Enter your binary message: ");
    scanf("%s", str);
    printf("Enter separator size: ");
    scanf("%d", &sep);

    int len = strlen(str);
    int num_blocks = (len + sep - 1) / sep;  // ceiling division
    int padded_len = num_blocks * sep;
    for (int i = len; i < padded_len; i++) str[i] = '0';
    str[padded_len] = '\0';

    int checksum = 0;
    char block[sep + 1];
    block[sep] = '\0';
    for (int i = 0; i < padded_len; i += sep) {
    strncpy(block, str + i, sep);
    checksum += bin_to_dec(block, sep);
    }

    send(sd, str, sizeof(str), 0);
    send(sd, &sep, sizeof(int), 0);
    send(sd, &checksum, sizeof(int), 0);

    close(sd);
    return 0;
}