#include "Server.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage : <port> <password>" << std::endl;
		return 0;
	}
	Server	server(atoi(argv[1]), argv[2]);
	try
	{
		server.startServer();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
