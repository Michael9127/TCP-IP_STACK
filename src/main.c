#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tun_alloc.h"

int main() {
  char *tun_name = "tun0";

  /* Connect to the device */
  int tun_fd = tun_alloc(tun_name); /* tun interface */

  if (tun_fd < 0) {
    perror("Allocating interface");
    exit(1);
  }

  /* Now read data coming from the kernel */
  while (1) {
    /* Note that "buffer" should be at least the MTU size of the interface, eg
     * 1500 bytes */
    char *buffer[1600];
    int nread = read(tun_fd, buffer, sizeof(buffer));
    if (nread < 0) {
      perror("Reading from interface");
      close(tun_fd);
      exit(1);
    }

    /* Do whatever with the data */
    printf("Read %d bytes from device %s\n", nread, tun_name);
  }
}
