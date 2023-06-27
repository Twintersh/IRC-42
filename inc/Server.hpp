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

		bool								checkEmpty(std::istringstream &content);
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
		void 			privmsg(std::istringstream &content, int fd);
		void			part(std::istringstream &content, int fd);
		void 			user(std::istringstream &content, int fd);
		void			kick(std::istringstream &content, int fd);
		void			invite(std::istringstream &content, int fd);
		void			topic(std::istringstream &content, int fd);
		void			mode(std::istringstream &content, int fd);
		void			nick(std::istringstream &content, int fd);
		void			help(std::istringstream &content, int fd);

		// mode utils
		void			limitUserChannel(std::string chName, int limit, int fd, char sign);
		void			passwordChange(std::string chName, std::string pass, int fd, char sign);
		void			operatorPriv(std::string chName, std::string user, int fd, char sign);

		//utils
		void			log(Client client, std::string msgLog);
		void			clientLog(int fd, std::string str);
		int				findFdByClientNick(std::string &name);
		bool			addPoll(int fd);

		Server(void);
	public:
		void			startServer(void);

		Server(const int port, const std::string password);
		Server(const Server& copy);
		~Server();
		Server& operator=(const Server& rhs);
};

#endif

