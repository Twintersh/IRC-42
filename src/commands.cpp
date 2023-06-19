#include "IRC.hpp"

void Server::privmsg(std::istringstream &content, int fd)
{
	std::string dest;
	std::string txt;
	std::string msg = "from [";

	content >> dest;
	getline(content, txt, '\0');
	if (dest[0] == '#' || dest[0] == '&')
	{
		vIt_Channel channel = this->_channels.find(dest);
		if (channel == this->_channels.end()){
			clientLog(fd, ERR_CHN_NOT_FND);
			return;
		}
		if (channel->second->isMember(fd))
		{
			msg += this->_clients[fd]->getNick() + "] in <" + channel->second->getName() + ">:" + txt;
			channel->second->sendChannel(msg, fd);
			log(*this->_clients[fd], LOG_MSG_CHANNEL);
		}
		else
			clientLog(fd, ERR_NOT_MEM);
	}
	else
	{
		int destFd = findFdByClientNick(dest);
		if (destFd == -1){
			clientLog(fd, ERR_USR_NOT_FND);
			return;
		}
		msg += this->_clients[fd]->getNick() + "]:" + txt;
		send(destFd, msg.c_str(), msg.length(), 0);
		log(*this->_clients[fd], LOG_MSG_CLIENT);
	}
}	

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

void	Server::join(std::istringstream &content, int fd)
{
	std::string	chName;

	content >> chName;
	if (chName.empty())
	{
		clientLog(fd, ERR_JOIN);
		return ;
	}
	if (this->_channels.find(chName) == this->_channels.end())
	{
		if (content.gcount() > 0)
		{
			clientLog(fd, ERR_JOIN);
			return ;
		}
		if (chName.at(0) != '&' && chName.at(0) != '#')
			chName.insert(0, 1, '#');
		this->_channels.insert(std::pair<std::string, Channel *>(chName, new Channel(chName, this->_clients[fd])));
		clientLog(fd, CLOG_CRT_CH);
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

void	Server::part(std::istringstream &content, int fd)
{
	std::string	chName;

	content >> chName;
	if (chName.empty() || content.gcount() > 0)
	{
		clientLog(fd, ERR_PART);
		return ;
	}
	if (this->_channels.find(chName) == this->_channels.end())
	{
		clientLog(fd, ERR_UNKWN_CH + chName);
		return ;
	}
	if (this->_channels[chName]->isOp(fd))
	{
		clientLog(fd, ERR_OP_LEAVER);
		return ;
	}
	if (!this->_channels[chName]->isMember(fd))
	{
		clientLog(fd, ERR_NOT_MEMBER);
		return ;
	}
	this->_channels[chName]->leaveChannel(fd);
	clientLog(fd, CLOG_LEFT_CH);
}