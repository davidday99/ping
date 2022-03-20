#include <stdint.h>

uint16_t csum(uint16_t *ptr,int nbytes) {
	register long sum;
	unsigned short oddbyte;
	register short answer;

	sum=0;
	while(nbytes > 1) {
		sum += *ptr++;
		nbytes -= 2;
	}
	if(nbytes == 1) {
		oddbyte = 0;
		*((uint8_t*) &oddbyte) = *((uint8_t*) ptr);
		sum+=oddbyte;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum = sum + (sum >> 16);
	answer = (uint16_t) ~sum;
	
	return answer;
}

