#include "IRC.hpp"

void Server::pass(std::istringstream &content, int fd)
{
	std::string password;

	content >> password;
	if (content.gcount() > 0)
		clientLog(fd, ERR_PASS);
	else if (this->_clients[fd]->getStatus() != pendingPassword)
		clientLog(fd, ERR_ALRDY_LOG);
	else if (password == this->_password)
	{
		if (this->_clients[fd]->setStatusUser(pendingUsername))
		{
			log(fd, LOG_LOGIN);
			clientLog(fd, CLOG_PASS);
		}
	}
	else
		clientLog(fd, ERR_BAD_PASS);
}
