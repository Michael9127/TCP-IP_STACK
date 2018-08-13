#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h> 
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <errno.h>
#include <stdlib.h>


int tun_alloc(char *dev)
{
    struct ifreq ifr;
    int fd, err;

    if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ) {
        printf("Cannot open TUN/TAP dev");
        exit(1);
    }

    memset(&ifr, 0, sizeof(ifr));

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    if( *dev ) {
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
        printf("ERR: Could not ioctl tun: %s\n", strerror(err));
        close(fd);
        return err;
    }

    //strncpy(dev, ifr.ifr_name, sizeof(dev));
    return fd;
}

int main()
{
    char *tun_name = "tun0";

    /* Connect to the device */
    int tun_fd = tun_alloc(tun_name);  /* tun interface */

    if(tun_fd < 0){
        perror("Allocating interface");
        exit(1);
    }

    /* Now read data coming from the kernel */
    while(1) {
        /* Note that "buffer" should be at least the MTU size of the interface, eg 1500 bytes */
        char *buffer[1600];  
        int nread = read(tun_fd,buffer,sizeof(buffer));
        if(nread < 0) {
            perror("Reading from interface");
            close(tun_fd);
            exit(1);
        }

        /* Do whatever with the data */
        printf("Read %d bytes from device %s\n", nread, tun_name);
    }

}

