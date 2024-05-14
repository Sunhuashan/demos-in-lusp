#include "poor_dgram_cl.h"

static void help(void)
{
    printf("Usage: client HOST SERVICE message\n");
    exit(-1);
}

int main(int argc, char *argv[])
{
    const char *host_name, *svc_name, *msg;
    const struct sockaddr *addrptr;
    struct addrinfo hint, *result, *entry;
    int sockfd, flags = 0, retval = 0;
    socklen_t addrlen;
    size_t sendlen, msglen;

    if (argc != 4)
        help();
    
    host_name = argv[1];
    svc_name = argv[2];
    msg = argv[3];
    msglen = strlen(msg) + 1;
    
    memset(&hint, 0, sizeof(struct addrinfo));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_DGRAM;

    // result = (struct addrinfo**)malloc(sizeof(struct addrinfo*));

    retval = getaddrinfo(host_name, svc_name, &hint, &result);
    if (retval != 0) {
        printf("failed to getaddrinfo, host = %s, svc = %s\n", host_name, svc_name);
        exit(-1);
    }

    for (entry = result; entry; entry = entry->ai_next) {
        addrptr = entry->ai_addr;
        addrlen = entry->ai_addrlen;

        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (socket < 0) {
            printf("failed to create socket\n");
            exit(-1);
        }

        sendlen = sendto(sockfd, msg, msglen, flags, addrptr, addrlen);
        if (sendlen < 0) {
            printf("failed to send message\n");
            close(sockfd);
            exit(-1);
        }

        retval = close(sockfd);
        if (retval != 0) {
            printf("failed to close socket\n");
            exit(-1);
        }

        freeaddrinfo(entry);
    }

    return retval;
}