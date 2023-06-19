#ifndef SERVER_HPP
# define SERVER_HPP

#include "IRC.hpp"

class	Client;
class	Channel;

class Server
{
	private:
		int									_fd;
		int									_epfd;
		socklen_t							_addrLen;
		struct sockaddr_in					_addr;
		struct epoll_event					_ev;
		std::map<int, Client *>				_clients;
		std::map<std::string, Channel *>	_channels;
		const std::string					_password;

	private:
		//main functions
		void			newClient(void);
		void			killClient(struct epoll_event &curEv);
		void			readStdin(void);

		//parsing
		void			parseRequest(struct epoll_event &curEv);
		void			parseMsg(int fd, std::istringstream &msg);

		//commands
		void			join(std::istringstream &content, int fd);
		void			pass(std::istringstream &content, int fd);
		// void 			prvmsg(std::istringstream &content, Client current);
		void 			user(std::istringstream &content, int fd);

		//utils
		void			clientError(int fd, std::string err);
		bool			addPoll(int fd);

		Server(void);

	public:
		void			log(Client client, std::string msgLog);
		void			startServer(void);

		Server(const int port, const std::string password);
		Server(const Server& copy);
		~Server();
		Server& operator=(const Server& rhs);
};

#endif

