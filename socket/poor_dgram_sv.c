#include "poor_dgram_sv.h"

static void help(void)
{
    printf("Usage: server port\n");
    exit(-1);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in addr, peer;
    socklen_t addrlen, peerlen;
    in_port_t port;
    int sockfd, flags = 0, retval = 0;
    char *msg;
    size_t msglen, recvlen;

    if (argc != 2)
        help();

    port = htons(atoi(argv[1]));

    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = INADDR_ANY;

    addrlen = sizeof(addr);
    peerlen = sizeof(peer);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("failed to create socket\n");
        exit(-1);
    }

    retval = bind(sockfd, (struct sockaddr*)&addr, addrlen);
    if (retval < 0) {
        printf("failed to bind socket\n");
        goto out;
    }

    msglen = MAX_MESSAGE;
    msg = (char*)malloc(msglen + 1);
    if (!msg) {
        printf("failed to alloc msg\n");
        goto out;
    }

    printf("Server Running...\n");

    while(1) {
        recvlen = recvfrom(sockfd, msg, msglen, flags, (struct sockaddr*)&peer, &peerlen);
        if (recvlen < 0) {
            printf("failed to recvform socket\n");
            goto out;
        }

        msg[msglen] = '\0';
        printf("recive message \"%s\"\n", msg);
        free(msg);
    }

out:
    close(sockfd);
    free(msg);
    return retval;
}