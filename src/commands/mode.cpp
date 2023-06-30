#include "IRC.hpp"

bool isNumber(const char *str)
{
	for (int i = 0 ; str[i] ; i++)
		if (!isdigit(str[i]))
			return (false);
	return (true);
}

void	Server::limitUserChannel(std::string chName, int limit, int fd, char sign)
{
	if (sign == '-')
		this->_channels[chName]->setUserLimit(0);
	else
		this->_channels[chName]->setUserLimit(limit);
	clientLog(fd, CLOG_LIMIT);
	log(fd, LOG_LIMIT + chName);
}

void	Server::operatorPriv(std::string chName, std::string nick, int fd, char sign)
{
	if (nick.empty())
		return (clientLog(fd, ERR_MODE));

	int nickFd = findFdByClientNick(nick);
	if (nickFd == -1)
		return (clientLog(fd, ERR_USR_NOT_FND));

	if (!this->_channels[chName]->isMember(nickFd))
		return (clientLog(fd, ERR_USRN_MEM));
	
	if (sign == '+')
	{
		if (this->_channels[chName]->isOp(nickFd))
			return (clientLog(fd, ERR_USRA_OP));
		
		this->_channels[chName]->addOp(this->_clients[nickFd]);
		log(*this->_clients[fd], LOG_GRAN_OP + nick);
		clientLog(fd, CLOG_GRAN_OP + nick);
	}
	else
	{
		if (!this->_channels[chName]->isOp(nickFd))
			return (clientLog(fd, ERR_USRN_OP));

		this->_channels[chName]->removeOp(nickFd);
		log(*this->_clients[fd], LOG_REV_OP + nick);
		clientLog(fd, CLOG_REV_OP + nick);
	}
}

void	Server::passwordChange(std::string chName, std::string pass, int fd, char sign)
{
	if (sign == '-')
	{
		this->_channels[chName]->setPassword("");
		log(*this->_clients[fd], LOG_PASS_REM + chName);
		clientLog(fd, CLOG_PASS_REM + chName);
	}
	else
	{
		if (pass.empty())
			return (clientLog(fd, ERR_MODE));
		this->_channels[chName]->setPassword(pass);
		log(*this->_clients[fd], LOG_PASS_CHG + chName);
		clientLog(fd, CLOG_PASS_CHG + chName);
	}
}

void	Server::mode(std::istringstream &content, int fd)
{
	std::string	chName;
	std::string	mode;
	std::string arg;
	char		sign;

	content >> chName;
	content >> mode;
	if (chName.empty() || mode.empty() || (mode[0] != '-' && mode[0] != '+'))
		return (clientLog(fd, ERR_MODE));
	if (this->_channels.find(chName) == this->_channels.end())
		return (clientLog(fd, ERR_UNKWN_CH));
	if (!this->_channels[chName]->isOp(fd))
		return (clientLog(fd, ERR_NOT_OP));
	for (unsigned int i = 0 ; i < mode.length() ; i++)
	{
		if (mode[i] == '+' || mode[i] == '-')
		{
			sign = mode[i];
			continue ;
		}
		switch (mode[i])
		{
			case('i'):
				this->_channels[chName]->setInviteMode(sign == '+');
				break;
			case('t'):
				this->_channels[chName]->setTopicRightsMode(sign == '+');
				break;
			case('k'):
				if (sign == '+')
					content >> arg;
				passwordChange(chName, arg, fd, sign);
				break;
			case('o'):
				content >> arg;
				operatorPriv(chName, arg, fd, sign);
				break;
			case('l'):
				if (sign != '-')
					content >> arg;
				if (isNumber(arg.c_str()) || sign == '-')
					limitUserChannel(chName, std::atoi(arg.c_str()), fd, sign);
				else
					clientLog(fd, ERR_MODE_LIMIT);
				break;
			default:
				clientLog(fd, ERR_MODE);
				break;
		}
	}
}
