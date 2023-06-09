#include "Server.hpp"

//main functions

void	Server::readStdin(void)
{
	std::string stdin_content;

	getline(std::cin, stdin_content);
	if (stdin_content == "exit") 
		exit(0);
}

void	Server::newClient(void)
{
	struct sockaddr_in	cAddr;
	int	fd;
	socklen_t addrLen = sizeof(struct sockaddr);

	fd = accept(this->_fd, (struct sockaddr *)&cAddr, &addrLen);
	if (fd == -1)
		throw std::range_error("could not establish new connection with client");
	if (!addPoll(fd))
		throw std::range_error("could not create new client");
	Client	newC(fd);
	this->_clients.push_back(newC);
}

bool	Server::addPoll(int fd)
{
	this->_ev.events = EPOLLIN;
	this->_ev.data.fd = fd;
	if (epoll_ctl(this->_epfd, EPOLL_CTL_ADD, fd, &this->_ev) == -1)
	{
		perror("epoll add");
		return (false);
	}
	return (true);
}

void	Server::startServer( void )
{
	struct epoll_event	eventList[MAX_EVENTS];

// waiting for request...
	bind(this->_fd, (struct sockaddr *)&this->_addr, sizeof(this->_addr));
	listen(this->_fd, 5);

// add server socket for new connection and stdin for exit
	if (!addPoll(this->_fd) || !addPoll(STDIN_FILENO))
		throw std::range_error("Could not create new poll");

// main loop
	while (true)
	{
		int nbEv = epoll_wait(this->_epfd, eventList, MAX_EVENTS, -1);

		for(int i = 0 ; i < nbEv ; i++)
		{
			if (eventList[i].data.fd == STDIN_FILENO)
				readStdin();
			else if (eventList[i].data.fd == this->_fd)
				newClient();
			else
				parseRequest(eventList[i].data.fd);
		}
	}
}

//constructors / destructors

Server::Server(void)
{
	return ;
}

Server::Server(const int port, const std::string password) : _password(password)
{
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	this->_addrLen = sizeof(struct sockaddr);
	memset(&this->_addr, 0, sizeof(this->_addr));
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(port);
	this->_addr.sin_addr.s_addr = INADDR_ANY;
	this->_epfd = epoll_create1(0);
	return ;
}

Server::Server(Server const &copy)
{
	*this = copy;
}
	
Server  &Server::operator=(Server const &rhs)
{
	if (this == &rhs)
		return (*this);
}

Server::~Server(void)
{
	return ;
}
