#ifndef IRC_HPP
#define IRC_HPP

//--------------------Libraries-----------------
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <time.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sstream>

class Client;
class Channel;
class Server;

typedef std::map<int, Client>::iterator vIt_Client;
typedef std::vector<Channel>::iterator vIt_Channel;

enum status{
	pendingPassword,
	pendingUsername,
	registered
};

//--------------------Headers-----------------
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

//--------------------Error Messages-----------------
#define ERR_LOGIN		"You must enter the password first, fdp"
#define ERR_BAD_PASS	"Bad password"
#define ERR_ALRDY_LOG	"You already are connected"
#define ERR_ALRDY_REGIS	"You already are registered"
#define ERR_REGIS		"Register yourself with the USER cmd"
#define ERR_CMD_NOT_FND	"Command not found"
#define ERR_JOIN 		"Wrong usage of JOIN, try `JOIN <channelName>`"
#define ERR_REQ_PASS	"This channel require a password to join, try JOIN <channelName> <password>"
#define ERR_CH_FULL		"This channel is full, try again later"
#define ERR_WRNG_PASS	"Wrong password. Try again"
#define ERR_PASS 		"Wrong usage of PASS, try `PASS <password>`"
#define ERR_PART 		"Wrong usage of PART, try `PART <channelName>`"
#define ERR_USER		"Wrong usage of USER, try `USER <nickname> <username>`"
#define ERR_MSG_LENGTH	"Your message should not exceed 500 characters"

// ------------------ log Messages -------------------

#define LOG_LOGIN		"password entered successfully"
#define LOG_JOIN		"joined channel "
#define LOG_NEW_CHANNEL	"created new channel "
#define LOG_CLOSED		"left the server"
#define LOG_START		"Server started"
#define	LOG_NEW_CLIENT	"connected"

//--------------------Defines-----------------

#define MAX_EVENTS	1024
#define MAX_BUF	500


#endif
