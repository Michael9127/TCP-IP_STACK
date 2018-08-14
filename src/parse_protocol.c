#include <stdio.h>
#include "protocol_structs.h"

void print_ethernet(char *buffer, int nread){
    struct eth_hdr *hdr = (struct eth_hdr *) buffer;
    printf("DST: %02x:%02x:%02x:%02x:%02x:%02x SRC: %02x:%02x:%02x:%02x:%02x:%02x ethertype: %d\n", 
            hdr->dmac[0],
            hdr->dmac[1],
            hdr->dmac[2],
            hdr->dmac[3],
            hdr->dmac[4],
            hdr->dmac[5],
            hdr->smac[0],
            hdr->smac[1],
            hdr->smac[2],
            hdr->smac[3],
            hdr->smac[4],
            hdr->smac[5],
            hdr->ethertype
            );

}


