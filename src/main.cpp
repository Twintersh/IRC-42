#include "Server.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage : <port> <password>" << std::endl;
		return 0;
	}
	if (!isNumber(argv[1]))
	{
		std::cout << "Usage: Port must be a number" << std::endl;
		return 1;
	}
	try
	{
		Server	server(atoi(argv[1]), argv[2]);
		server.startServer();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
