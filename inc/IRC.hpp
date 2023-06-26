#ifndef IRC_HPP
#define IRC_HPP

//--------------------Libraries-----------------
#include <iostream>
#include <csignal>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <map>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sstream>

class Client;
class Channel;
class Server;

typedef std::map<int, Client *>::iterator vIt_Client;
typedef std::map<std::string, Channel *>::iterator vIt_Channel;

enum status{
	pendingPassword,
	pendingNickname,
	pendingUsername,
	registered
};

//--------------------Headers-----------------
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

//-------------------- Client Error Messages -----------------
#define ERR_PEND_PASS	"You must enter the password using PASS"
#define ERR_PEND_NICK	"You must set your Nickname using NICK"
#define ERR_PEND_REGIS	"You must register yourself with the USER cmd"
#define ERR_ALRDY_LOG	"You already are connected"
#define ERR_ALRDY_NICK	"You already have entered a Nickname"
#define ERR_ALRDY_REGIS	"You already are registered"
#define ERR_BAD_PASS	"Wrong password"
#define ERR_CMD_NOT_FND	"Command not found"
#define ERR_NICK_TAKEN	"This nickname is not available, try another one"
#define ERR_CH_NAME		"Channel names must start with '#' or '&'"
#define ERR_REQ_PASS	"This channel require a password to join, try JOIN <channelName> [password]"
#define ERR_CH_FULL		"This channel is full, try again later"
#define ERR_REQ_INVIT	"You need an invitation to join this channel"
#define ERR_WRNG_PASS	"Wrong channel password. Try again"
#define ERR_HELP		"Wrong usage of HELP, try `HELP` without any arguments"
#define ERR_MODE		"Wrong usage of MODE, try `MODE <channelName> {[+|-]|o|i|t|l|k} [<userLimit>] [<userName>]`"
#define ERR_INVITE		"Wrong usage of INVITE, try `INVITE <nickname> <channel>`"
#define ERR_JOIN 		"Wrong usage of JOIN, try `JOIN <channelName>`"
#define ERR_PASS 		"Wrong usage of PASS, try `PASS <password>`"
#define ERR_PART 		"Wrong usage of PART, try `PART <channelName>`"
#define ERR_KICK		"Wrong usage of KICK, try `KICK <channelName> <nickname>`"
#define ERR_NICK		"Wrong usage of NICK, try `NICK <nickname>"
#define ERR_TOPIC		"Wrong usage of TOPIC, try TOPIC <channelName> [newTopic]"
#define ERR_PRIVMSG		"Wrong usage of PRIVMSG, try `PRIVMSG <destination> <message>`"
#define ERR_USER		"Wrong usage of USER, try `USER <username> <hostName> <serverName> <realName>`"
#define ERR_NO_TOPIC	"This channel has no Topic for the moment"
#define ERR_NOT_MEMBER	"You are not member of this channel"
#define ERR_KICK_OP		"This user is operator on this channel"
#define ERR_USR_NO_MEM	"This user is not a member of this channel"
#define ERR_NOT_OP		"You are not operator in this channel"
#define ERR_ALR_MEM		"You already are member of this channel"
#define ERR_USRA_OP		"This user is already operator"
#define ERR_USRN_OP		"This user is not operator on this channel"
#define ERR_USRN_MEM	"This user is not member of this channel"
#define ERR_OP_LEAVER	"You are operator in this channel, try revoke your rights before leaving"
#define ERR_UNKWN_CH	"Could not find channel "
#define ERR_MSG_LENGTH	"Your message should not exceed 500 characters"
#define ERR_USR_NOT_FND "User not found"
#define ERR_MODE_LIMIT	"Limit argument is not a number"

//-------------------- Client Log Messages -----------------
#define CLOG_PASS		"Password accepted"
#define CLOG_REGIS		"Successfully registered"
#define CLOG_CRT_CH		"Successfully created channel "
#define CLOG_JOIN_CH	"Successfully joined channel "
#define CLOG_LEFT_CH	"You left channel "
#define CLOG_INVITED	"You have been invited to channel "
#define CLOG_INVT_SUCC	"client invited to channel successfully"
#define CLOG_KICK_USR	"Kicked user "
#define CLOG_TOPIC_SET	"Change topic channel for : "
#define CLOG_GRAN_OP	"Granted "
#define CLOG_REV_OP		"Revoked "
#define CLOG_LIMIT		"limit changed successfully"
#define CLOG_PASS_REM	"Removed password from channel "
#define CLOG_PASS_CHG	"Changed password from channel "

// ------------------ Server log Messages -------------------
#define LOG_LOGIN		"password entered successfully"
#define LOG_NICK		"Nickname entered successfully"
#define LOG_JOIN		"joined channel "
#define LOG_NEW_CHANNEL	"created new channel "
#define LOG_CLOSED		"left the server"
#define LOG_START		"Server started"
#define	LOG_NEW_CLIENT	"connected"
#define LOG_MSG_CLIENT	"sent message to "
#define LOG_MSG_CHANNEL	"sent message to channel "
#define LOG_INVIT		"invited a client to channel "
#define LOG_KICK_CH		"kicked user from channel"
#define LOG_GRAN_OP		"granted "
#define LOG_REV_OP		"Revoked "
#define LOG_LIMIT		"changed number of limit user of channel "
#define LOG_PASS_REM	"removed password from channel "
#define LOG_PASS_CHG	"changed password from channel "

//--------------------Colors-----------------
#define BLK "\e[1;30m"
#define RED "\e[1;31m"
#define GRN "\e[1;32m"
#define YEL "\e[1;33m"
#define BLU "\e[1;34m"
#define MAG "\e[1;35m"
#define CYN "\e[1;36m"
#define WHT "\e[1;37m"
#define NC	"\e[0m"

#define CAPY "\n  \
\e[1;32m                  ⢀⡀                     \n \
	           ⣶⠛⢻         ⣠⣤⡀     \e[1;33m     ⢀⣀⣀⣀⣀⡀    \e[1;32m   \n \
	           ⢻⣄⣼⡦⠴⠒⠒⠶⣤⣀ ⣾⢧⡋⡇     \e[1;33m   ⡤⣚⡍    ⢩⣓⢤  \e[1;32m   \n \
	       ⣀⡤⠶⠚⠉⠁       ⠈⣿⣷⣋⡿⠃     \e[1;33m ⢀⣞⣼⣿⣿⣆  ⣰⣿⣿⣧⣳⡀\e[1;32m   \n \
	   ⢀⡤⠖⠋⠁         \e[1;33m⢀⣶⣶⣦ \e[1;32m⠈⠻⠻⣆     \e[1;33m ⢸⢸⣿⣿⣿⣟⣴⣦⣻⣿⣿⣿⡇⡇\e[1;32m   \n \
	⢀⡠⠞⠃    ⣀        \e[1;33m⠘⣿\e[1;31m⣿\e[1;33m⣿⡇\e[1;32m ⡀⠙⣇     \e[1;33m ⢸    ⠈⣻⣟⠁    ⡇\e[1;32m   \n \
	⡞⠁    ⢀⡴⠃        \e[1;33m ⠛⠛⠟ \e[1;32m ⠙ ⠸⣆    \e[1;33m ⠈⢧  ⢀⣾⣿⣿⣷⡀  ⡼⠁\e[1;32m   \n \
	⡿⣤⡀ ⢀⡴⠋             ⢀⡀    ⠘⣆   \e[1;33m   ⠓⢤⣺⠿⠿⠿⠿⣗⡤⠞⠁ \e[1;32m   \n \
	⡇ ⠉⠉⠉         ⡀      ⠳⣄  ⡀ ⠈⢳⡀ \e[1;33m     ⠈⠉⠉⠉⠉⠁    \e[1;32m   \n \
	⢹⡀ ⢸          ⢈⣷⣄        ⠙⢦⡀ ⠙⢦⡀                \n \
	⠘⣇ ⠘⣆       ⢀⣴⠞ ⠹⠆  ⠈⢳     ⠁   ⠉⠳⠤⣀             \n \
	 ⠘⢦⣤⣹⣄⣀⣀⣀⣠⣤⠴⠊        ⠈⠃    ⠲⣤⡀    ⠈⠙⠲⢤⡀         \n \
	      ⠙⠲⢤⡀      ⢀      ⢰⡄    ⠁    ⠈⠑⠢⣄⡙⠷⣄       \n \
	        ⠈⡇  ⡀   ⢸⡇     ⢸⡇           ⡀⠈  ⠈⠳⣄     \n \
	         ⣻  ⢳   ⠘⠃                  ⠈⠢⡀ ⠑⢄⠙⢆    \n \
	         ⢸⡇ ⠈⠂    ⢠⣿      ⢀⣤⠴⠚⠃  ⠘⢢⡀  ⠉  ⠈⠧⠘⢧   \n \
	         ⢈⡇       ⠘⠋     ⣴⠋        ⠙⢦⡀ ⢦    ⠈⣇  \n \
	         ⠈⢹ ⢰⢀          ⣴⠁          ⠈⠁ ⠈⢳⡀   ⠸⡆ \n \
	          ⢸ ⠘⠷     ⢠   ⠠⡏  ⢠     ⢠⡀   ⡀  ⠷ ⢸⡄ ⢳ \n \
	          ⠈⡇    ⡄  ⢸⡇  ⢸⣧  ⠈⢣    ⢀⣳   ⢹⡄   ⠈⠁ ⢸ \n \
	           ⠻⡄   ⣷  ⠘⠃  ⢀⣿⡀        ⠉⠁  ⠸⢳⡀⢀⡀ ⢠ ⢸ \n \
	            ⠹⣄  ⢻⡇     ⣸⠉⢧⡀            ⠘ ⠐⣧ ⠸ ⡼ \n \
	            ⢀⣿⣦⡀⣸⣷     ⡇ ⠈⠳⡄              ⠁  ⢸⠇ \n \
	           ⣴⣖⡿⣿⡟⣻⣿⣷⡄  ⢾⣁⡀  ⣨⡷⣄              ⢠⠏  \n \
	           ⠿⠷⠿⣿⣥⠟ ⣹⣾⠦⡿⡾⠇⠉⢻⣟⣀⣀⡬⠟⠲⢤⣀⣀⣀⣀    ⢀⣀⡴⠋   \n \
	              ⠋⠁⢰⣿⡽⢛⡧⢠⡇   ⠉⠉⠙⠓⠒⠒⠚⠉⠁ ⠉⠑⠒⠒⠉⠉⠁     \n \
	               ⠘⠛⠒⣿⣤⠞                          \n \
	\e[6;3;4;31m WELCOME TO OUR INSANE RADIOACTIVE CAPYBARA SERVER \e[0m \n \
	     \e[1mUSE COMMAND `HELP` TO GET COMMAND LIST\e[0m\n🦛> "

//--------------------Defines-----------------

#define MAX_EVENTS	1024
#define MAX_BUF	500


#endif
