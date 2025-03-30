// Checksum Server Side
#include <arpa/inet.h>
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
    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd, 10);

    struct sockaddr_in cad;
    socklen_t addrlen = sizeof(cad);
    int cd = accept(sd, (struct sockaddr *)&cad, &addrlen);

    char str[100];
    int sep, recv_checksum;
    recv(cd, str, sizeof(str), 0);
    recv(cd, &sep, sizeof(int), 0);
   // recv(cd, &recv_checksum, sizeof(int), 0);
    int received_bytes = recv(cd, &recv_checksum, sizeof(int), 0);
    if (received_bytes != sizeof(int)) {
        printf("Error receiving checksum.\n");
        close(cd);
        close(sd);
        return 1;
    }


    printf("Received message: %s\n", str);

    int len = strlen(str);
    int checksum = 0;
    char block[sep + 1];
    block[sep] = '\0';
    for (int i = 0; i < len; i += sep) {
    strncpy(block, str + i, sep);
    checksum += bin_to_dec(block, sep);
    }

    printf("Checksum %s.\n", (checksum == recv_checksum) ? "valid" : "invalid");

    printf("Received checksum: %d\n", recv_checksum);
   
    close(cd);
    close(sd);
    return 0;
}