#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>

int main(int argc, char const* argv[])
{
    int sockD = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_port
        = htons(9001); // use some unused port number
    servAddr.sin_addr.s_addr = INADDR_ANY;

    int connectStatus
        = connect(sockD, (struct sockaddr*)&servAddr,
                  sizeof(servAddr));

    if (connectStatus == -1) {
        printf("Error...\n");
    }

    else {
        // Constants
        const int MAX_LENGTH = 999;
        const char DELIMITER = '.';

        int i = 0;
        char clMsg[MAX_LENGTH];

        printf("Please enter a string of characters ending with # (up to %i):\n", MAX_LENGTH);
        scanf("%c", &clMsg[0]);

        while (clMsg[i] != DELIMITER) {
            i++;

            // Input size validation
            if (i >= MAX_LENGTH) {
                printf("Error...\n");
                printf("Input is more than %i chars...\n", MAX_LENGTH);

                return 1;
            }

            scanf("%c", &clMsg[i]);
        }
        send(sockD, clMsg, MAX_LENGTH, 0);
    }

    return 0;
}