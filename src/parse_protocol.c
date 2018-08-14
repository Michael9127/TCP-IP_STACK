#include <stdio.h>
#include "protocol_structs.h"

void print_ethernet(char *buffer, int nread){
    struct eth_hdr *hdr = (struct eth_hdr *) buffer;
    printf("%012x\n", hdr->dmac);


}


