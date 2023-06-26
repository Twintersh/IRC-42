#include "Client.hpp"

//Setter / getter

struct sockaddr_in	Client::getAddr(void) const {return this->_addr;}

int	Client::getFd(void) const{return (this->_fd);}

std::string	Client::getNick(void) const {return this->_nick;}

std::string	Client::getUser(void) const {return this->_user;}

enum status	Client::getStatus(void) const {return this->_status;}

std::string Client::getCmd(void) const {return this->_curCmd;}

std::string	Client::getCNick(void) const { return (this->_color + this->_nick + NC);}

void Client::joinCmd(std::string &join) {this->_curCmd += join;}

void Client::clearCmd(void) {this->_curCmd.clear();}

void	Client::setNick(std::string nick) {this->_nick = nick;}

void	Client::setFd(int fd) {this->_fd = fd;}

void	Client::setUser(std::string user) {this->_user = user;}

void	Client::setServerName(std::string serverName) {this->_serverName = serverName;}

void	Client::setHostName(std::string hostName) {this->_hostName = hostName;}

void	Client::setRealName(std::string realName) {this->_realName = realName;}

void Client::setColor(void)
{
	srand(time(NULL));
	std::string color[] = {RED, GRN, YEL, BLU, MAG, CYN};
	this->_color = color[rand() % 6];
}



bool	Client::setStatusUser(status newStatus){
	if (newStatus == _status + 1)
		_status = newStatus;
	else
		return (false);
	return (true);
}

// constructors / destructors

Client::Client(int fd): _status(pendingPassword), _fd(fd), _nick(), _user()
{
	setColor();
	return;
}

Client::Client( void ): _status(pendingPassword), _fd(), _nick(), _user()
{
	setColor();
	return;
}

Client::Client( Client const &copy)
{
	*this = copy;
}

Client  &Client::operator=( Client const &rhs)
{
	if (this == &rhs)
		return *this;
	setColor();
	this->_fd = rhs._fd;
	this->_addr = rhs.getAddr();
	return *this;
}

Client::~Client( void )
{
	return;
}
