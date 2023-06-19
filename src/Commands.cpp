#include "IRC.hpp"


void Server::pass(std::istringstream &content, int fd)
{
	std::string password;

	content >> password;
	if (content.gcount() > 0)
		clientError(this->_clients[fd]->getFd(), ERR_PASS);
	else if (this->_clients[fd]->getStatus() != pendingPassword)
		Server::clientError(this->_clients[fd]->getFd(), ERR_ALRDY_LOG);
	else if (password == this->_password)
	{
		if (this->_clients[fd]->setStatusUser(pendingUsername))
			Server::log(this->_clients[fd]->getFd(), LOG_LOGIN);
	}
	else
		Server::clientError(this->_clients[fd]->getFd(), ERR_BAD_PASS);
}
	
void	Server::user(std::istringstream &content, int fd)
{
	std::string	str;

	if (this->_clients[fd]->getStatus() != pendingUsername)
	{
		if (this->_clients[fd]->getStatus() == pendingPassword)
			clientError(this->_clients[fd]->getFd(), ERR_LOGIN);
		else
			clientError(this->_clients[fd]->getFd(), ERR_ALRDY_REGIS);
		return ;
	}
	content >> str;
	if (str.empty())
	{
		clientError(this->_clients[fd]->getFd(), ERR_USER);
		return ;
	}
	this->_clients[fd]->setNick(str);
	str.clear();
	content >> str;
	if (str.empty())
	{
		clientError(this->_clients[fd]->getFd(), ERR_USER);
		return ;
	}
	this->_clients[fd]->setUser(str);
	str.clear();
	content >> str;
	if (!str.empty())
	{
		clientError(this->_clients[fd]->getFd(), ERR_USER);
		return ;
	}
	log(this->_clients[fd]->getFd(), "registered");
}

void	Server::join(std::istringstream &content, int fd)
{
	std::string	chName;

	content >> chName;
	if (chName.empty())
	{
		clientError(this->_clients[fd]->getFd(), ERR_JOIN);
		return ;
	}
	if (std::find(this->_channels.begin(), this->_channels.end(), chName) == this->_channels.end())
	{
		if (content.gcount() > 0)
		{
			clientError(this->_clients[fd]->getFd(), ERR_JOIN);
			return ;
		}
		if (chName.at(0) != '&' || chName.at(0) != '#')
			chName.insert(0, 1, '#');
		this->_channels.insert(std::pair<std::string, Channel *>(chName, new Channel(chName, this->_clients[fd])));
		log(*this->_clients[fd], LOG_NEW_CHANNEL + chName);
	}
	else
	{
		if (!this->_channels[chName]->getPassword().empty())
		{
			std::string	password;
			content >> password;
			if (password.empty())
			{
				clientError(fd, ERR_REQ_PASS);
				return ;
			}
			if (password != this->_channels[chName]->getPassword())
			{
				clientError(fd, ERR_WRNG_PASS);
				return ;
			}
		}
		if (this->_channels[chName]->getConnectedUser() >= (this->_channels[chName]->getUserLimit()))
		{
			clientError(fd, ERR_CH_FULL);
			return ;
		}
		this->_channels[chName]->joinChannel(this->_clients[fd]);	
		log(*this->_clients[fd], LOG_JOIN + this->_channels[chName]->getName());
	}
}