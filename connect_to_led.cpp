#include "connect_to_led.hpp"
struct termios tio;
struct termios old_stdio;
int tty_fd;
unsigned char c;

void Connect_to_led::openPort_USB(std::string portName, int baudrate) {
    printf("Connecting :  %s\n", portName.c_str());

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    tty_fd=open(portName.c_str(), O_RDWR | O_NONBLOCK);
    cfsetospeed(&tio,B9600);
    cfsetispeed(&tio,B9600);

    tcsetattr(tty_fd,TCSANOW,&tio);

}

void Connect_to_led::closePort_USB() {
    close(tty_fd);
    tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);
}

void Connect_to_led::writePort(int *message,int s_array) {
    for (int i = 0; i <s_array; i++) {
     write(tty_fd, &message[i], 1);
     usleep(1);
    }
}

int Connect_to_led::readPort() {
    int result = 0;
    int counter =0;
    while(counter <= 2){
        int size = read(tty_fd,&c,1);
        if (size < 0)
            result = 0;
        if (size > 0)
         result = 1;
         break;
         counter ++;
    }

    return result;
}
