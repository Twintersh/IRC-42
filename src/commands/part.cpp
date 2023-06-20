#include "IRC.hpp"

void	Server::part(std::istringstream &content, int fd)
{
	std::string	chName;

	content >> chName;
	if (chName.empty() || content.gcount() > 0)
		return (clientLog(fd, ERR_PART));

	if (this->_channels.find(chName) == this->_channels.end())
		return (clientLog(fd, ERR_UNKWN_CH + chName));

	if (this->_channels[chName]->isOp(fd))
		return (clientLog(fd, ERR_OP_LEAVER));

	if (!this->_channels[chName]->isMember(fd))
		return (clientLog(fd, ERR_NOT_MEMBER));

	this->_channels[chName]->leaveChannel(fd);
	clientLog(fd, CLOG_LEFT_CH);
}