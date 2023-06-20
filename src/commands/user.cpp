#include "IRC.hpp"

void	Server::user(std::istringstream &content, int fd)
{
	std::string	str;

	if (this->_clients[fd]->getStatus() != pendingUsername)
	{
		if (this->_clients[fd]->getStatus() == pendingPassword)
			clientLog(fd, ERR_LOGIN);
		else
			clientLog(fd, ERR_ALRDY_REGIS);
		return ;
	}
	content >> str;
	if (str.empty())
	{
		clientLog(fd, ERR_USER);
		return ;
	}
	this->_clients[fd]->setNick(str);
	str.clear();
	content >> str;
	if (str.empty())
	{
		clientLog(fd, ERR_USER);
		return ;
	}
	this->_clients[fd]->setUser(str);
	str.clear();
	content >> str;
	if (!str.empty())
	{
		clientLog(fd, ERR_USER);
		return ;
	}
	this->_clients[fd]->setStatusUser(registered);
	clientLog(fd, CLOG_REGIS);
	log(fd, "registered");
}