#include "poor_stream_sv.h"
#include "read_line.h"

static void help(void) {
    printf("Usage: server PORT\n");
    exit(-1);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in addr, peer;
    socklen_t addrlen, peerlen;
    in_port_t port;
    int sockfd, handlfd, flags = 0, retval = 0;
    char *buffer, *peername;
    size_t bufflen, revclen;

    if (argc != 2)
        help();

    port = htons(atoi(argv[1]));

    memset(&addr, 0, sizeof(struct sockaddr_in));
    memset(&peer, 0, sizeof(struct sockaddr_in));

    addr.sin_port = port;
    addr.sin_addr.s_addr = INADDR_ANY;
    addrlen = sizeof(struct sockaddr_in);
    peerlen = sizeof(struct sockaddr_in);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket < 0) {
        printf("failed to create socket\n");
        exit(-1);
    }
    
    retval = bind(sockfd, (struct sockaddr*)&addr, addrlen);
    if (retval < 0) {
        printf("failed to bind socket\n");
        goto out;
    }

    retval = listen(sockfd, SOMAXCONN);
    if (retval < 0) {
        printf("failed to listen socket\n");
        goto out;
    }

    bufflen = MAX_STREAM;
    buffer = (char*)malloc(bufflen + 1);
    if (!buffer) {
        printf("failed to malloc buffer\n");
        goto out;
    }

    printf("Server Running...\n");

    while (1) { 
        handlfd = accept(sockfd, (struct sockaddr*)&peer, &peerlen);
        if (handlfd < 0) {
            printf("failed to accept socket\n");
            goto free;
        }

        revclen = read_line(handlfd, (void*)buffer, bufflen, flags);
        if (revclen < 0) {
            printf("falied to read_line from socket\n");
            goto out0;
        }

        peername = (char*)malloc(INET_ADDRSTRLEN);
        if (!peername) {
            printf("failed to malloc peername\n");
            goto out0;
        }
        inet_ntop(AF_INET, (void*)&peer.sin_addr, peername, peerlen);

        buffer[bufflen] = 0;
        printf("success to recv \"%s\" form %s\n", buffer, peername);

        free(peername);
        free(buffer);
        close(handlfd);
    }


out0:
    if (close(handlfd) < 0)
        printf("failed to close handle socket\n");

free:
    free(buffer);

out:
    if (close(sockfd) < 0)
        printf("failed to close listen socket\n");
    return retval;
}