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

void config_time_inner_menu()
{
    int keepRunningInner = 1;
    int menuOptionInner = -1;
    do
    {
        printf("\n");
        printf("Escolhar uma opção relacionada a tempo: \n");
        printf("1 - Horario completo\n");
        printf("2 - Data completa\n");
        printf("-----------------------\n");
        printf("3 - Hora\n");
        printf("4 - Minuto\n");
        printf("5 - Segundo\n");
        printf("6 - Dia\n");
        printf("7 - Mês\n");
        printf("8 - Ano\n");
        printf("9 - Voltar\n");

        scanf("%d", &menuOptionInner);
        switch (menuOptionInner)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            keepRunningInner = 0;
            return;
        default:
            printf("Opção invalida\n");
        }

    } while (keepRunningInner);
}

void config_temperature_inner_menu()
{
    int keepRunningInner = 1;
    int menuOptionInner = -1;
    do
    {
        printf("\n");
        printf("Escolhar uma opção relacionada a temperatura atual: \n");
        printf("1 - Celsius\n");
        printf("2 - Fahrenheit\n");
        printf("3 - Voltar\n");

        scanf("%d", &menuOptionInner);
        switch (menuOptionInner)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            keepRunningInner = 0;
            return;
        default:
            printf("Opção invalida\n");
        }

    } while (keepRunningInner);
}

void config_menu()
{
    int keepRunning = 1;
    int menuOption = -1;

    do
    {
        printf("\n");
        printf("Escolhar uma opção: \n");
        printf("1 - Tempo\n");
        printf("2 - Temperatura\n");
        printf("3 - Encerar\n");

        scanf("%d", &menuOption);

        switch (menuOption)
        {
        case 1:
            config_time_inner_menu();
            break;
        case 2:
            config_temperature_inner_menu();
            break;
        case 3:
            printf("Finalizando... \n");
            keepRunning = 0;
            return;
        default:
            printf("Opção invalida\n");
        }

    } while (keepRunning);
}

int main(int argc, char **argv)
{
    // int fd, val;
    // char a;
    // if (argc < 2)
    // {
    //     printf("Usage: ./serial <char>");
    //     return 0;
    // }
    // fd = config_serial("/dev/ttyUSB0", B9600);
    // if (fd < 0)
    // {
    //     return 0;
    // }

    // a = argv[1][0];
    // write(fd, &a, 1);
    // val = 0;

    // read(fd, &a, 1);
    // printf("%c\n", a);
    // val = (a << 8);

    config_menu();

    return 0;
}
