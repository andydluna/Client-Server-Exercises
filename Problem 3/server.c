#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>

int main(int argc, char const* argv[])
{
    // create server socket similar to what was done in
    // client program
    int servSockD = socket(AF_INET, SOCK_STREAM, 0);

    // define server address
    struct sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(9001);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    // bind socket to the specified IP and port
    bind(servSockD, (struct sockaddr*)&servAddr,
         sizeof(servAddr));

    // listen for connections
    listen(servSockD, 1);

    // integer to hold client socket.
    int clientSocket = accept(servSockD, NULL, NULL);

    const int MAX_LENGTH = 999;
    int i = 0, j = 0, count = 0;
    char strData[MAX_LENGTH], word[MAX_LENGTH];

    recv(clientSocket, strData, MAX_LENGTH, 0);

    while (strData[i] != '#') {
        if (strData[i] != ' ') {
            word[j++] = strData[i];
        }
        else {
            if (j > 2 && strData[j-3] == 'i' && strData[j-2] == 'n'
                && strData[j - 1] == 'g') {
                // FIXME: ensure it only prints when word ends with ing
                count++;
                printf("%s\n", word);
            }
            j = 0;
            memset(word, '\0', MAX_LENGTH);
        }
        i++;
    }

    if (j > 2 && strData[j-3] == 'i' && strData[j-2] == 'n'
        && strData[j - 1] == 'g') {
        count++;
        printf("%s\n", word);
    }

    send(clientSocket, &count, sizeof(count), 0);

    return 0;
}