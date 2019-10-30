#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int config_serial(char *device, unsigned int baudrate)
{
    struct termios options;
    int fd;

    fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd < 0)
    {
        /*
        * Could not open the port.
        */
        printf("\n\n%d\n\n", errno);
        perror("config_serial: Não pode abrir a serial - ");
        return -1;
    }

    fcntl(fd, F_SETFL, 0);
    /*
    * Get the current options for the port...
    */
    tcgetattr(fd, &options);

    /* sets the terminal to something like the "raw" mode */
    cfmakeraw(&options);

    /*
    * Set the baudrate...
    */
    cfsetispeed(&options, baudrate);
    cfsetospeed(&options, baudrate);
    /*
    * Enable the receiver and set local mode...
    */
    options.c_cflag |= (CLOCAL | CREAD);

    /*
    * No parit, 1 stop bit, size 8
    */
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    /*
    * Clear old settings
    */
    options.c_cflag &= ~CRTSCTS;
    options.c_iflag &= ~(IXON | IXOFF | IXANY);

    /* non-caninical mode */
    options.c_lflag &= ~ICANON;
    /*
    * Set the new options for the port...
    */
    tcsetattr(fd, TCSANOW, &options);

    /* configura a tty para escritas e leituras não bloqueantes */
    //fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);

    return fd;
}
int main(int argc, char **argv)
{
    int fd, val;
    char a;
    if (argc < 2)
    {
        printf("Usage: ./serial <char>");
        return 0;
    }
    fd = config_serial("/dev/ttyUSB0", B9600);
    if (fd < 0)
    {
        return 0;
    }
    a = argv[1][0];
    write(fd, &a, 1);
    val=0;
    
    read(fd, &a, 1);
    printf("%c\n", a);
    val = (a<<8);
    
    read(fd, &a, 1);
    val|=a;
    printf("%c\n", a);

    printf("%d\n", val);
    close(fd);
    return 0;
}
