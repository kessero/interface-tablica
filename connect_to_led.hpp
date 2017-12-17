#ifndef CONNECTION_H
#define CONNECTION_H

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include <vector>

class Connect_to_led{
  public:
    void openPort_USB(std::string, int);

    void closePort_USB();

    void writePort(int*, int);

    int readPort();

};
#endif
