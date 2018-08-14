#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tap_alloc.h"

int main() {
  char *tap_name = "tap0";

  /* Connect to the device */
  int tap_fd = tap_alloc(tap_name); /* tap interface */

  if (tap_fd < 0) {
    perror("Allocating interface");
    exit(1);
  }

  /* Now read data coming from the kernel */
  while (1) {
    /* Note that "buffer" should be at least the MTU size of the interface, eg
     * 1500 bytes */
    char buffer[1600];
    int nread = read(tap_fd, buffer, sizeof(buffer));
    if (nread < 0) {
      perror("Reading from interface");
      close(tap_fd);
      exit(1);
    }

    /* Do whatever with the data */
    //printf("Read %d bytes from device %s\n", nread, tap_name);
    printf("%s\n", buffer);
  }
}
