#include "IRC.hpp"

void Server::privmsg(std::istringstream &content, int fd)
{
	std::string dest;
	std::string txt;
	std::string msg = "from [";

	content >> dest;
	getline(content, txt, '\0');
	if (dest.empty() || txt.empty())
	{
		clientLog(fd, ERR_PRIVMSG);
		return
	}
	if (dest[0] == '#' || dest[0] == '&')
	{
		vIt_Channel channel = this->_channels.find(dest);
		if (channel == this->_channels.end()){
			clientLog(fd, ERR_UNKWN_CH);
			return;
		}
		if (channel->second->isMember(fd))
		{
			msg += this->_clients[fd]->getCNick() + "] in <" + channel->second->getName() + ">:" + txt;
			channel->second->sendChannel(msg, fd);
			log(*this->_clients[fd], LOG_MSG_CHANNEL + channel->second->getName());
		}
		else
			clientLog(fd, ERR_NOT_MEMBER);
	}
	else
	{
		int destFd = findFdByClientNick(dest);
		if (destFd == -1){
			clientLog(fd, ERR_USR_NOT_FND);
			return;
		}
		msg += this->_clients[fd]->getCNick() + "]:" + txt;
		send(destFd, msg.c_str(), msg.length(), 0);
		log(*this->_clients[fd], LOG_MSG_CLIENT + this->_clients[fd]->getFd());
	}
}	
