#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// #define port "/dev/ttyUSB0"
#define port "/dev/cu.usbserial-1420"

int fd;

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

void getInfo(char input) {

    write(fd, &input, 1);

    // Pega o primeiro byte do pacote que corresponde ao tamanho da mensagem
    uint8_t buffer_size;
    read(fd, &buffer_size, 1);

    // Pega o resto da mensagem de acordo com o tamanho
    char output[buffer_size];
    read(fd, &output, buffer_size);
    printf("\n%s\n", output);
}

void config_time_inner_menu()
{
    int keepRunningInner = 1;
    int menuOptionInner = -1;
    do
    {
        printf("\n");
        printf("Escolhar uma opção de data: \n");
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
        case 1: getInfo('f');
            break;
        case 2: getInfo('F');
            break;
        case 3: getInfo('h');
            break;
        case 4: getInfo('m');
            break;
        case 5: getInfo('s');
            break;
        case 6: getInfo('d');
            break;
        case 7: getInfo('M');
            break;
        case 8: getInfo('y');
            break;
        case 9:
            keepRunningInner = 0;
            return;
        default:
            printf("Opção inválida\n");
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
        printf("Escolher uma opção de temperatura: \n");
        printf("1 - Celsius\n");
        printf("2 - Fahrenheit\n");
        printf("3 - Voltar\n");

        scanf("%d", &menuOptionInner);
        switch (menuOptionInner)
        {
        case 1: getInfo('T');
            break;
        case 2: getInfo('t');
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
        printf("1 - Data\n");
        printf("2 - Temperatura\n");
        printf("3 - Encerrar\n");

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
            printf("Opção inválida\n");
        }

    } while (keepRunning);
}

int main(int argc, char **argv)
{
    fd = config_serial(port, B9600);
    if (fd < 0)
    {
        return 0;
    }
    
    config_menu();

    return 0;
}
