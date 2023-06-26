#include "IRC.hpp"

void	Server::user(std::istringstream &content, int fd)
{
	std::string	user;
	std::string	serverName;
	std::string	hostName;
	std::string	realName;

	enum status status = this->_clients[fd]->getStatus();
	if (status != pendingUsername)
	{
		if (status == pendingPassword)
			clientLog(fd, ERR_PEND_PASS);
		else if (status == pendingNickname)
			clientLog(fd, ERR_PEND_NICK);
		else
			clientLog(fd, ERR_ALRDY_REGIS);
		return ;
	}
	content >> user;
	content >> serverName;
	content >> hostName;
	content >> realName;
	if (user.empty() || serverName.empty() || hostName.empty() || realName.empty() || !checkEmpty(content)) 
		return (clientLog(fd, ERR_USER));
	this->_clients[fd]->setUser(user);
	this->_clients[fd]->setServerName(serverName);
	this->_clients[fd]->setHostName(hostName);
	this->_clients[fd]->setRealName(realName);
	this->_clients[fd]->setStatusUser(registered);
	clientLog(fd, CLOG_REGIS);
	log(fd, "registered");
}