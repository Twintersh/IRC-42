#include "IRC.hpp"

void Server::nick(std::istringstream &content, int fd)
{
	std::string nick;

	content >> nick;
	enum status status = this->_clients[fd]->getStatus();
	if (nick.empty() || !checkEmpty(content))	
		return (clientLog(fd, ERR_NICK));
	if (findFdByClientNick(nick) != -1)
		return (clientLog(fd, ERR_NICK_TAKEN));
	if (status != pendingNickname)
	{
		if (status == pendingPassword)
			clientLog(fd, ERR_PEND_PASS);
		else if (status == pendingUsername)
			clientLog(fd, ERR_ALRDY_NICK);
		else
			clientLog(fd, ERR_ALRDY_REGIS);
		return ;
	}
	clientLog(fd, LOG_NICK);
	this->_clients[fd]->setNick(nick);
	this->_clients[fd]->setStatusUser(pendingUsername);
}