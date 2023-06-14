#ifndef IRC_HPP
#define IRC_HPP

//--------------------Defines-----------------

#define MAX_EVENTS	1024
#define BUFLEN	1024

//--------------------Libraries-----------------
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/epoll.h>

//--------------------Headers-----------------
#include "Server.hpp"
#include "Client.hpp"

#endif
