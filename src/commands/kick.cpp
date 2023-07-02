#include "IRC.hpp"

static void	kickMessage(std::istringstream &content, const Client &op, int leaverFd, std::string chName)
{
	std::string	msg;
	std::string	reason;

	getline(content, reason, '\n');
	msg = "You have been kicked from channel ";
	msg += chName;
	msg += " by ";
	msg += op.getNick();
	msg += "\r\n";
	if (reason.empty())
	{
		send(leaverFd, msg.c_str(), msg.size(), 0);
		return ;
	}
	msg += ". Reason :";
	msg += reason;
	msg += "\r\n";
	send(leaverFd, msg.c_str(), msg.size(), 0);
}

void	Server::kick(std::istringstream &content, int fd)
{
	std::string	str[2];
	std::string	reason;
	int	nickFd;

	content >> str[0];
	content >> str[1];
	if (str[0].empty() || str[1].empty())
		return (clientLog(fd, ERR_KICK));

	if (this->_channels.find(str[0]) == this->_channels.end())
		return (clientLog(fd, ERR_UNKWN_CH));

	nickFd = findFdByClientNick(str[1]);
	if (nickFd == -1)
		return (clientLog(fd, ERR_USR_NOT_FND));

	if (!this->_channels[str[0]]->isMember(nickFd))
		return (clientLog(fd, ERR_USR_NO_MEM));

	if (!this->_channels[str[0]]->isOp(fd))
		return (clientLog(fd, ERR_NOT_OP));

	if (this->_channels[str[0]]->isOp(nickFd))
		return (clientLog(fd, ERR_KICK_OP));

	this->_channels[str[0]]->leaveChannel(nickFd);
	kickMessage(content, *this->_clients[fd], nickFd, str[0]);
	clientLog(fd, CLOG_KICK_USR + str[1]);
	log(*this->_clients[fd], LOG_KICK_CH);
}