#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <syslog.h>

#include <util.h>

//-----------------------------------------------------------------------------
int main(int argc, char *argv [])
{
    char * port1 = NULL;
    char * port2 = NULL;

    openlog("test", LOG_PID | LOG_CONS | LOG_PERROR, LOG_LOCAL0);  // open logger with flags to save pid, send to console and stderr

    // parse comand line
    if (argc != 5)
    {
        fprintf(stderr, "Invalid usage: reader -o port_name -p port_name\n");
        exit(EXIT_FAILURE);
    }

    char *options = "o:p:";
    int option;
    while((option = getopt(argc, argv, options)) != -1)
    {
        switch(option)
        {
            case 'o':
                port1 = optarg;
                break;

            case 'p':
                port2 = optarg;
                break;

            case '?':
                fprintf(stderr, "Invalid option %c\n", optopt);
                exit(EXIT_FAILURE);
        }
    }


    int fd[2];

    // open serial port
    fd[0] = open(port1, O_RDWR | O_NOCTTY);
    if (fd[0] == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    tcflush(fd[0], TCIOFLUSH);

    fd[1] = open(port2, O_RDWR | O_NOCTTY);
    if (fd[1] == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    tcflush(fd[1], TCIOFLUSH);

    // read port
    char buff[50];
    fd_set fdset;

    while(1)
    {
        FD_ZERO(&fdset);
        for (int i=0; i<2; i++) {

            bzero(buff, sizeof(buff));

            FD_SET(fd[i], &fdset);

            select(fd[i]+1, &fdset, NULL, NULL, NULL);

            if (FD_ISSET(fd[i], &fdset))
            {
                int bytes = read (fd[i], buff, sizeof(buff));

                if (bytes > 0)
                {
                    printf("%s\n", buff);
                    fflush(stdout);
                }

                printf("read from fd %d\n", i);
            }
        }


    }

    // close serial port
    for (int i=0; i<2; i++) {
       close(fd[i]);
    }

    exit(EXIT_SUCCESS);
}
