#include "IRC.hpp"

void	Server::join(std::istringstream &content, int fd)
{
	std::string	chName;

	content >> chName;
	if (chName.empty())
	{
		clientLog(fd, ERR_JOIN);
		return ;
	}
	if (chName[0] != '#' && chName[0] != '&')
	{
		clientLog(fd, ERR_CH_NAME);
		return ;
	}
	if (this->_channels.find(chName) == this->_channels.end())
	{
		if (content.gcount() > 0)
		{
			clientLog(fd, ERR_JOIN);
			return ;
		}
		this->_channels.insert(std::pair<std::string, Channel *>(chName, new Channel(chName, this->_clients[fd])));
		clientLog(fd, CLOG_CRT_CH);
		log(*this->_clients[fd], LOG_NEW_CHANNEL + chName);
	}
	else
	{
		if (this->_channels[chName]->getInviteMode() && !this->_channels[chName]->isInvited(fd))
		{
			clientLog(fd, ERR_REQ_INVIT);
			return ;
		}
		if (!this->_channels[chName]->getPassword().empty())
		{
			std::string	password;
			content >> password;
			if (password.empty())
			{
				clientLog(fd, ERR_REQ_PASS);
				return ;
			}
			if (password != this->_channels[chName]->getPassword())
			{
				clientLog(fd, ERR_WRNG_PASS);
				return ;
			}
		}
		if (this->_channels[chName]->getUserLimit() > 0
		&& this->_channels[chName]->getConnectedUser() >= (this->_channels[chName]->getUserLimit()))
		{
			clientLog(fd, ERR_CH_FULL);
			return ;
		}
		this->_channels[chName]->joinChannel(this->_clients[fd]);
		clientLog(fd, CLOG_JOIN_CH);
		log(*this->_clients[fd], LOG_JOIN + this->_channels[chName]->getName());
	}
}
