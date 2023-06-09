#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "IRC.hpp"
#include "Server.hpp"

class Client
{
	private :
		struct	sockaddr_in	_addr;
		int		_fd;

		Client(void);
	public :
		struct sockaddr_in	getAddr(void) const;
		int		getFd(void) const;
		void	setFd(int fd);

		Client(int fd);
		Client(const Client &copy);
		~Client(void);
		Client	&operator=(Client const &rhs);
};

#endif
