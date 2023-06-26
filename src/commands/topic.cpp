#include "IRC.hpp"

void	printTopic(int fd, std::string topic)
{
	std::string	msg;

	msg = "Channel's Topic :";
	msg += topic;
	msg += '\n';
	send(fd, msg.c_str(), msg.size(), 0);
}

void	Server::topic(std::istringstream &content, int fd)
{
	std::string	chName;
	std::string	topic;

	content >> chName;
	content >> topic;
	if (chName.empty() || !checkEmpty(content))
	{
		clientLog(fd, ERR_TOPIC);
		return ;
	}
	if (this->_channels.find(chName) == this->_channels.end())
	{
		clientLog(fd, ERR_UNKWN_CH);
		return ;
	}
	if (!this->_channels[chName]->isMember(fd))
	{
		clientLog(fd, ERR_NOT_MEMBER);
		return ;
	}
	if (topic.empty())
	{
		if (this->_channels[chName]->getTopic().empty())
		{
			clientLog(fd, ERR_NO_TOPIC);
			return ;
		}
		printTopic(fd, this->_channels[chName]->getTopic());
		return ;
	}
	if (!this->_channels[chName]->getTopicRights() && !this->_channels[chName]->isOp(fd))
	{
		clientLog(fd, ERR_NOT_OP);
		return ;
	}
	this->_channels[chName]->setTopic(topic);
	clientLog(fd, CLOG_TOPIC_SET + topic);
}