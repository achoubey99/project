#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/select.h>
#include <errno.h>
#include <fstream>
#include <sys/wait.h>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#define PORTNO 8888 
#define bSIZE 1024
#define TRUE 1
#define FALSE 0

using namespace std;

