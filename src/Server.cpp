#include "Server.hpp"


// server utils
void	Server::clientError(int fd, std::string err)
{
	std::string	msg;

	msg = "[Server] ";
	msg += err;
	msg += "\n";
	send(fd, msg.c_str(), msg.size(), 0);
}

void	Server::log(Client client, std::string msgLog)
{
	time_t	timer = time(0);
	tm	*stime = localtime(&timer);
	char	buf[80];
	
	strftime(buf, sizeof(buf), "[%x %X]", stime);
	if (client.getFd() == -2)
		std::cout << buf << " " << msgLog << std::endl;
	else
		std::cout << buf << " Client " << client.getFd() << " : " << msgLog << std::endl;
}

bool	Server::addPoll(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);

	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	this->_ev.events = EPOLLIN;
	this->_ev.data.fd = fd;
	if (epoll_ctl(this->_epfd, EPOLL_CTL_ADD, fd, &this->_ev) == -1)
		return (false);
	return (true);
}

//main functions

void	Server::parseRequest(struct epoll_event &curEv)
{
	char buf[6000];
	int	bytes;

	bytes = recv(curEv.data.fd, buf, sizeof(buf), 0);
	std::string str(buf);
	std::istringstream strm(str);
	if (bytes == 0)
		killClient(curEv);
	else if (bytes >= MAX_BUF)
		clientError(curEv.data.fd, ERR_MSG_LENGTH);
	else
		parseMsg(curEv.data.fd, strm);
	memset(buf, 0, sizeof(buf));
}

void Server::killClient(struct epoll_event &curEv)
{
	close(curEv.data.fd);
	epoll_ctl(this->_epfd, EPOLL_CTL_DEL, curEv.data.fd, &curEv);
	log(curEv.data.fd, LOG_CLOSED);
	this->_clients.erase(curEv.data.fd);
}


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
		throw std::range_error("accept");
	log(Client(fd), LOG_NEW_CLIENT);
	if (!addPoll(fd))
		throw std::range_error("addPoll");
	this->_clients.insert(std::pair<int, Client *>(fd, new Client(fd)));
}


void	Server::startServer( void )
{
	log(Client(-2), LOG_START);
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
	this->_clients = std::map<int, Client *>(rhs._clients);
	this->_ev = rhs._ev;
	this->_fd = rhs._fd;
	this->_epfd = rhs._epfd;
	return *this;
}

Server::~Server(void)
{
	return ;
}
