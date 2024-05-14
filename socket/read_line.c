#include "read_line.h"

ssize_t read_line(int sockfd, void *buffer, size_t n, int flags) {
    ssize_t readlen;
    size_t total;
    char ch;
    char *off;

    if (!buffer || n < 0)
        return -1;

    off = buffer;
    total = 0;

    for (;;) {
        readlen = recv(sockfd, &ch, 1, flags);
        if (readlen < 0) {
            printf("failed to recv form socket\n");
            return -1;
        } else if (readlen == 0) {  /* EOF */
            if (total == 0)
                return 0;
            else 
                break;
        } else {                    /* readlen == 1 */

            
            if (total < n - 1) {
                *off++ = ch;
                total++;
            } 

            if (ch == '\n') {
                break;
            }
        }
    }
    
    *off = '\0';
    return total;
}