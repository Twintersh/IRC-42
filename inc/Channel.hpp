#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "IRC.hpp"

class Channel
{
	private :
		bool				_inviteOnly;
		bool				_topicRights;
		int					_userLimit;
		std::string			_topic;
		std::string			_password;
		std::vector<Client>	_operators;
		std::vector<Client>	_members;

	public :

	
		Channel( void );
		Channel( Channel const &copy );
		~Channel( void );
		Channel	&operator=( Channel const &rhs );
};

#endif
