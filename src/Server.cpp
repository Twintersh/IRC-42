#include "Server.hpp"

//Server utils

bool	Server::addPoll(int fd)
{
	this->_ev.events = EPOLLIN;
	this->_ev.data.fd = fd;
	if (epoll_ctl(this->_epfd, EPOLL_CTL_ADD, fd, &this->_ev) == -1)
		return (false);
	return (true);
}

std::vector<Client>::iterator	Server::findClientFd(int fd)
{
	for(std::vector<Client>::iterator it = this->_clients.begin();it != this->_clients.end();it++)
		if (it->getFd() == fd)
			return it;
}
//parsing functions


//main functions

void	Server::parseRequest(struct epoll_event &curEv)
{
	char *buf = new char[BUFLEN];
	std::string	sBuf;
	int	bytes;

	bytes = recv(curEv.data.fd, buf, BUFLEN, 0);
	sBuf = buf;
	if (bytes == 0)
		killClient(curEv);
	else if (bytes > BUFLEN)
	{

	}
	else
		parseMsg(curEv.data.fd, sBuf);
	delete buf;
}

void Server::killClient(struct epoll_event &curEv)
{
	epoll_ctl(this->_epfd, EPOLL_CTL_DEL, curEv.data.fd, &curEv);
	this->_clients.erase(findClientFd(curEv.data.fd));
	close(curEv.data.fd);
	std::cout << "Closed connection with client" << std::endl;
}

void	Server::readStdin(void)
{
	std::string stdin_content;

	std::cout << "reading stdin" << std::endl;
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
	std::cout << "New connection established, adding client to poll" << std::endl;
	if (!addPoll(fd))
		throw std::range_error("could not create new client");
	Client	newC(fd);
	this->_clients.push_back(newC);
	std::cout << "Client added to client list" << std::endl;
}


void	Server::startServer( void )
{
	std::cout << "Server started" << std::endl;
	struct epoll_event	eventList[MAX_EVENTS];

	// waiting for request...
	bind(this->_fd, (struct sockaddr *)&this->_addr, sizeof(this->_addr));
	listen(this->_fd, 5);
	std::cout << "Server is waiting for request" << std::endl;
	
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
				parseRequest(eventList[i]);
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

Server::Server(Server const &copy) : _password(copy._password)
{
	*this = copy;
}
	
Server  &Server::operator=(Server const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_addr = rhs._addr;
	this->_addrLen = rhs._addrLen;
	this->_clients = std::vector<Client>(rhs._clients);
	this->_ev = rhs._ev;
	this->_fd = rhs._fd;
	this->_epfd = rhs._epfd;
	return *this;
}

Server::~Server(void)
{
	return ;
}
