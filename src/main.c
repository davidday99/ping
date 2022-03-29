#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "icmp.h"


#define RECV_BUF_SZ 1024 

struct in_addr get_host_address(char *name) {
    struct addrinfo *a;
    struct in_addr dst = {.s_addr = 0};
    int success = getaddrinfo(name, NULL, NULL, &a);
    if (success == 0) {
        for (; a != NULL; a = a->ai_next) {
            struct sockaddr_in *sa = (struct sockaddr_in *) a->ai_addr;
            if (sa->sin_addr.s_addr != 0)
                dst = sa->sin_addr;
        }
    }
    return dst;   
}

void print_icmp_echo_reply(icmp_echo *echo, int ttl, char *hostname, struct in_addr dst) {
    printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%d ms\n",
            sizeof(icmp_echo), hostname, inet_ntoa(dst), ntohs(echo->header.seqnum),
            ttl, 0);
}

icmp_echo *process_packet(struct ip *packet) {
    unsigned int offset = packet->ip_hl * 4;
    icmp_echo *echo = (icmp_echo *) &((uint8_t *) packet)[offset];
    return echo;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ping <host>\n");
        exit(1);
    }

    char *hostname = argv[1];
    struct in_addr ip = get_host_address(argv[1]);
    char *ip_string = inet_ntoa(ip);

    icmp_echo request;
    icmp_echo reply;
    init_icmp_echo(&request, 10, 1);

    int s = socket(AF_INET, SOCK_RAW | SOCK_NONBLOCK, IPPROTO_ICMP);
    
    if (s == -1) {
        printf("Failed to create socket!\n");
        exit(1);
    }
    
    struct sockaddr_in dst_addr;
    struct sockaddr sin_addr;
    socklen_t len;
    dst_addr.sin_family = AF_INET;
    dst_addr.sin_addr = ip;
    char buf[RECV_BUF_SZ];

    printf("PING %s (%s)\n", hostname, ip_string);

    while (1) {
        sendto(s, &request, sizeof(icmp_echo), 0, (struct sockaddr *) &dst_addr, sizeof(dst_addr)); 
        sleep(1);
        recvfrom(s, buf, sizeof(buf), 0, &sin_addr, &len);  
        struct ip *packet = (struct ip *) buf;
        icmp_echo *reply = process_packet(packet);
        if (verify_icmp_echo_reply(&request, reply)) {
            print_icmp_echo_reply(&request, packet->ip_ttl, hostname, ip);
            increment_icmp_echo_seqnum(&request); 
        }
    }

    close(s);
    return 0;
}
