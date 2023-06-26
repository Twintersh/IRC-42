#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "IRC.hpp"

class Client
{
	private :
		enum status			_status;
		struct	sockaddr_in	_addr;
		int					_fd;
		std::string			_nick;
		std::string			_curCmd;
		std::string			_color;
		std::string			_user;
		std::string			_hostName;
		std::string			_serverName;
		std::string			_realName;

		void				setColor(void);

	public :
		struct sockaddr_in	getAddr(void) const;
		int					getFd(void) const;
		std::string			getNick(void) const;
		std::string			getCNick(void) const;
		std::string			getUser(void) const;
		std::string			getCmd(void) const;
		enum status			getStatus(void) const;
		bool				setStatusUser(enum status status);
		void				setFd(int fd);
		void				setNick(std::string nick);
		void				setUser(std::string user);
		void				setServerName(std::string serverName);
		void				setHostName(std::string hostName);
		void				setRealName(std::string realName);
		void				joinCmd(std::string &join);
		void				clearCmd(void);

		Client(void);
		Client(int fd);
		Client(const Client &copy);
		~Client(void);
		Client	&operator=(Client const &rhs);
};

#endif
