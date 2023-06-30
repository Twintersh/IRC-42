#include "IRC.hpp"

void Server::privmsg(std::istringstream &content, int fd)
{
	std::string dest;
	std::string txt;
	std::string msg = "\nfrom [";

	content >> dest;
	getline(content, txt, '\0');
	if (dest.empty() || txt.empty())
		return (clientLog(fd, ERR_PRIVMSG));
	if (dest[0] == '#' || dest[0] == '&')
	{
		vIt_Channel channel = this->_channels.find(dest);
		if (channel == this->_channels.end())
			return (clientLog(fd, ERR_UNKWN_CH));
		if (channel->second->isMember(fd))
		{
			msg += this->_clients[fd]->getCNick() + "] in <" + channel->second->getCName() + ">:" + txt + "\n🦛> ";
			channel->second->sendChannel(msg, fd);
			log(*this->_clients[fd], LOG_MSG_CHANNEL + channel->second->getCName());
		}
		else
			return (clientLog(fd, ERR_NOT_MEMBER));
	}
	else
	{
		int destFd = findFdByClientNick(dest);
		if (destFd == fd)
			return (clientLog(fd, ERR_ALONE));
		if (destFd == -1 || this->_clients[destFd]->getStatus() != registered)
			return (clientLog(fd, ERR_USR_NOT_FND));
		msg += this->_clients[fd]->getCNick() + "]:" + txt + "\r\n";
		this->_clients[destFd]->clearCmd();
		send(destFd, msg.c_str(), msg.length(), 0);
		log(*this->_clients[fd], LOG_MSG_CLIENT + this->_clients[fd]->getNick());
	}
}	
