#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "IRC.hpp"

class Client
{
	private :
		struct	sockaddr_in	_addr;
		int		_fd;
		std::string	_nick;
		std::string	_user;

		Client(void);
	public :
		struct sockaddr_in	getAddr(void) const;
		int	getFd(void) const;
		void	setFd(int fd);

		Client(int fd);
		Client(const Client &copy);
		~Client(void);
		Client	&operator=(Client const &rhs);
};

#endif
