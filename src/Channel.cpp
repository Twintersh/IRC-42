#include "Channel.hpp"

//Main fucntions
void	Channel::joinChannel(Client *newClient)
{
	if (this->_inviteOnly)
		this->_invited.erase(newClient->getFd());
	this->_members.insert(std::pair<int, Client *>(newClient->getFd(), newClient));
	return ;
}

void Channel::setColor(void)
{
	srand(time(NULL));
	std::string color[] = {RED, GRN, YEL, BLU, MAG, CYN};
	this->_color = "\e[3;4m" + color[rand() % 6];
}

void Channel::inviteClient(Client *newClient)
{
	if (this->_invited.find(newClient->getFd()) == this->_invited.end())
		this->_invited.insert(std::pair<int, Client *>(newClient->getFd(), newClient));
}

void	Channel::leaveChannel(int fd)
{
	this->_members.erase(fd);
	return ;
}

void	Channel::addOp(Client *newOp)
{
	this->_operators.insert(std::pair<int, Client *>(newOp->getFd(), newOp));
}

void	Channel::removeOp(int fd)
{
	this->_operators.erase(fd);
}

void	Channel::removeUser(int fd)
{
	if (this->_members.find(fd) != this->_members.end())
		this->_members.erase(fd);
	if (this->_operators.find(fd) != this->_operators.end())
		this->_operators.erase(fd);
	if (this->_invited.find(fd) != this->_invited.end())
		this->_invited.erase(fd);
}

bool		Channel::isMember(int fd)
{
	if (this->_members.find(fd) == this->_members.end())
		return false;
	return true;
}

bool		Channel::isOp(int fd)
{
	if (this->_operators.find(fd) == this->_operators.end())
		return false;
	return true;
}

bool		Channel::isInvited(int fd)
{
	if (this->_invited.find(fd) == this->_invited.end())
		return false;
	return true;
}

void Channel::sendChannel(std::string &msg, int fd)
{
	for (vIt_Client it = _members.begin() ; it != _members.end() ; it++) 
	{
		if (it->first != fd)
		{
			it->second->clearCmd();
			send(it->first, msg.c_str(), msg.length(), 0);
		}
	}
}


//Getters / Setters


bool		Channel::getInviteMode(void) const {return this->_inviteOnly;}

bool		Channel::getTopicRights(void) const {return this->_topicRights;}

int			Channel::getUserLimit(void) const {return this->_userLimit;}

int			Channel::getConnectedUser(void) const {return this->_members.size();}

std::string	Channel::getName(void) const {return this->_name;}

std::string Channel::getCName(void) const {
	return (_color + this->_name + NC);
}

std::string	Channel::getTopic(void) const {return this->_topic;}

std::string	Channel::getPassword(void) const {return this->_password;}

void		Channel::setInviteMode(bool mode) {this->_inviteOnly = mode;}

void		Channel::setTopicRightsMode(bool mode) {this->_topicRights = mode;}

void		Channel::setUserLimit(int limit) {this->_userLimit = limit;}

void		Channel::setName(std::string name) {this->_name = name;}

void		Channel::setPassword(std::string password) {this->_password = password;}

void		Channel::setTopic(std::string topic) {this->_topic = topic;}

// Constructors / Destructors

Channel::Channel( void ): _inviteOnly(false), _topicRights(false), _userLimit(0), _name(), 
_topic(),  _password()
{
	setColor();
	return ;
}

Channel::Channel( const std::string &name, Client *op): _inviteOnly(false),
_topicRights(false), _userLimit(0),_name(name), _topic(), _password()
{
	setColor();
	this->_operators.insert(std::pair<int, Client *>(op->getFd(), op));
	this->_members.insert(std::pair<int, Client *>(op->getFd(), op));
	return ;
}

Channel::Channel( Channel const &copy)
{
	*this = copy;
}

Channel  &Channel::operator=( Channel const &rhs)
{
	if (this == &rhs)
		return *this;
	setColor();
	this->_name = rhs._name;
	this->_topic = rhs._topic;
	this->_password = rhs._password;
	this->_inviteOnly = rhs._inviteOnly;
	this->_topicRights = rhs._topicRights;
	this->_userLimit = rhs._userLimit;
	this->_members = std::map<int, Client *>(rhs._members);
	this->_operators = std::map<int, Client *>(rhs._operators);
	return *this;
}

Channel::~Channel( void )
{
	return ;
}
