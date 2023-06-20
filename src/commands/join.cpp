#include "IRC.hpp"

void	Server::join(std::istringstream &content, int fd)
{
	std::string	chName;

	content >> chName;
	if (chName.empty())
		return (clientLog(fd, ERR_JOIN));

	if (chName[0] != '#' && chName[0] != '&')
		return (clientLog(fd, ERR_CH_NAME));

	if (this->_channels.find(chName) == this->_channels.end())
	{
		if (content.gcount() > 0)
			return (clientLog(fd, ERR_JOIN));
		this->_channels.insert(std::pair<std::string, Channel *>(chName, new Channel(chName, this->_clients[fd])));
		return (clientLog(fd, CLOG_CRT_CH));
	}
	else
	{
		if (this->_channels[chName]->getInviteMode() && !this->_channels[chName]->isInvited(fd))
			return (clientLog(fd, ERR_REQ_INVIT));

		if (!this->_channels[chName]->getPassword().empty())
		{
			std::string	password;
			content >> password;
			if (password.empty())
				return (clientLog(fd, ERR_REQ_PASS));
			if (password != this->_channels[chName]->getPassword())
				return (clientLog(fd, ERR_WRNG_PASS));
		}
		if (this->_channels[chName]->getUserLimit() > 0
		&& this->_channels[chName]->getConnectedUser() >= (this->_channels[chName]->getUserLimit()))
			return (clientLog(fd, ERR_CH_FULL));
			
		this->_channels[chName]->joinChannel(this->_clients[fd]);
		clientLog(fd, CLOG_JOIN_CH);
		log(*this->_clients[fd], LOG_JOIN + this->_channels[chName]->getName());
	}
}
