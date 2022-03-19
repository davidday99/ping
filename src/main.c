#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char *get_host_address(char *name) {
    struct addrinfo *a;
    int success = getaddrinfo(name, NULL, NULL, &a);
    if (success == 0) {
        for (; a != NULL; a = a->ai_next) {
            struct sockaddr_in *sa = (struct sockaddr_in *) a->ai_addr;
            if (sa->sin_addr.s_addr != 0)
                return inet_ntoa(sa->sin_addr);
        }
    }
    return NULL;    
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ping <host>\n");
        return -1;
    }
    char *hostname = argv[1];
    char *ip = get_host_address(argv[1]);

    printf("PING %s (%s)\n", hostname, ip);
    return 0;
}