#ifndef SERVER_HPP
# define SERVER_HPP

#include "Client.hpp"
#include "IRC.hpp"

class Server
{
	private:
		int					_fd;
		int					_epfd;
		socklen_t			_addrLen;
		struct sockaddr_in	_addr;
		struct epoll_event	_ev;
		std::vector<Client>	_clients;
		const std::string	_password;

	private:
		bool	addPoll(int fd);
		void	newClient(void);
		void	readStdin(void);
		void	parseRequest(int fd);

		Server( void );

	public:
		void	startServer(void);

		Server(const int port, const std::string password);
		Server(const Server& copy);
		~Server();
		Server& operator=(const Server& rhs);
};

#endif

