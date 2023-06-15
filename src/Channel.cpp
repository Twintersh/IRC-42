#include "Channel.hpp"

Channel::Channel( void )
{
	return ;
}

Channel::Channel( Channel const &copy)
{
	*this = copy;
}

Channel  &Channel::operator=( Channel const &rhs)
{
	if (this == &rhs)
		return *this;

}

Channel::~Channel( void )
{
	return ;
}
