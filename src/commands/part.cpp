#include "IRC.hpp"

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