#include "IRC.hpp"

void	Server::invite(std::istringstream &content, int fd)
{
	std::string	username;
	std::string	channelName;
	vIt_Channel	channelIt;
	int			clientFd;

	content >> username >> channelName;
	if (username.empty() || channelName.empty() || content.gcount() > 0)
	{
		clientLog(fd, ERR_INVITE);
		return;
	}
	channelIt = this->_channels.find(channelName);
	clientFd = findFdByClientNick(username);
	if (channelIt == this->_channels.end() || clientFd == -1)
	{
		if (channelIt == this->_channels.end())
			clientLog(fd, ERR_UNKWN_CH);
		if (clientFd == -1)
			clientLog(fd, ERR_USR_NOT_FND);
		return;
	}
	if (!channelIt->second->isMember(fd))
	{
		clientLog(fd, ERR_NOT_MEMBER);
		return;
	}
	if (!channelIt->second->getUserLimit() ||
		channelIt->second->getConnectedUser() < channelIt->second->getUserLimit())
	{
		channelIt->second->inviteClient(this->_clients[clientFd]);
		clientLog(clientFd, CLOG_INVITED + channelIt->second->getName());
		clientLog(fd, CLOG_INVT_SUCC);
		log(fd, LOG_INVIT + channelIt->second->getName());
	}
	else
		clientLog(fd, ERR_CH_FULL);
}