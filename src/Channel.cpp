#include "Channel.hpp"

//Main fucntions
void	Channel::joinChannel(Client *newClient)
{
	if (this->_inviteOnly)
		this->_invited.erase(newClient->getFd());
	this->_members.insert(std::pair<int, Client *>(newClient->getFd(), newClient));
	return ;
}
//Getters / Setters

bool		Channel::getInviteMode(void) const {return this->_inviteOnly;}

bool		Channel::getTopicRights(void) const {return this->_topicRights;}

int			Channel::getUserLimit(void) const {return this->_userLimit;}

int			Channel::getConnectedUser(void) const {return this->_members.size() + this->_operators.size();}

std::string	Channel::getName(void) const {return this->_name;}

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
	return ;
}

Channel::Channel( const std::string &name, Client *op): _inviteOnly(false),
_topicRights(false), _userLimit(0),_name(name), _topic(), _password()
{
	this->_operators.insert(std::pair<int, Client *>(op->getFd(), op));
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
