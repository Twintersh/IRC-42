#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "IRC.hpp"

class	Client;

class Channel
{
	private :
		bool				_inviteOnly;
		bool				_topicRights;
		int					_userLimit;
		std::string			_name;
		std::string			_topic;
		std::string			_password;
		std::map<int, Client *>	_operators;
		std::map<int, Client *>	_members;
		std::map<int, Client *>	_invited;

		Channel( void );
	public :
		bool		getInviteMode(void) const;
		bool		getTopicRights(void) const;
		int			getUserLimit(void) const;
		int			getConnectedUser(void) const;
		std::string	getName(void) const;
		std::string	getTopic(void) const;
		std::string	getPassword(void) const;
		void		setInviteMode(bool mode);
		void		setTopicRightsMode(bool mode);
		void		setUserLimit(int limit);
		void		setName(std::string name);
		void		setPassword(std::string password);
		void		setTopic(std::string topic);

		bool		isOp(const Client &check);
		bool		isMember(const Client &check);

		void		joinChannel(Client *newClient);


		Channel(const std::string &name, Client *op);
		Channel( Channel const &copy );
		~Channel( void );
		Channel	&operator=( Channel const &rhs );
};

#endif
