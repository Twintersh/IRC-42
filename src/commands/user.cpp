#include "IRC.hpp"

void	Server::user(std::istringstream &content, int fd)
{
	std::string	nick;
	std::string	user;

	if (this->_clients[fd]->getStatus() != pendingUsername)
	{
		if (this->_clients[fd]->getStatus() == pendingPassword)
			clientLog(fd, ERR_LOGIN);
		else
			clientLog(fd, ERR_ALRDY_REGIS);
		return ;
	}
	content >> nick;
	content >> user;
	if (nick.empty() || user.empty() || content.gcount() > 0) 
		return (clientLog(fd, ERR_USER));
	if (findFdByClientNick(nick) != -1)
		return (clientLog(fd, ERR_NICK_TAKEN));
	this->_clients[fd]->setNick(nick);
	this->_clients[fd]->setUser(user);
	this->_clients[fd]->setStatusUser(registered);
	clientLog(fd, CLOG_REGIS);
	log(fd, "registered");
}