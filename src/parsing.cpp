#include "IRC.hpp"

void	Server::parseMsg(int fd, std::istringstream &msg)
{
	std::string command;
	std::string messages[] = {"PASS", "USER", "NICK", "PRIVMSG", "JOIN", "PART", "INVITE", "TOPIC", "KICK", "MODE", "HELP"};
	enum status status = this->_clients[fd]->getStatus();
	int i;

	msg >> command;
	for (i = 0 ; i < 11 ; i++)
	{
		if (command == messages[i])
			break;
	}
	if (status != registered && !(i < 3 || i == 10))
	{
		if (status == pendingPassword)
			clientLog(fd, ERR_PEND_PASS);
		else if (status == pendingNickname)
			clientLog(fd, ERR_PEND_NICK);
		else
			clientLog(fd, ERR_PEND_REGIS);
		return ;
	}
	switch (i)
	{
		case (0):
			pass(msg, fd);
			break;
		case (1):
			user(msg, fd);
			break;
		case (2):
			nick(msg, fd);
			break;
		case (3):
			privmsg(msg, fd);
			break;
		case (4):
			join(msg, fd);
			break;
		case (5):
			part(msg, fd);
			break ;
		case (6):
			invite(msg, fd);
			break;
		case (7):
			topic(msg, fd);
			break ;
		case (8):
			kick(msg, fd);
			break ;
		case (9):
			mode(msg, fd);
			break ;
		case (10):
			help(msg, fd);
			break ;
		default : 
			clientLog(fd, ERR_CMD_NOT_FND);
	}
}